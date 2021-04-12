#ifndef AXEL_HPP
#define AXEL_HPP

#include "stm32l071xx.h"
#include "gpio.hpp"
#include "tim.h"

/* ADXL345 register's addresses */
#define DEVID                   0x00
        /*reserved*/
#define THRESH_TAP              0x1D
#define DUR                     0x20
#define LATENT                  0x22
#define WINDOW                  0x23
#define THRESH_ACT              0x24
#define TAP_AXES                0x2A
#define POWER_CTL               0x2D
#define INT_ENABLE              0x2E
#define INT_MAP                 0x2F
#define INT_SOURCE              0x30
#define DATA_FORMAT             0x31
#define DATAX0                  0x32
#define DATAX1                  0x33
#define DATAY0                  0x34
#define DATAY1                  0x35
#define DATAZ0                  0x36
#define DATAZ1                  0x37

union AxelData
{
  uint64_t input; 
  struct
  {
    uint64_t x          : 16;
    uint64_t y          : 16;
    uint64_t z          : 16;
  };
};

class AxelDriver
{
public: 
  AxelData data;
  
  AxelDriver();
  void Transmit(uint8_t address, uint8_t data);
  void Receive(uint8_t address);
  void Delay(uint16_t time);
};

extern AxelDriver Axel;

#endif /* AXEL_HPP */