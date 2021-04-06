#include "main.h"
#include "stm32l0xx_it.h"

void TIM6_IRQHandler(void)
{
  TIM6->SR = 0;
  
  Pyro.Read();
  UART.Transmit((uint16_t)Pyro.data.adc);
  SETBIT(GPIOB->ODR, LED_CTRL);
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
    if (UART.Rx.buffer[0] == HEADER)
    {
      //UART.Tx.FormMessage(UART.Rx.buffer);
      UART.Transmit((uint16_t)Pyro.data.adc);
      UART.Rx.buffer[0] = 0x00;
    }
    UART.Receive();
  }
}

void EXTI4_15_IRQHandler(void)
{
  //EXTI->PR |= EXTI_PR_PR8;
  //CLEARBIT(EXTI->IMR, EXTI_IMR_IM8);
  //Pyro.Read();
}
