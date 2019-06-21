#include "setup.h"

#ifdef USE_PWMs
	void Init_PWMs()
	{
		/*
		 * 50% * 0.01 s = 0.005 s: 0.005 low, then 0.005 s high;
		 * our eyes are not able to notice that it is a vibrating light
		*/
//		pwm_config.Pulse = 0;
//		pwm_config.OCMode = TIM_OCMODE_PWM1;
//		pwm_config.OCPolarity = TIM_OCPOLARITY_HIGH;
//		pwm_config.OCFastMode = TIM_OCFAST_ENABLE;
//
//		HAL_TIM_PWM_ConfigChannel(&tim2h, &pwm_config, TIM_CHANNEL_1);

//		/*
//		 * 50% * 0.01 s = 0.005 s: 0.005 low, then 0.005 s high;
//		 * our eyes are not able to notice that it is a vibrating light
//		*/
		pwm_config.Pulse = 0;
		pwm_config.OCMode = TIM_OCMODE_PWM1;
		pwm_config.OCPolarity = TIM_OCPOLARITY_HIGH;
		pwm_config.OCFastMode = TIM_OCFAST_ENABLE;

		HAL_TIM_PWM_ConfigChannel(&tim3h, &pwm_config, TIM_CHANNEL_1);
//
//		/*
//		 * 50% * 0.01 s = 0.005 s: 0.005 low, then 0.005 s high;
//		 * our eyes are not able to notice that it is a vibrating light
//		*/
//		pwm_config.Pulse = 50;
//		pwm_config.OCMode = TIM_OCMODE_PWM1;
//		pwm_config.OCPolarity = TIM_OCPOLARITY_HIGH;
//		pwm_config.OCFastMode = TIM_OCFAST_ENABLE;
//
//		HAL_TIM_PWM_ConfigChannel(&tim5h, &pwm_config, TIM_CHANNEL_4);
	}

	void Init_Pins_for_PWM_out()
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();

		PA15_LED_config.Pin = GPIO_PIN_15;
		PA15_LED_config.Mode = GPIO_MODE_AF_PP; /* configure as input */
		PA15_LED_config.Pull = GPIO_NOPULL;
		PA15_LED_config.Speed = GPIO_SPEED_FREQ_LOW;
		PA15_LED_config.Alternate = GPIO_AF1_TIM2;  /* we need this alternate function to use TIM2 in OC mode */

		HAL_GPIO_Init(GPIOA, &PA15_LED_config);

		__HAL_RCC_GPIOB_CLK_ENABLE();

		PB4_LED_config.Pin = GPIO_PIN_4	;
		PB4_LED_config.Mode = GPIO_MODE_AF_PP; /* configure as output, in PUSH-PULL mode */
		PB4_LED_config.Pull = GPIO_NOPULL;
		PB4_LED_config.Speed = GPIO_SPEED_HIGH;
		PB4_LED_config.Alternate = GPIO_AF2_TIM3;  /* we need this alternate function to use TIM3 in OC mode */

		HAL_GPIO_Init(GPIOB, &PB4_LED_config);

//		__HAL_RCC_GPIOI_CLK_ENABLE();
//
//		PI0_LED_config.Pin = GPIO_PIN_0;
//		PI0_LED_config.Mode = GPIO_MODE_AF_PP; /* configure as output, in PUSH-PULL mode */
//		PI0_LED_config.Pull = GPIO_NOPULL;
//		PI0_LED_config.Speed = GPIO_SPEED_HIGH;
//		PI0_LED_config.Alternate = GPIO_AF2_TIM5;  /* we need this alternate function to use TIM5 in OC mode */
//
//		HAL_GPIO_Init(GPIOI, &PI0_LED_config);
	}
#endif

