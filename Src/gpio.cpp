#include "gpio.hpp"

void GPIO_Init(void)
{
  /* I/O port A, B - enable */
  RCC->IOPENR |= RCC_IOPENR_IOPAEN | RCC_IOPENR_IOPBEN;
  
   /* LED & DEBUG - output mode */
  GPIOB->MODER &= ~GPIO_MODER_MODE1 &  ~GPIO_MODER_MODE2 &  ~GPIO_MODER_MODE4;
  GPIOB->MODER |=  GPIO_MODER_MODE1_0 | GPIO_MODER_MODE2_0 | GPIO_MODER_MODE4_0;
   
  /* PB5 - BK-SI - output mode */
  GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE5) | GPIO_MODER_MODE5_0; 
  
  /* PB8 - BK-DL - output mode */
  GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE8) | GPIO_MODER_MODE8_0;
}