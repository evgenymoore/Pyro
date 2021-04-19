#include "main.h"
#include "stm32l0xx_it.h"

uint8_t counter = 0;

void TIM6_IRQHandler(void)
{
  TIM6->SR = 0;
  
  Pyro.Read();
  
  if (counter < 6) {
    if (counter != 0)
      Pyro.TEMP += Pyro.data.tem;
    counter++; 
  }
  else if (counter == 6) {
    Pyro.TEMP /= 5;
    UART.Transmit(Pyro.TEMP);
    counter++;
  }
  else if (counter > 6)
    UART._Transmit(Pyro.data.adc, Pyro.data.tem);
  
  (UART.freq != 66) ? (UART.freq++) : (UART.freq = 0);
  
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

void EXTI4_15_IRQHandler(void) {}
