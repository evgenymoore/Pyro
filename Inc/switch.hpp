#pragma once

#include "main.h"

typedef enum 
{ MODE_0, MODE_1, MODE_2, MODE_3, 
  MODE_4, MODE_5, MODE_6, MODE_7 } 
MODE;

extern MODE DISTANCE;

MODE Switch(GPIO_TypeDef* GPIOx);