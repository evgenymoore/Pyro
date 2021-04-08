#ifndef AXEL_HPP
#define AXEL_HPP

#include "stm32l071xx.h"
#include "gpio.hpp"
#include "tim.h"

#define DEVID           0x00

#define INT_ENABLE      0x2E
#define DATAX0          0x32
#define DATAX1          0x33
#define DATAY0          0x34
#define DATAY1          0x35
#define DATAZ0          0x36
#define DATAZ1          0x37

union AxelData
{
  uint16_t input;
  struct
  {
    uint16_t id : 8;
  };
};

class AxelDriver
{
public: 
  AxelData data;
  
  AxelDriver();
  void Init();
  void Transmit(uint8_t address, uint8_t data);
  void Receive(uint8_t address);
  void Delay(uint16_t time);
};

extern AxelDriver Axel;

#endif /* AXEL_HPP */