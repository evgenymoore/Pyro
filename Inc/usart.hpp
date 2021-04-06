#ifndef USART_HPP
#define USART_HPP

#include "gpio.hpp"
#include "tim.h"

#define HEADER          0xAA

class UartDriver 
{
  private:
    uint16_t delay;
    static const uint8_t size = 3;
    void Delay();
  public:
    struct buffer
    {
      uint8_t buffer[size];
      uint8_t index;
      
      uint8_t CxR();
    };
    buffer Rx, Tx;
    
    UartDriver();
    void Init();
    void Transmit(uint16_t data);
    void Receive();
};

extern UartDriver UART;

#endif
