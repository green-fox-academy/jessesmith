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
			
GPIO_InitTypeDef led_handle, button_handle;

int main(void)
{

	HAL_Init();

	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	led_handle.Pin = GPIO_PIN_10;
	led_handle.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOF, &led_handle);

	led_handle.Pin = GPIO_PIN_9;
	HAL_GPIO_Init(GPIOF, &led_handle);

	led_handle.Pin = GPIO_PIN_8;
	HAL_GPIO_Init(GPIOF, &led_handle);

	led_handle.Pin = GPIO_PIN_7;
	HAL_GPIO_Init(GPIOF, &led_handle);

	button_handle.Pin = GPIO_PIN_4;
	button_handle.Mode = GPIO_MODE_INPUT;
	button_handle.Pull = GPIO_NOPULL;
	button_handle.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOB, &button_handle);

	int count = 0;
	while(1) {

		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))
		{
			count++;
			while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)) {
				HAL_Delay(50);
			}
		}

		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, count & 0b0001);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, count & 0b0010);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, count & 0b0100);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, count & 0b1000);
	}
}
