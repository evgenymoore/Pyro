#include "main.h"
#include "stm32l0xx_it.h"

void TIM6_IRQHandler(void)
{
  CLEARREG(TIM6->SR);
  
  SETBIT(GPIOB->ODR, LED_CTRL);
  /* reading the data from direct link of PYD1588 */
  Pyro.Read();
  /* transmission of pyro data*/
  UART.Transmit((uint16_t)Pyro.DIR.DR);
}

void TIM7_IRQHandler(void)
{
  CLEARREG(TIM7->SR);
  Axel.Receive(DATAX0);
}

void EXTI4_15_IRQHandler(void)
{
  EXTI->PR |= EXTI_PR_PR6 | EXTI_PR_PR8;
  
  /* alarm */
  SWITCHBIT(GPIOB->ODR, LED_CTRL);
  
  Pyro.Reset();
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
    if (UART.Rx.CxR() == 0xEC)
    {
      /* send the pyro ID */
      UART.Transmit(PYRO);
      TIM_Enable(TIM6); 
    }
    else 
      UART.Receive();
  }
}
