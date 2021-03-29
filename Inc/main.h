#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>

#include "tim.h"
#include "gpio.hpp"
#include "usart.hpp"
#include "pyro.hpp"

extern FILE *log;

void Error_Handler(void);

#endif  /* __MAIN_H */