#include "main.h"
#include "stm32l0xx_it.h"

void TIM6_IRQHandler(void)
{
  CLEARREG(TIM6->SR);
  
  Pyro.Read();
  UART.Transmit((uint16_t)Pyro.DIR.DR);
}

void USART1_IRQHandler(void)
{
  /* UART error handler */
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
      UART.Rx.buffer[0] = 0x00;
      UART.Transmit(DEVICE);
      TIM_Enable(TIM6); 
    }
    else 
      UART.Receive();
  }
}
