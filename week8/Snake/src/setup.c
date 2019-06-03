#include "setup.h"

/* regiszter címek */
#define SYSTEM_SETUP_REG	0x20
#define ROW_INT_SET_REG		0xA0
#define DISPLAY_SETUP_REG	0x80

/* regiszter értékek */
#define STANDBY_MODE		(0 << 0)
#define NORMAL_MODE			(1 << 0)
#define OUTPUT_MODE			(0 << 0)
#define DISP_ON_BLINK_OFF	(1 << 0)


#define	CONFIG_REG			(0x01)

/* regiszter értékek */
#define	TEMP_STANDBY_MODE	(1 << 7)
#define	TEMP_NORMAL_MODE	(0 << 7)
#define	DATA_READY			(0 << 6)
#define	DATA_NOT_READY		(1 << 6)

GPIO_InitTypeDef SCL_SDA_config;           // configure GPIOs for I2C data and clock lines

uint8_t normal_mode = (SYSTEM_SETUP_REG | NORMAL_MODE);
uint8_t output_mode = (ROW_INT_SET_REG | OUTPUT_MODE);
uint8_t no_blinking = (DISPLAY_SETUP_REG | DISP_ON_BLINK_OFF);
uint8_t max_brightness = (0xE0 | 0x0F);

uint8_t temp_normal_mode = TEMP_NORMAL_MODE;
uint8_t temp_read_reg = READ_TEMP_REG;

void setup_GPIOs_for_i2c(void) {
	SCL_SDA_config.Pin         = GPIO_PIN_8 | GPIO_PIN_9;  /* PB8: SCL, PB9: SDA */
	SCL_SDA_config.Pull        = GPIO_PULLUP;
	SCL_SDA_config.Mode        = GPIO_MODE_AF_OD;          /* configure in pen drain mode */
	SCL_SDA_config.Alternate   = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &SCL_SDA_config);
}

void dot_matrix_init(void) {
	HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, SYSTEM_SETUP_REG,
	I2C_MEMADD_SIZE_8BIT, NORMAL_MODE, 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, ROW_INT_SET_REG,
	I2C_MEMADD_SIZE_8BIT, OUTPUT_MODE, 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, DISPLAY_SETUP_REG,
	I2C_MEMADD_SIZE_8BIT, DISP_ON_BLINK_OFF, 1, 100);


	HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDRESS, &normal_mode, 1, 100);
	HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDRESS, &output_mode, 1, 100);
	HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDRESS, &no_blinking, 1, 100);
	//HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDRESS, &max_brightness, 1, 100);
	HAL_Delay(50);
}

void temp_sensor_init(void) {
	HAL_I2C_Mem_Write(&hi2c1, TC74_ADDRESS, CONFIG_REG, I2C_MEMADD_SIZE_8BIT,
			&temp_normal_mode, 1, 100);

	I2C_handle.Instance             = I2C1;
	I2C_handle.Init.Timing          = 0x40912732;
	I2C_handle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;

	HAL_I2C_Init(&I2C_handle);
}

void I2C_Init_1(void)
{
	/* defining the UART configuration structure */
		I2C_handle.Instance             = I2C1;
		I2C_handle.Init.Timing          = 0x40912732;
		I2C_handle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;

		HAL_I2C_Init(&I2C_handle);
}

void I2C_Init_2(void)
{
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x00303D5B;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
		Error_Handler();
	}
	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE)
			!= HAL_OK) {
		Error_Handler();
	}
	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK) {
		Error_Handler();
	}
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

void USART1_UART_Init(void)
{
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_NVIC_EnableIRQ(USART1_IRQn);
	HAL_NVIC_SetPriority(USART1_IRQn, 1, 1);
}

//Called from HAL_UART_Init, above
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
	__HAL_RCC_USART1_CLK_ENABLE();

	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	/**USART1 GPIO Configuration
	PB7     ------> USART1_RX
	PB9     ------> USART1_TX
	*/

	GPIO_InitStruct.Pin = GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_9;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

