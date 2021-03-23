#ifndef PYRO_HPP
#define PYRO_HPP

#include <stdint.h>
#include "stm32l071xx.h"
#include "gpio.hpp"

#define PIN_IS_INP      0
#define PIN_IS_OUT      1
#define DLA_OUT         (GPIOB->MODER &= 0xFFFFF7FF)
#define DLA_IN          (GPIOB->MODER &= 0xFFFFF3FF)

int                     PIRval  = 0;
unsigned long           statcfg = 0;

void readpyro(void);


class PyroDriver
{
public:
  uint32_t data;
  PyroDriver(GPIO_TypeDef* _port, uint16_t _pin);
  
  void Read();
  void Delay();
private:
  GPIO_TypeDef* dl_port;
  uint16_t dl_pin;
 
  void Clock();
  void End();
};

extern PyroDriver Pyro;

#endif /* PYRO_HPP */