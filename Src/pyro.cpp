#include "pyro.hpp"

PyroDriver Pyro(GPIOB, BK_DL);

PyroDriver::PyroDriver(GPIO_TypeDef* _port, uint16_t _pin)
{
  dl_port = _port;
  dl_pin = _pin;
}

inline void PyroDriver::Delay(uint32_t usec)
{
  //while(usec-- > 0) {}
}

void PyroDriver::Read()
{
  data.input = 0;
  
  /* Set DL = High, to force fast uC controlled DL read out */
  SETBIT(GPIOB->MODER, GPIO_MODER_MODE8_0);
  SETBIT(GPIOB->ODR, BK_DL);
  while (!(dl_port->ODR & dl_pin)) {}
  
  /* delay for 150 us */
  for (uint8_t i = 0; i < 150; i++) ;
  
  for (uint8_t i = 0; i < 40; i++)      
  {
    /* create low to high transition */
    CLEARBIT(GPIOB->ODR, BK_DL);
    SETBIT(GPIOB->MODER, GPIO_MODER_MODE8_0);
    CLEARBIT(GPIOB->ODR, BK_DL);
    asm ("nop");
    SETBIT(GPIOB->ODR, BK_DL);
    asm ("nop");
    CLEARBIT(GPIOB->MODER, GPIO_MODER_MODE8);
    /* wait for stable low signal */
    for (uint8_t j = 0; j < 4; j++) ;
    
    data.input <<= 1;
    
    /* if DL High set masked bit in PIRVal */
    if (dl_port->IDR & dl_pin) data.input++;
  }
  
  SETBIT(GPIOB->MODER, GPIO_MODER_MODE8_0);
  /* create low to high transition */ 
  CLEARBIT(GPIOB->ODR, BK_DL);
  for (uint8_t i = 0; i < 5; i++) ;
}