#ifdef USE_TIMERS
	void Timers_Init()
	{
		//IC Timer
		__HAL_RCC_TIM2_CLK_ENABLE();



//		thing

		tim2h.Instance = TIM2;
		tim2h.Init.Prescaler = 16 - 1; // 16000000/16=1000000 -> speed of 1 count-up: 1/1000000 s = 0.001 ms
		tim2h.Init.Period = 100 - 1; // 100 x 0.001 ms = 10 ms = 0.01 s period
		tim2h.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		tim2h.Init.CounterMode = TIM_COUNTERMODE_UP;

		/* configuring the timer in IC mode instead of calling HAL_TIM_Base_Init(&timer_handle) */
		HAL_TIM_IC_Init(&tim2h);

		TIM_MasterConfigTypeDef ms = { 0 };
		ms.MasterOutputTrigger = TIM_TRGO_RESET;
		ms.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

		HAL_TIMEx_MasterConfigSynchronization(&tim2h, &ms);

		TIM_IC_InitTypeDef thing;
		thing.ICPolarity = TIM_ICPOLARITY_RISING;
		thing.ICSelection = TIM_ICSELECTION_DIRECTTI;
		thing.ICPrescaler = TIM_ICPSC_DIV1;
		thing.ICFilter = 0x0;

		HAL_TIM_IC_ConfigChannel(&tim2h, &thing, TIM_CHANNEL_1);


		HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);

		//PWM control
		__HAL_RCC_TIM3_CLK_ENABLE();

		tim3h.Instance = TIM3;
		tim3h.Init.Prescaler = 16 - 1; // 16000000/16=1000000 -> speed of 1 count-up: 1/1000000 s = 0.001 ms
		tim3h.Init.Period = 100 - 1; // 100 x 0.001 ms = 10 ms = 0.01 s period
		tim3h.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		tim3h.Init.CounterMode = TIM_COUNTERMODE_UP;

		/* configuring the timer in PWM mode instead of calling HAL_TIM_Base_Init(&timer_handle) */
		HAL_TIM_PWM_Init(&tim3h);


		//General timer
		__HAL_RCC_TIM5_CLK_ENABLE();

		tim5h.Instance = TIM5;
		tim5h.Init.Prescaler = 16000 - 1; // 16000000/16000=1000 -> speed of 1 count-up: 1/1000 s = 1ms
		tim5h.Init.Period = 1000 - 1; // 1000 x 1ms = 1s period
		tim5h.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		tim5h.Init.CounterMode = TIM_COUNTERMODE_UP;

		HAL_NVIC_SetPriority(TIM5_IRQn, 3, 0);
		HAL_NVIC_EnableIRQ(TIM5_IRQn);

		/* configuring the timer in PWM mode instead of calling HAL_TIM_Base_Init(&timer_handle) */
		HAL_TIM_Base_Init(&tim5h);
	}
#endif

#ifdef USE_ADC
	void Init_ADC()
	{
	    /* configuring A0 pin as analog input */
	    __HAL_RCC_GPIOA_CLK_ENABLE();
		/* there is no need for setting the Alternate datafield like other peripherals*/
	    gpio_adc_pin.Mode = GPIO_MODE_ANALOG;
	    gpio_adc_pin.Pin = GPIO_PIN_0;
	    gpio_adc_pin.Speed = GPIO_SPEED_FAST;
	    gpio_adc_pin.Pull = GPIO_NOPULL;

	    HAL_GPIO_Init(GPIOA, &gpio_adc_pin);

	    __HAL_RCC_GPIOF_CLK_ENABLE();
	    gpio_adc_pin.Mode = GPIO_MODE_ANALOG;
	    gpio_adc_pin.Pin = GPIO_PIN_10;
	    gpio_adc_pin.Speed = GPIO_SPEED_FAST;
	    gpio_adc_pin.Pull = GPIO_NOPULL;

	    HAL_GPIO_Init(GPIOF, &gpio_adc_pin);

	    /* configuring ADC3, as it is the only ADC wired out to the headers */
	    __HAL_RCC_ADC3_CLK_ENABLE();
	    adc_handle.Instance = ADC3;
	    adc_handle.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	    adc_handle.Init.Resolution = ADC_RESOLUTION_12B;

	    /* these 5 settings are closely related */
	    adc_handle.Init.ScanConvMode = ENABLE;
	    adc_handle.Init.ContinuousConvMode = ENABLE;
	    adc_handle.Init.DiscontinuousConvMode = DISABLE;
	    adc_handle.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	    adc_handle.Init.NbrOfConversion = 2;

	    HAL_ADC_Init(&adc_handle);

	    /* configuring a channel belonging to ADC3 */
	    adc_channel_config.Channel = ADC_CHANNEL_0;
	    adc_channel_config.Rank = ADC_REGULAR_RANK_1;
	    adc_channel_config.SamplingTime = ADC_SAMPLETIME_56CYCLES;

	    HAL_ADC_ConfigChannel(&adc_handle, &adc_channel_config);

	    adc_channel_config.Channel = ADC_CHANNEL_8;
	    adc_channel_config.Rank = ADC_REGULAR_RANK_2;
	    adc_channel_config.SamplingTime = ADC_SAMPLETIME_56CYCLES;

	    HAL_ADC_ConfigChannel(&adc_handle, &adc_channel_config);
	}
