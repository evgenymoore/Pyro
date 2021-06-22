#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>

#include "tim.h"
#include "axel.hpp"
#include "gpio.hpp"
#include "pyro.hpp"
#include "usart.hpp"
#include "alarm.hpp"

#define DEVICE          1798U
#define PROJECT         0x9
#define STOP            0xE5
#define CXR             0x46

void Error_Handler(void);

#endif  /* __MAIN_H */