#include "tim.h"

void TIM6_Init(uint16_t prescaler, uint16_t preload)        /*!< TIM ACTIVATION */
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
  
  TIM6->PSC |= prescaler - 1; 
  
  TIM6->ARR = preload - 1;     
  
  TIM6->EGR |= TIM_EGR_UG;
  __NOP();  
  TIM6->SR = 0;
  
  TIM6->DIER |= TIM_DIER_UIE;
  
  NVIC_SetPriority(TIM6_IRQn, 0); 
  NVIC_EnableIRQ(TIM6_IRQn);
}

void TIM_Enable(TIM_TypeDef* tim)
{
  tim->CR1 |= TIM_CR1_CEN;
}

void TIM_Disable(TIM_TypeDef* tim)
{
  tim->CR1 &= ~TIM_CR1_CEN;
  tim->SR = 0;
}
