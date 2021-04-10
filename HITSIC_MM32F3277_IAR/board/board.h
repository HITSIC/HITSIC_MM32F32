#ifndef __BOARD_H
#define __BOARD_H

#include "hal_conf.h"
#include <stdio.h>

#define DEBUG_UART	        UART1
#define DEBUG_UART_BAUD		115200
#define DEBUG_UART_TX_GPIO		GPIOA
#define DEBUG_UART_TX_PIN               GPIO_Pin_9
#define DEBUG_UART_RX_GPIO		GPIOA
#define DEBUG_UART_RX_PIN               GPIO_Pin_10

void BOARD_Init(void);
void GPIO_DEBUG_Init(GPIO_TypeDef *GPIO_TX, u16 TX_PIN, GPIO_TypeDef *GPIO_RX, u16 RX_PIN);
void UART_DEBUG_Init(UART_TypeDef *debug_uartn, u32 baud);


void HSE_SYSCLK_Init(RCC_PLLMul_TypeDef pll_mul);

#endif  /** __BOARD_H */
