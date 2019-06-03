#include "stm32f7xx.h"
#include "stm32746g_discovery.h"

#ifndef SETUP_H
#define SETUP_H
/* 7 bit address of an I2C sensor shifted to left 1 bit, leaving place for W/R bit,
 * which is inserted by the HAL_I2C_Master_Transmit and HAL_I2C_Master_Receive */
#define TEMP_SENSOR_ADDRESS (0b1001000 << 1)

#define	HT16K33_ADDRESS		(0b1110000 << 1)

/* hőmérséklet szenzor */
#define	TC74_ADDRESS		(0b1001000 << 1)

/* regiszter címek */
#define READ_TEMP_REG		(0x00)




I2C_HandleTypeDef I2C_handle;            // defining the I2C configuration structure
UART_HandleTypeDef huart1;

I2C_HandleTypeDef hi2c1;


void I2C_Init_1(void);
void I2C_Init_2(void);
void SystemClock_Config(void);
void USART1_UART_Init(void);
void Error_Handler(void);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);

#endif //define SETUP_H
