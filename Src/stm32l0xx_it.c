#include "main.h"
#include "stm32l0xx_it.h"

uint8_t counter = 0;

void TIM6_IRQHandler(void)
{
  TIM6->SR = 0;
  
  (UART.counter != 66) ? (UART.counter++) : (UART.counter = 0);
  
  Pyro.Read();

  UART.Transmit(Pyro.data.adc);
  
  SWITCHBIT(GPIOB->ODR, LED_CTRL);
}

void TIM7_IRQHandler(void)
{
  TIM7->SR = 0;
  
  Pyro.Read();
  /* average temperature value */
  if (counter < 6)
  {
    switch (counter)
    {
      case 5  : Pyro.TEMP /= counter;
                UART.Tx.buffer[3] = (uint8_t)(Pyro.TEMP >> 8);
                UART.Tx.buffer[4] = (uint8_t)(Pyro.TEMP);
                Pyro.TEMP = counter = 0;
            break; 
      default : Pyro.TEMP += Pyro.data.tem;
                counter++;
            break;
    }
  }
}

void USART1_IRQHandler(void)
{
  /* UART error handler */
  if (USART1->ISR & (USART_ISR_ORE | USART_ISR_FE | USART_ISR_NE))
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
      UART.Transmit(DEVICE);
      TIM_Disable(TIM7);
      TIM_Enable(TIM6); 
    }
    else
      UART.Receive();
  }
}

void EXTI4_15_IRQHandler(void) {}
