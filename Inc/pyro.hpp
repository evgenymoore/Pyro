#ifndef PYRO_HPP
#define PYRO_HPP

#include <stdint.h>
#include "stm32l071xx.h"

#include "gpio.hpp"

/*SERIN Configuration register - 25 bit*/
#define FORCE           0x00000030
#define WAKEUP          0x00402F10

/*DIRECT LINK Description*/
union DirectLink
{
  uint64_t input;
  struct
  {
    uint64_t CFGR       : 25;   //Configuration register
    uint64_t DR         : 14;   //Data register
    uint64_t SR         :  1;   //Status register
  };
};

class PyroDriver
{
public:
  DirectLink    DIR;
  uint32_t      SERIN;

  PyroDriver();
  void Write(uint32_t regval);
  void Read();
  void Reset();
};

extern PyroDriver Pyro;

#endif /* PYRO_HPP */