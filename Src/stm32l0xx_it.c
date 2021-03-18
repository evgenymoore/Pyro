#include "main.h"
#include "stm32l0xx_it.h"

void TIM6_IRQHandler(void)
{
  TIM6->SR = 0;
  GPIOB->ODR ^= DEBUG;
}

void USART1_IRQHandler(void) {}

void DMA1_Channel2_3_IRQHandler(void)
{
  if (DMA1->ISR & DMA_ISR_TCIF3)
  {
    DMA1->IFCR |= 0xFF << 8;
    DMA1_Channel3->CCR &= ~DMA_CCR_EN;
    GPIOB->ODR ^= LED_CTRL;
    UART.Transmit();
    UART.Receive();
  }
  
}