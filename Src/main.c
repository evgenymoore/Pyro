#include "main.h"

void SystemClockSetting(void);

int main(void)
{
  SystemClockSetting();
  SystemCoreClockUpdate();

  /* PYD MODE*/
  Pyro.SERIN = FORCE_TEMP; 
  GPIO_Init();
  
  Pyro.Reset();
  Pyro.Write(Pyro.SERIN);
  
  SETBIT(SPI_PORT, CS);
  SETBIT(SPI_PORT, SCLK);
  Axel.Write(THRESH_ACT, 0x20);
  Axel.Write(ACT_INACT_CTL, 0x70);
  Axel.Write(INT_ENABLE, 0x10);
  Axel.Write(POWER_CTL, 0x08);
  
  TIM7_Init((uint16_t)(SystemCoreClock / 8000), 100);

  TIM6_Init((uint16_t)(SystemCoreClock / 1000), 12);
  UART.Init();  
  UART.Receive();
  
  while (1) {
    Axel.Read(INT_SOURCE);
  }
}

void SystemClockSetting(void)
{
  /* RCC->CFGR reset */
  RCC->CFGR = 0;
  while(RCC->CFGR & RCC_CFGR_SWS) {}
    
  /* HSI reset */
  RCC->CR &= ~RCC_CR_HSION;
  while(RCC->CR & RCC_CR_HSIRDY) {}
  
  /* PLL reset */
  RCC->CR &= ~RCC_CR_PLLON;
  while(RCC->CR & RCC_CR_PLLRDY) {}
  
  /* reset all interrupt's flags*/
  RCC->CSR &= ~RCC_CSR_RMVF;
  
  /*interrupt's cancellation*/
  RCC->CIER = 0;
  
  /* HSE clock enable bit */
  RCC->CR |= RCC_CR_HSEON;
  while(!(RCC->CR & RCC_CR_HSERDY)) {}
  
  /* system clock switch - HSE oscillator used as system clock*/
  RCC->CFGR |= RCC_CFGR_SW_HSE;
  while(!(RCC->CFGR & RCC_CFGR_SW_HSE)) {}  
  
  /* MSI reset */
  RCC->CR &= ~RCC_CR_MSION;
  while(RCC->CR & RCC_CR_MSIRDY) {}
}

void Error_Handler(void) {}

