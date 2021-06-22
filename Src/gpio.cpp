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
  
  /* SPI CONFIGURATION */
  GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE2) | GPIO_MODER_MODE2_0;       /* SCLK - output mode */
  GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE3) | GPIO_MODER_MODE3_0;       /* SDI  - output mode */
  GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE4);                            /* SDO  - input mode */
  GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE5);                            /* INT2 - input mode */
  GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE6);                            /* INT1 - input mode */
  GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE7) | GPIO_MODER_MODE7_0;       /* CS   - output mode */
  
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI6_PA;
  
  /*EXTI SETTINGS*/
  EXTI->IMR |= EXTI_IMR_IM6;
  EXTI->RTSR |= EXTI_RTSR_TR6;
  
  NVIC_EnableIRQ(EXTI4_15_IRQn);
  NVIC_SetPriority(EXTI4_15_IRQn, 1);
  
  /* pin configuration */
  SETBIT(SPI_PORT, CS);
  SETBIT(SPI_PORT, SCLK);
}