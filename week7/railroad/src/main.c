/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f7xx.h"
#include "stm32746g_discovery.h"
			
GPIO_InitTypeDef led1_handle, led2_handle;

int main(void)
{

	HAL_Init();

	__HAL_RCC_GPIOF_CLK_ENABLE();

	led1_handle.Pin = GPIO_PIN_10;
	led1_handle.Mode = GPIO_MODE_OUTPUT_PP;

	HAL_GPIO_Init(GPIOF, &led1_handle);

	led2_handle.Pin = GPIO_PIN_9;
	led2_handle.Mode = GPIO_MODE_OUTPUT_PP;

	HAL_GPIO_Init(GPIOF, &led2_handle);

	while(1) {
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET);
		HAL_Delay(300);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
		HAL_Delay(75);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_Delay(300);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_Delay(75);
	}
}
