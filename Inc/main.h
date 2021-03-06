#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>

#include "tim.h"
#include "pyro.hpp"
#include "axel.hpp"
#include "gpio.hpp"
#include "alarm.hpp"
#include "usart.hpp"

#define PYRO            1588U
#define ID              0x9
#define DEVICE          0xE5
#define CXR             0x46

void Error_Handler(void);

#endif  /* __MAIN_H */