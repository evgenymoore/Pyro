#include "pyro.hpp"

PyroDriver Pyro;

void PyroDriver::Read()
{
  data.input = 0;
  
  /* Set DL = High, to force fast uC controlled DL read out */
  SETBIT(GPIOB->MODER, GPIO_MODER_MODE8_0);
  SETBIT(GPIOB->ODR, BK_DL);
  while (!(GPIOB->ODR & BK_DL)) {}
  
  /* delay for 150 us */
  for (uint8_t i = 0; i < 150; i++) ;
  
  for (uint8_t i = 0; i < 28; i++)      
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
    if (GPIOB->IDR & BK_DL) data.input++;
  }
  
  SETBIT(GPIOB->MODER, GPIO_MODER_MODE8_0);
  /* create low to high transition */ 
  CLEARBIT(GPIOB->ODR, BK_DL);
  for (uint8_t i = 0; i < 5; i++) ;
}

