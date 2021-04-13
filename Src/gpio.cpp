#include "gpio.hpp"
#include "pyro.hpp"

void GPIO_Init(void)
{
  /* I/O port A, B - enable */
  RCC->IOPENR |= RCC_IOPENR_IOPAEN | RCC_IOPENR_IOPBEN;
  
  /* LED & DEBUG - output mode */
  GPIOB->MODER &= ~GPIO_MODER_MODE1 &  ~GPIO_MODER_MODE2 &  ~GPIO_MODER_MODE4;
  GPIOB->MODER |=  GPIO_MODER_MODE1_0 | GPIO_MODER_MODE2_0 | GPIO_MODER_MODE4_0;
   
  /* PB5 - BK-SI - output mode */
  GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE5) | GPIO_MODER_MODE5_0; 
  
  if (Pyro.SERIN == FORCE)
    /* PB8 - BK-DL - output mode */
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE8) | GPIO_MODER_MODE8_0;
  else if (Pyro.SERIN == WAKEUP) {
    /* PB8 - BK-DL - input mode */
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE8);
    
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI8_PB;
    
    /*EXTI SETTINGS*/
    EXTI->IMR |= EXTI_IMR_IM8;
    EXTI->RTSR |= EXTI_RTSR_TR8;
    
    NVIC_EnableIRQ(EXTI4_15_IRQn);
    NVIC_SetPriority(EXTI4_15_IRQn, 1);  
  }
  
  /* SPI CONFIGURATION */
  GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE2) | GPIO_MODER_MODE2_0;       /* SCLK - output mode */
  GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE3) | GPIO_MODER_MODE3_0;       /* SDI  - output mode */
  GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE4);                            /* SDO  - input mode */
  GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE5);                            /* INT2 - input mode */
  GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE6);                            /* INT1 - input mode */
  GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE7) | GPIO_MODER_MODE7_0;       /* CS   - output mode */
  
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI6_PB;
  
  /*EXTI SETTINGS*/
  EXTI->IMR |= EXTI_IMR_IM6;
  EXTI->RTSR |= EXTI_RTSR_TR6;
  
  NVIC_EnableIRQ(EXTI4_15_IRQn);
  NVIC_SetPriority(EXTI4_15_IRQn, 1);
}