#ifndef USART_HPP
#define USART_HPP

#include "gpio.h"
#include "tim.h"

const uint8_t size = 5;

class UartDriver {
public:
  struct buffer
  {
    uint8_t buffer[size];
    uint8_t index;
  };
  buffer Rx; buffer Tx;
  
  uint16_t delay;
  
  UartDriver();
  void Init();
  void Transmit();
  void Receive();
};

extern UartDriver UART;
#endif
