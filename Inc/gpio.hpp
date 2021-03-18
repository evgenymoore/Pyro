#ifndef GPIO_HPP
#define GPIO_HPP

#include "stm32l071xx.h"

    /* GPIO port A pin configuration */
#define TXD                     ((uint16_t)0x0200)
#define RXD                     ((uint16_t)0x0400)
#define RE_DE                   ((uint16_t)0x0800)

    /* GPIO port B pin configuration */
#define LED_DEB                 ((uint16_t)0x0002)
#define DEBUG                   ((uint16_t)0x0004)
#define LED_CTRL                ((uint16_t)0x0010) 

void LED_Init(void);

#endif