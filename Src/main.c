#include "main.h"

void SystemClockSetting(void);

int main(void)
{
  SystemClockSetting();
  SystemCoreClockUpdate();
  
  GPIO_Init();
  
  Axel.Write(THRESH_ACT, 0x40);
  //Axel.Write(INT_ENABLE, 0x10);
  Axel.Write(INT_ENABLE, 0x80);
  Axel.Write(ACT_INACT_CTL, 0x70);
  Axel.Write(BW_RATE, 0x07);
  Axel.Write(DATA_FORMAT, 0x00);
  Axel.Write(POWER_CTL, 0x08);
  
  Axel.Axis(0x32);
  
  TIM2_Init((uint16_t)(SystemCoreClock / 1000), 5000); 
  TIM6_Init((uint16_t)(SystemCoreClock / 1000), 15);
  TIM7_Init((uint16_t)(SystemCoreClock / 1000), 16);
  TIM_Enable(TIM7);
  
  UART.Init();
  UART.Receive();
  
  while (1) {
    
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

