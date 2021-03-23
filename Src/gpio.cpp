#include "gpio.hpp"

void GPIO_Init(void)
{
  /* I/O port B - enable */
  RCC->IOPENR |= RCC_IOPENR_IOPAEN | RCC_IOPENR_IOPBEN;
  
   /* LED - output mode */
  GPIOB->MODER = GPIO_MODER_MODE1_0 | GPIO_MODER_MODE4_0;
  
  /* PB5 - BK-DL - Input with pull-down */
  GPIOB->PUPDR |= GPIO_PUPDR_PUPD5_1;
  
  /* PB5 - BK-DL - EXTI with rising edge trigger detection */
  EXTI->IMR |= EXTI_IMR_IM8;
  EXTI->RTSR |= EXTI_RTSR_TR8;
 
  NVIC_EnableIRQ(EXTI4_15_IRQn);
  NVIC_SetPriority(EXTI4_15_IRQn, 0);
}