#include "gpio.hpp"

void GPIO_Init(void)
{
  /* I/O port B - enable */
  RCC->IOPENR |= RCC_IOPENR_IOPAEN | RCC_IOPENR_IOPBEN;
  
   /* LED & DEBUG - output mode */
  GPIOB->MODER &= ~GPIO_MODER_MODE1 &  ~GPIO_MODER_MODE2 &  ~GPIO_MODER_MODE4;
  GPIOB->MODER |=  GPIO_MODER_MODE1_0 | GPIO_MODER_MODE2_0 | GPIO_MODER_MODE4_0;
  
  /* PB8 - BK-DL - EXTI with rising edge trigger detection */
  GPIOB->MODER &= ~GPIO_MODER_MODE8; 
  GPIOB->MODER |=  GPIO_MODER_MODE8_0;
  
  GPIOB->ODR |= BK_DL;
  GPIOB->MODER &= ~GPIO_MODER_MODE8;
  
  EXTI->IMR |= EXTI_IMR_IM8;
  EXTI->RTSR |= EXTI_RTSR_TR8;
  
    /*EXTI SETTINGS*/
  NVIC_EnableIRQ(EXTI4_15_IRQn);
  NVIC_SetPriority(EXTI4_15_IRQn, 0);
}