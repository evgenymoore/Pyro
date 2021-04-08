#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>

#include "tim.h"
#include "pyro.hpp"
#include "axel.hpp"
#include "gpio.hpp"
#include "usart.hpp"

#define DEVICE          1588U
#define PROJECT         0x9
#define STOP            0xE5

void Error_Handler(void);

#endif  /* __MAIN_H */