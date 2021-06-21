#include "tim.h"

void TIM2_Init(uint16_t prescaler, uint16_t preload)        /*!< TIM2 ACTIVATION */
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  TIM2->CR1 |= TIM_CR1_OPM | TIM_CR1_ARPE;
  TIM2->PSC |= prescaler - 1; 
  TIM2->ARR = preload - 1;     
  TIM2->EGR |= TIM_EGR_UG;
  __NOP();  
  TIM2->SR = 0;
  TIM2->DIER |= TIM_DIER_UIE;
  NVIC_SetPriority(TIM2_IRQn, 0); 
  NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM6_Init(uint16_t prescaler, uint16_t preload)        /*!< TIM6 ACTIVATION */
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

void TIM7_Init(uint16_t prescaler, uint16_t preload)        /*!< TIM7 ACTIVATION */
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
  
  TIM7->PSC |= prescaler - 1; 
  TIM7->ARR = preload - 1;     
  TIM7->CR1 |= TIM_CR1_ARPE;
  TIM7->EGR |= TIM_EGR_UG;
  __NOP();  
  TIM7->SR = 0;
  TIM7->DIER |= TIM_DIER_UIE;
  NVIC_SetPriority(TIM7_IRQn, 0); 
  NVIC_EnableIRQ(TIM7_IRQn);
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
