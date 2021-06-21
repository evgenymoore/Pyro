#ifndef USART_HPP
#define USART_HPP

#include "main.h"

#define HEADER          0xAA

class UartDriver 
{
  private:
    uint16_t delay;
    void Delay();
  public:
    struct tx_buff
    {
      static const uint8_t size = 7;
      uint8_t buffer[size];
      uint8_t index;
      
      uint8_t CxR();
    };
    tx_buff Tx;
    
    struct rx_buff
    {
      static const uint8_t size = 4;
      uint8_t buffer[size];
      uint8_t index;
      
      uint8_t CxR();
    };
    rx_buff Rx;
    
    uint8_t counter;
        
    UartDriver();
    void Init();
    void Transmit(uint16_t data);
    void Receive();
};

extern UartDriver UART;

#endif
