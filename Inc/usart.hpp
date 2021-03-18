#ifndef USART_HPP
#define USART_HPP

#include "gpio.hpp"
#include "tim.h"

#define RX_HEADER       0xAA
#define CMD_1           0x01
#define CMD_2           0x02
#define CMD_3           0x03

class UartDriver {
private:
  static const uint8_t size = 5;
public:
  uint16_t delay;
  struct buffer
  {
    uint8_t buffer[size];
    uint8_t index;
  };
  buffer Rx; buffer Tx;
 
  UartDriver();
  void Init();
  void Transmit();
  void Receive();
};

extern UartDriver UART;

#endif
