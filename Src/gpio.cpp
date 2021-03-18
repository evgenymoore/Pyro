#include "gpio.hpp"

void LED_Init(void)
{
  /* I/O port B - enable */
  RCC->IOPENR |= RCC_IOPENR_IOPAEN | RCC_IOPENR_IOPBEN;
   /* GPIO port B - output mode */
  GPIOB->MODER = GPIO_MODER_MODE1_0 | GPIO_MODER_MODE4_0;
}
