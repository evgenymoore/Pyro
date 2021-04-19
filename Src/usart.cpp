#include "usart.hpp"

UartDriver UART;

UartDriver::UartDriver() {}

void UartDriver::Init()
{
 /*!< CLOCK CONFIGURATION */
  RCC->AHBENR  |= RCC_AHBENR_DMAEN;
  RCC->IOPENR  |= RCC_IOPENR_IOPAEN;
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

  /*!< GPIO CONFIGURATION*/  
    /* Tx config - Alternate mode pull-up */
  GPIOA->MODER &= ~GPIO_MODER_MODE9 | GPIO_MODER_MODE9_1;   

  /* Rx config - Alternate mode pull-up */
  GPIOA->MODER &= ~GPIO_MODER_MODE10 | GPIO_MODER_MODE10_1;

  /* Rx/Tx - pull-up */
  GPIOA->PUPDR |= GPIO_PUPDR_PUPD9_0 | GPIO_PUPDR_PUPD10_0;

  /* USART1_Tx/Rx - Alternate function #4 - 0x4 */
  GPIOA->AFR[1] |= (0x4 << GPIO_AFRH_AFSEL9_Pos) | (0x4 << GPIO_AFRH_AFSEL10_Pos);  

  /* RE/DE config - Output mode*/
  GPIOA->MODER &= ~GPIO_MODER_MODE11 | GPIO_MODER_MODE11_0;   
  
  /* baudrate value - 115200*/
  USART1->BRR |= SystemCoreClock / 115200; 
  /* DMA Enable Receiver */
  USART1->CR3 |= USART_CR3_DMAR;
  
/* DMA CONFIGURATION */
  /* clear the status register */
  DMA1->IFCR = 0;
  /* DMA channel 3 remapped to USART1_RX */
  DMA1_CSELR->CSELR |= 0x3 << DMA_CSELR_C3S_Pos;
  
  /* all the rest configs */
  DMA1_Channel3->CCR |= DMA_CCR_TCIE | DMA_CCR_MINC | DMA_CCR_PL_1;
  DMA1_Channel3->CPAR = (uint32_t)&(USART1->RDR);
  DMA1_Channel3->CMAR = (uint32_t)(Rx.buffer);
  DMA1_Channel3->CNDTR = sizeof(Rx.buffer);
  
  NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
  NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0);
  
  NVIC_EnableIRQ(USART1_IRQn);
  NVIC_SetPriority(USART1_IRQn, 0);
  
  /* transmit and receive enable */
  USART1->CR3 |= USART_CR3_EIE;
  USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void UartDriver::Transmit(uint16_t data)
{
  Tx.buffer[0] = HEADER;
  Tx.buffer[1] = (uint8_t)(data >> 8);
  Tx.buffer[2] = (uint8_t)(data);  
  Tx.buffer[3] = UartDriver::counter;

  GPIOA->BSRR |= RE_DE;
  USART1->ICR |= USART_ICR_TCCF;
  if (!(USART1->ISR & USART_ISR_TC)) 
  {
    while (Tx.index < sizeof(Tx.buffer)) 
    {
      USART1->TDR = Tx.buffer[Tx.index++];
      Delay();
    }
    USART1->ICR |= USART_ICR_TCCF;
    Tx.index = 0;
  }  
}

void UartDriver::Receive()
{
  GPIOA->BSRR |= RE_DE << 16;
  DMA1_Channel3->CCR &= ~DMA_CCR_EN;
  DMA1_Channel3->CNDTR = sizeof(Rx.buffer);
  DMA1_Channel3->CCR |=  DMA_CCR_EN;
}

void UartDriver::Delay(void)
{
  while (delay++ < 1000) {}
  delay = 0;
}

uint8_t UartDriver::rx_buff::CxR()
{
  uint8_t CxR = 0;
  for (uint8_t i = 1; i < sizeof(rx_buff::buffer); i++)
    CxR ^= rx_buff::buffer[i];
  return CxR;
}
