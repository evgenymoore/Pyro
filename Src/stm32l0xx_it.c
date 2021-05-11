#include "main.h"
#include "stm32l0xx_it.h"

uint8_t counter = 0;

void TIM6_IRQHandler(void)
{
  TIM6->SR = 0;
  
  Pyro.Read();

  if (counter > 6) 
    UART.Transmit(Pyro.data.adc, Pyro.data.tem);
  else 
  {
    switch (counter)
    {
      case 0  : __NOP();
            break;
      case 6  : Pyro.TEMP /= 5;
                UART.Transmit(0, Pyro.TEMP);
            break;
      default : Pyro.TEMP += Pyro.data.tem;
            break;
    }
    counter++;
  }
  
  (UART.counter != 66) ? (UART.counter++) : (UART.counter = 0);
  
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
    if (UART.Rx.CxR() == UART.Rx.buffer[3])
    {
      UART.Transmit(DEVICE, 0);
      TIM_Enable(TIM6); 
    }
    else
      UART.Receive();
  }
}

void EXTI4_15_IRQHandler(void) {}
