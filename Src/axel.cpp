#include "axel.hpp"

AxelDriver Axel;

AxelDriver::AxelDriver() {}

void AxelDriver::Transmit(uint8_t address, uint8_t data) 
{
  CLEARBIT(SPI_PORT, CS);    
  
  /* WRITE mode */
  CLEARBIT(SPI_PORT, SDI);

  for (uint8_t i = 2; i > 0; i--) 
  {
    /* SCLK = 0 */
    CLEARBIT(SPI_PORT, SCLK);
    Delay(125);
    /* SCLK = 1 */
    SETBIT(SPI_PORT, SCLK);
    Delay(125);
  }
  
  /* send the address byte */
  for (int8_t shift = 7; shift >= 0; shift--)
  {
    (address >> shift) & 0x01 ? (SPI_PORT |= SDI) : (SPI_PORT &= ~SDI);
    
    /* SCLK = 0 */
    CLEARBIT(SPI_PORT, SCLK);
    Delay(125);
    /* SCLK = 1 */
    SETBIT(SPI_PORT, SCLK);
    Delay(125);
  }
  /* send the data byte */
  for (int8_t shift = 7; shift >= 0; shift--)
  {
    (data >> shift) & 0x01 ? (SPI_PORT |= SDI) : (SPI_PORT &= ~SDI);
    
    /* SCLK = 0 */
    CLEARBIT(SPI_PORT, SCLK);
    Delay(125);
    /* SCLK = 1 */
    SETBIT(SPI_PORT, SCLK);
    Delay(125);
  }
  
  SETBIT(SPI_PORT, CS);
}

void AxelDriver::Receive(uint8_t address) 
{
  CLEARBIT(SPI_PORT, CS);    
  
  /* READ mode */
  SETBIT(SPI_PORT, SDI);

  for (uint8_t i = 2; i > 0; i--) 
  {
    /* SCLK = 0 */
    CLEARBIT(SPI_PORT, SCLK);
    Delay(125);
    /* SCLK = 1 */
    SETBIT(SPI_PORT, SCLK);
    Delay(125);
  }
  
  /* send the address byte */
  for (int8_t shift = 5; shift >= 0; shift--)
  {
    (address >> shift) & 0x01 ? (SPI_PORT |= SDI) : (SPI_PORT &= ~SDI);
    
    /* SCLK = 0 */
    CLEARBIT(SPI_PORT, SCLK);
    Delay(125);
    /* SCLK = 1 */
    SETBIT(SPI_PORT, SCLK);
    Delay(125);
  }
  
  /* receive the data byte */
  for (uint8_t i = 0; i < 8; i++)
  {
    data.input <<= 1;
    
    /* SCLK = 0 */
    CLEARBIT(SPI_PORT, SCLK);
    Delay(125);
    if (GPIOA->IDR & SDO) data.input++;
    /* SCLK = 1 */
    SETBIT(SPI_PORT, SCLK);
    Delay(125);
  }
  
  SETBIT(SPI_PORT, CS);
}

inline void AxelDriver::Delay(uint16_t time) { for (time; time >0; time--) ; }