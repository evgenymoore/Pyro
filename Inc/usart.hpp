#ifndef USART_HPP
#define USART_HPP

#include "gpio.hpp"
#include "tim.h"

#define HEADER          0xAA

class UartDriver 
{
  private:
    uint16_t delay;
    void Delay();
  public:
    struct tx_buff
    {
      static const uint8_t size = 6;
      uint8_t buffer[size];
      uint8_t index;
    };
    tx_buff Tx;
    
    struct rx_buff
    {
      static const uint8_t size = 3;
      uint8_t buffer[size];
      uint8_t index;
      
      uint8_t CxR();
    };
    rx_buff Rx;
    
    uint8_t freq;
    
    UartDriver();
    void Init();
    void Transmit(uint32_t data);
    void _Transmit(uint32_t data, uint32_t tem);
    void Receive();
};

extern UartDriver UART;

#endif
