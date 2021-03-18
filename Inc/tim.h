#pragma once

#include "stm32l071xx.h"

void TIM6_Init(uint16_t prescaler, uint16_t preload);

void TIM_Enable(TIM_TypeDef* tim);
void TIM_Disable(TIM_TypeDef* tim);
