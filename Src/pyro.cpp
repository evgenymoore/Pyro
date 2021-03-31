#include "pyro.hpp"

PyroDriver Pyro;

PyroDriver::PyroDriver() {}

void PyroDriver::Write(uint32_t regval)
{
  uint16_t i;
  /* register mask init */
  uint32_t mask = 0x1000000;
  for (i = 0; i < 25; i++) 
  {
    /* SI to HIGH */
    SETBIT(GPIOB->ODR, BK_SI);
    if (!(regval & mask)) 
    { CLEARBIT(GPIOB->ODR, BK_SI); }
    
    /* delay for t > 72 us */
    for (uint8_t j = 0; j < 100; j++) ;
    CLEARBIT(GPIOB->ODR, BK_SI);
    /* shift the mask for next bit checking */
    mask >>= 1;
  }
  
  /* SI to LOW*/
  CLEARBIT(GPIOB->ODR, BK_SI);
  /* interrupt after data transmition for t > 580 us */
  for (i = 0; i < 800; i++) ;
}

void PyroDriver::Read()
{
  DIR.input = 0;
  
  /* Set DL = High, to force fast uC controlled DL read out */
  SETBIT(GPIOB->MODER, GPIO_MODER_MODE8_0);
  SETBIT(GPIOB->ODR, BK_DL);
  while (!(GPIOB->ODR & BK_DL)) {}
  
  /* delay for <150 us */
  for (uint8_t i = 0; i < 170; i++) ;
  
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
    
    DIR.input <<= 1;
    
    /* if DL High set masked bit in PIRVal */
    if (GPIOB->IDR & BK_DL) DIR.input++;
  }
  
  SETBIT(GPIOB->MODER, GPIO_MODER_MODE8_0);
  /* create low to high transition */ 
  CLEARBIT(GPIOB->ODR, BK_DL);
  for (uint8_t i = 0; i < 5; i++) ;
}
