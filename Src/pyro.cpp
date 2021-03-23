#include "pyro.hpp"

PyroDriver Pyro(GPIOB, BK_SI);

PyroDriver::PyroDriver(GPIO_TypeDef* _port, uint16_t _pin)
{
  dl_port = _port;
  dl_pin = _pin;
}

void PyroDriver::Delay()
{
  /* 100 miliseconds of delay */
  uint16_t delay = 0;
  while (delay++ < (SystemCoreClock / 1000)) {}
  
}

inline void PyroDriver::Clock()
{
  clearpin(dl_port->ODR, dl_pin);               
  setpin(dl_port->MODER, GPIO_MODER_MODE8_0);  
  clearpin(dl_port->ODR, dl_pin);

  setpin(dl_port->ODR, dl_pin);
  
  clearpin(dl_port->MODER, GPIO_MODER_MODE8_0);  
}

inline void PyroDriver::End()
{
  clearpin(dl_port->ODR, dl_pin);
  setpin(dl_port->MODER, GPIO_MODER_MODE8_0);  

  for (uint8_t j = 0; j < 4; j++) ;
  clearpin(dl_port->MODER, GPIO_MODER_MODE8_0);
}

void PyroDriver::Read()
{
  NVIC_DisableIRQ(EXTI4_15_IRQn);
  data = 0;
  
  while (!(dl_port->IDR & dl_pin)) {}
  for (uint8_t i = 0; i < 240; i++) ;
  for (uint8_t i = 0; i < 40; i++)      //40 - number of bits
  {
    Clock();
    for (uint8_t j = 0; j < 4; j++) ;
    data <<= 0x1;
    if (dl_port->IDR & dl_pin) 
      data++;
  }
  
  End();
  
  NVIC_EnableIRQ(EXTI4_15_IRQn);
  setpin(EXTI->IMR, EXTI_IMR_IM8);
}
