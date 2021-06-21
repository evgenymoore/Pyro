#include "main.h"
#include "stm32l0xx_it.h"

uint8_t counter = 0;

void TIM2_IRQHandler(void)
{
  CLEARREG(TIM2->SR);
  CLEARBIT(GPIOB->ODR, LED_CTRL);
  Alarm.State = AlarmDriver::PatternState::Ready;
}

void TIM6_IRQHandler(void)
{
  CLEARREG(TIM6->SR);
  
<<<<<<< HEAD
  (UART.counter != 83) ? (UART.counter++) : (UART.counter = 0);
=======
  /* transmission indication */
  SETBIT(GPIOB->ODR, LED_CTRL);
>>>>>>> 22bb9888f3f0813989209af2a93340ff8dc53a57
  
  (UART.counter != 88) ? (UART.counter++) : (UART.counter = 0);
  
  /* reading the data from direct link of PYD1588 */
  if (Pyro.SERIN == FORCE_TEMP) 
  {
    Pyro.Reset();
    /* switch to pyro data */
    Pyro.SERIN = FORCE_PIR;
    Pyro.Write(Pyro.SERIN);
  }
<<<<<<< HEAD
  Pyro.Read();
  //Alarm.Expectation.Calculation((uint16_t)Pyro.DIR.DR);
=======
  Pyro.Read();  
>>>>>>> 22bb9888f3f0813989209af2a93340ff8dc53a57
  UART.Transmit((uint16_t)Pyro.DIR.DR);
}

void TIM7_IRQHandler(void)
{
  CLEARREG(TIM7->SR);
  Pyro.Read();
  /* average temperature value */
  if (Pyro.SERIN == FORCE_TEMP && counter < 6)
  {
    switch (counter)
    {
      case 5  : Pyro.TEMP /= counter;
                UART.Tx.buffer[3] = (uint8_t)(Pyro.TEMP >> 8);
                UART.Tx.buffer[4] = (uint8_t)(Pyro.TEMP);
                Pyro.TEMP = counter = 0;
            break; 
      default : Pyro.TEMP += Pyro.DIR.DR;
                counter++;
            break;
    }
  }
}

void EXTI4_15_IRQHandler(void)
{
  EXTI->PR |= EXTI_PR_PR6;
  
  /* accelerometer alarm */
  SETBIT(GPIOB->ODR, LED_CTRL);
  
  /* alarm state - capture of sensor */  
  if (Alarm.State == AlarmDriver::PatternState::Ready)
  {
    Alarm.State = AlarmDriver::PatternState::Capture;
    TIM_Enable(TIM2);
  }
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
      TIM_Disable(TIM7);
      TIM_Enable(TIM6); 
    }
    else 
      UART.Receive();
  }
}
