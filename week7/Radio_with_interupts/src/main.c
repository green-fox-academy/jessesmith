/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include <stdio.h>
#include "stm32f7xx.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd.h"

GPIO_InitTypeDef led_handle, button_handle;

GPIO_TypeDef *vol_up_port = GPIOB;
uint16_t button1_pin = GPIO_PIN_4;
uint16_t vol_up_pin = GPIO_PIN_4;

GPIO_TypeDef *vol_down_port = GPIOB;
uint16_t button2_pin = GPIO_PIN_14;
uint16_t vol_down_pin = GPIO_PIN_14;

GPIO_TypeDef *freq_up_port = GPIOC;
uint16_t button3_pin = GPIO_PIN_6;
uint16_t freq_up_pin = GPIO_PIN_6;

GPIO_TypeDef *freq_down_port = GPIOI;
uint16_t button4_pin = GPIO_PIN_3;
uint16_t freq_down_pin = GPIO_PIN_3;

uint16_t led1_pin = GPIO_PIN_10;
uint16_t led2_pin = GPIO_PIN_9;
uint16_t led3_pin = GPIO_PIN_8;
uint16_t led4_pin = GPIO_PIN_7;

int volume;
int frequency;
int update_flag;

static void Error_Handler(void);
static void SystemClock_Config(void);

void GPIO_Init()
{
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();

	//Set up leds
	led_handle.Pin = (led1_pin | led2_pin | led3_pin | led4_pin);
	led_handle.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOF, &led_handle);

	//Set up Volume buttons
	button_handle.Pin = vol_up_pin;
	button_handle.Mode = GPIO_MODE_IT_RISING;
	button_handle.Pull = GPIO_NOPULL;
	button_handle.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(vol_up_port, &button_handle);

	button_handle.Pin = vol_down_pin;
	HAL_GPIO_Init(vol_down_port, &button_handle);

	//Set up freq buttons
	button_handle.Pin = freq_up_pin;
	HAL_GPIO_Init(freq_up_port, &button_handle);

	button_handle.Pin = freq_down_pin;
	HAL_GPIO_Init(freq_down_port, &button_handle);

	/* tell the interrupt handling unit to process our interrupts */
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	/* assign a priority to our interrupt line */
	HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);
	HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 0);
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
}

void LCD_Init()
{
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(1, LCD_FB_START_ADDRESS);
	BSP_LCD_SelectLayer(1);
	BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKGRAY);
	BSP_LCD_Clear(LCD_COLOR_DARKGRAY);
}

int main(void)
{
	frequency = 0;
	volume = 0;
	update_flag = 0;

	HAL_Init();
	SystemClock_Config();
	GPIO_Init();
	LCD_Init();

	BSP_LED_Init(LED_GREEN);

	//	/* drawing a red circle */
	//	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	//	BSP_LCD_FillCircle(50, 50, 30);

	/* drawing text */
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTYELLOW);

	char freq_text[100];
	sprintf(freq_text, "Freq: %d", frequency);
	BSP_LCD_DisplayStringAt(50, 75, (uint8_t *)freq_text, LEFT_MODE);

	char vol_text[100];
	sprintf(vol_text, "Volume: %d", volume);
	BSP_LCD_DisplayStringAt(50, 150, (uint8_t *)vol_text, LEFT_MODE);

	while (1)
	{
		HAL_GPIO_WritePin(GPIOF, led1_pin, HAL_GPIO_ReadPin(vol_up_port, vol_up_pin));
		HAL_GPIO_WritePin(GPIOF, led2_pin, HAL_GPIO_ReadPin(vol_down_port, vol_down_pin));
		HAL_GPIO_WritePin(GPIOF, led3_pin, HAL_GPIO_ReadPin(freq_up_port, freq_up_pin));
		HAL_GPIO_WritePin(GPIOF, led4_pin, HAL_GPIO_ReadPin(freq_down_port, freq_down_pin));

		if (update_flag)
		{

			BSP_LCD_Clear(LCD_COLOR_DARKGRAY);

			sprintf(freq_text, "Freq: %d", frequency);
			BSP_LCD_DisplayStringAt(50, 75, (uint8_t *)freq_text, LEFT_MODE);

			sprintf(vol_text, "Volume: %d", volume);
			BSP_LCD_DisplayStringAt(50, 150, (uint8_t *)vol_text, LEFT_MODE);

			update_flag = 0;
		}
	}
}

void EXTI9_5_IRQHandler()
{
	HAL_GPIO_EXTI_IRQHandler(freq_up_pin);
}

void EXTI3_IRQHandler()
{
	HAL_GPIO_EXTI_IRQHandler(freq_down_pin);
}

void EXTI4_IRQHandler()
{
	HAL_GPIO_EXTI_IRQHandler(vol_up_pin);
}

void EXTI15_10_IRQHandler()
{
	HAL_GPIO_EXTI_IRQHandler(vol_down_pin);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/* this is the place for the user code */
	if (GPIO_Pin == freq_down_pin)
		frequency--;
	if (GPIO_Pin == freq_up_pin)
		frequency++;
	if (GPIO_Pin == vol_up_pin)
		volume++;
	if (GPIO_Pin == vol_down_pin)
		volume--;

	update_flag = 1;
}

static void Error_Handler(void)
{
}

static void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/**Configure the main internal regulator output voltage */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/**Initializes the CPU, AHB and APB busses clocks */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 216;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 2;

	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/**Activate the Over-Drive mode */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK)
	{
		Error_Handler();
	}

	/**Initializes the CPU, AHB and APB busses clocks */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
	{
		Error_Handler();
	}
}
