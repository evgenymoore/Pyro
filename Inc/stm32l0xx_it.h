#ifndef __STM32L0xx_IT_H
#define __STM32L0xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif  
  
void USART1_IRQHandler(void);
void EXTI4_15_IRQHandler(void);
void DMA1_Channel2_3_IRQHandler(void);

void TIM2_IRQHandler(void);
void TIM6_IRQHandler(void);
void TIM7_IRQHandler(void);

#ifdef __cplusplus
}
#endif
#endif /* __STM32L0xx_IT_H */
