#include "main.h"
#include "stm32l0xx_it.h"

void TIM6_IRQHandler(void)
{
  TIM6->SR = 0;
}

void USART1_IRQHandler(void) {}

void DMA1_Channel2_3_IRQHandler(void)
{
  if (DMA1->ISR & DMA_ISR_TCIF3)
  {
    /* clear the status register */
    DMA1->IFCR |= (0xFF << 8); 
    
    if (UART.Rx.buffer[0] == RX_HEADER)
    {
      switch (UART.Rx.buffer[1])
      {
        case CMD_1 : UART.Tx.buffer[4] = CMD_1;
                     break;
        case CMD_2 : UART.Tx.buffer[4] = CMD_2;
                     break;
        case CMD_3 : UART.Tx.buffer[4] = CMD_3;
                     break;
        default : UART.Tx.buffer[4] = 0x00;
      }
      UART.Transmit();
      UART.Rx.buffer[0] = 0x00;
    }
    GPIOB->ODR ^= LED_CTRL;
    UART.Receive();
  }
}