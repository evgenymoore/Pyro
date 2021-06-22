#ifndef PYRO_HPP
#define PYRO_HPP

#include <stdint.h>
#include "stm32l071xx.h"

#include "gpio.hpp"

union PyroData
{
  uint32_t input;
  struct
  {
    uint32_t tem     : 14;
    uint32_t adc     : 14;
  };
};

class PyroDriver
{
public:
  PyroData data;
  uint16_t TEMP;
  
  void Read();
  void Delay(uint32_t usec);
};

extern PyroDriver Pyro;

#endif /* PYRO_HPP */