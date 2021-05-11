#include "main.h"
#include "stm32l0xx_it.h"

uint8_t counter = 0;

void TIM6_IRQHandler(void)
{
  CLEARREG(TIM6->SR);
  /* transmission indication */
  SETBIT(GPIOB->ODR, LED_CTRL);
  
  /* reading the data from direct link of PYD1588 */
  Pyro.Read();
  /* average temperature value */
  if (Pyro.SERIN == FORCE_TEMP && counter <= 6) 
  {
    switch (counter)
    {
      case 0  : __NOP();
            break;
      case 6  : Pyro.TEMP /= 5;
                /* transmission of internal temperature*/
                UART.Transmit((uint16_t)Pyro.TEMP);
                Pyro.Reset();
                /* switch to pyro data */
                Pyro.SERIN = FORCE_PIR;
                Pyro.Write(Pyro.SERIN);
            break; 
      default : Pyro.TEMP += Pyro.DIR.DR;
            break;
    }
    counter++;
  }
  else
    /* transmission of pyro data*/
    UART.Transmit((uint16_t)Pyro.DIR.DR);
  
  (UART.counter != 88) ? (UART.counter++) : (UART.counter = 0);
}

void TIM7_IRQHandler(void)
{
  CLEARREG(TIM7->SR);
}

void EXTI4_15_IRQHandler(void)
{
  EXTI->PR |= EXTI_PR_PR6 | EXTI_PR_PR8;
  
  /* accelerometer alarm */
  //SWITCHBIT(GPIOB->ODR, LED_DEB);
}

void USART1_IRQHandler(void)
{
  /* UART ERROR HANDLER */
  if (USART1->ISR & (USART_ISR_ORE | USART_ISR_FE | USART_ISR_NE))
    /* clear interrupt status register*/
    USART1->ICR = 0xFF;
}

void DMA1_Channel2_3_IRQHandler(void)
{
  if (DMA1->ISR & DMA_ISR_TCIF3)
  {
    /* clear the status register */
    DMA1->IFCR |= (0xFF << 8); 
    if (UART.Rx.CxR() == UART.Rx.buffer[3])
    {
      /* send the pyro ID */
      UART.Transmit(PYRO);
      TIM_Enable(TIM6); 
    }
    else 
      UART.Receive();
  }
}
