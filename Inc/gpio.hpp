#ifndef GPIO_HPP
#define GPIO_HPP

#include "stm32l071xx.h"

    /* GPIO port A pin configuration */
#define TXD                     ((uint16_t)0x0200)
#define RXD                     ((uint16_t)0x0400)
#define RE_DE                   ((uint16_t)0x0800)

    /* SPI port & pin configurations */
#define SCLK                    ((uint16_t)0x0004)      /* PA2 */ 
#define SDI                     ((uint16_t)0x0008)      /* PA3 */       /* MOSI */
#define SDO                     ((uint16_t)0x0010)      /* PA4 */       /* MISO */
#define INT2                    ((uint16_t)0x0020)      /* PA5 */
#define INT1                    ((uint16_t)0x0040)      /* PA6 */
#define CS                      ((uint16_t)0x0080)      /* PA7 */

#define SPI_PORT                GPIOA->ODR

    /* GPIO port B pin configuration */
#define LED_DEB                 ((uint16_t)0x0002)      //PB1
#define DEBUG                   ((uint16_t)0x0004)      //PB2
#define LED_CTRL                ((uint16_t)0x0010)      //PB4
#define BK_SI                   ((uint16_t)0x0020)      //PB5
#define BK_DL                   ((uint16_t)0x0100)      //PB8

#define SETBIT(PORT, BIT)       PORT |=  BIT;
#define CLEARBIT(PORT, BIT)     PORT &= ~BIT;     
#define SWITCHBIT(PORT, BIT)    PORT ^=  BIT;

#define CLEARREG(REG)           REG   =  0;

void GPIO_Init(void);

#endif