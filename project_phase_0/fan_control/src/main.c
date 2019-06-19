/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "setup.h"

volatile int new_pwm_val;

int main(void)
{
	new_pwm_val = 0;

	HAL_Init();
	SystemClock_Config();
	USART1_UART_Tx_Init();

#ifdef UART_RX
	USART1_UART_Rx_Init();
#endif

#ifdef USE_TIMERS
	Timers_Init();

	HAL_TIM_Base_Start(&tim2h);
#endif

#ifdef USE_PWMs
	Init_PWMs();
	Init_Pins_for_PWM_out();

	HAL_TIM_PWM_Start(&tim2h, TIM_CHANNEL_1);
#endif

#ifdef USE_ADC
	ADC_Channel_Read_Toggle = 0;

	Init_ADC();
#endif

#ifdef USE_I2C
	I2C_Init_1();
	I2C_Init_2();
#endif

	for(;;) {
//		HAL_Delay(500);
	}
}

#ifdef USE_ADC
	void ADC_IRQHandler(void)
	{
		HAL_ADC_IRQHandler(&adc_handle);
	}

	void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
	{
		int adc_val_1, adc_val_2;

	    /* deciding whether CH1 or CH8 measurement is active */
	    if (!ADC_Channel_Read_Toggle) {
	    	adc_val_1 = HAL_ADC_GetValue(&adc_handle);
	        ADC_Channel_Read_Toggle++;
		} else {
			adc_val_2 = HAL_ADC_GetValue(&adc_handle);
	        ADC_Channel_Read_Toggle--;
	    }

		__HAL_TIM_SET_COMPARE(&tim2h, TIM_CHANNEL_1, adc_val_1);
		__HAL_TIM_SET_COMPARE(&tim3h, TIM_CHANNEL_1, adc_val_2);
	}
#endif

#ifdef UART_RX
	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
		{
			if (UART_recv_data_char == '\r') {
				new_pwm_val = strtol(UART_data_in);
				UART_data_in[UART_rx_count++] = '\r';
				UART_data_in[UART_rx_count++] = '\n';
				HAL_UART_Transmit(huart, UART_data_in, UART_rx_count, HAL_MAX_DELAY);
				UART_rx_count = 0;
			} else {
				UART_data_in[UART_rx_count++] = UART_recv_data_char;
			}
			__HAL_TIM_SET_COMPARE(&tim2h, TIM_CHANNEL_1, new_pwm_val);
			HAL_UART_Receive_IT(&huart1, &UART_recv_data_char, 1);
		}
#endif
UART_PUTCHAR
{
	HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
	return ch;
}

#ifdef UART_RX
	UART_GETCHAR
	{
		uint8_t ch8;
		HAL_UART_Receive(&huart1,&ch8,1,HAL_MAX_DELAY);
		return ch8;
	}
#endif

