#ifndef PYRO_HPP
#define PYRO_HPP

#include <stdint.h>
#include "stm32l071xx.h"

#include "gpio.hpp"

union PyroData
{
  uint64_t input;
  struct
  {
    uint64_t status     :  1;
    uint64_t adc        : 14;
    uint64_t config     : 25;
  };
};

class PyroDriver
{
public:
  PyroData data;
  
  void Write(uint32_t regval);
  void Read();
};

extern PyroDriver Pyro;

#endif /* PYRO_HPP */