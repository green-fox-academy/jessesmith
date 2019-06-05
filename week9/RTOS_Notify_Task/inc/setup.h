#include "stm32f7xx.h"
#include "stm32746g_discovery.h"

#ifndef SETUP_H
#define SETUP_H

void SystemClock_Config(void);
void USART1_UART_Init(void);
void Error_Handler(void);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);

UART_HandleTypeDef huart1;

#endif //define SETUP_H