#endif

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

void USART1_UART_Tx_Init(void)
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

#ifdef UART_RX
	void USART1_UART_Rx_Init()
	{
		UART_rx_count = 0;
		HAL_UART_Receive_IT(&huart1, &UART_recv_data_char, 1);
	}

	void USART1_IRQHandler()
	{
		HAL_UART_IRQHandler(&huart1);
	}
#endif

#ifdef USE_I2C
	void I2C_Init_1(void)
	{

//		HAL_I2C_Mem_Write(&I2C_h1, TC74_ADDRESS, CONFIG_REG, I2C_MEMADD_SIZE_8BIT,
//					&temp_normal_mode, 1, 100);

		/* defining the UART configuration structure */
		I2C_h1.Instance             = I2C1;
		I2C_h1.Init.Timing          = 0x40912732;
		I2C_h1.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;

		HAL_I2C_Init(&I2C_h1);

		/* READ TEMP Sample
		if (HAL_I2C_Mem_Read(&hi2c1, TC74_ADDRESS, READ_TEMP_REG,
				I2C_MEMADD_SIZE_8BIT, &temp, 1, 100) != HAL_OK) {
			return -1;
		}
		HAL_Delay(50);
		return temp;
		*/

	}

	void I2C_Init_2(void)
	{
		I2C_h2.Instance = I2C1;
		I2C_h2.Init.Timing = 0x00303D5B;
		I2C_h2.Init.OwnAddress1 = 0;
		I2C_h2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
		I2C_h2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
		I2C_h2.Init.OwnAddress2 = 0;
		I2C_h2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
		I2C_h2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
		I2C_h2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
		if (HAL_I2C_Init(&I2C_h2) != HAL_OK) {
			Error_Handler();
		}

		/** Configure Analog filter
		 */
		if (HAL_I2CEx_ConfigAnalogFilter(&I2C_h2, I2C_ANALOGFILTER_ENABLE) != HAL_OK) {
			Error_Handler();
		}
		/** Configure Digital filter
		 */
		if (HAL_I2CEx_ConfigDigitalFilter(&I2C_h2, 0) != HAL_OK) {
			Error_Handler();
		}

//		HAL_I2C_Master_Transmit(&I2C_h2, HT16K33_ADDRESS, &normal_mode, 1, 100);
//		HAL_I2C_Master_Transmit(&I2C_h2, HT16K33_ADDRESS, &output_mode, 1, 100);
//		HAL_I2C_Master_Transmit(&I2C_h2, HT16K33_ADDRESS, &no_blinking, 1, 100);
//		HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDRESS, &max_brightness, 1, 100);
		HAL_Delay(50); //SOME TIME to get it ready
	}
#endif

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

