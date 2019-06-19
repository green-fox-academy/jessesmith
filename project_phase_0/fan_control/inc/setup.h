#include "stm32f7xx.h"
#include "stm32746g_discovery.h"

#ifndef SETUP_H
#define SETUP_H


#define UART_PUTCHAR int __io_putchar(int ch)
#define UART_GETCHAR int __io_getchar()


void SystemClock_Config(void);
void USART1_UART_Tx_Init(void);

#ifdef UART_RX
	void USART1_UART_Rx_Init(void);

	int UART_rx_count;
	uint8_t UART_data_in[100];
	uint8_t UART_recv_data_char;
#endif

void Error_Handler(void);

UART_HandleTypeDef huart1;

#ifdef USE_TIMERS
	void Timers_Init(void);

	TIM_HandleTypeDef tim2h;
	TIM_HandleTypeDef tim3h;
	TIM_HandleTypeDef tim5h;
#endif

#ifdef USE_PWMs
	void Init_PWMs(void);
	void Init_Pins_for_PWM_out(void);

	TIM_OC_InitTypeDef pwm_config;
	GPIO_InitTypeDef PA15_LED_config;
	GPIO_InitTypeDef PB4_LED_config;
	GPIO_InitTypeDef PI0_LED_config;
#endif

#ifdef USE_ADC
	void Init_ADC(void);

	GPIO_InitTypeDef gpio_adc_pin;
	ADC_HandleTypeDef adc_handle;
	ADC_ChannelConfTypeDef adc_channel_config;

	volatile int ADC_Channel_Read_Toggle;
#endif

#ifdef USE_I2C
	void I2C_Init_1(void);
	void I2C_Init_2(void);

	I2C_HandleTypeDef I2C_h1;
	I2C_HandleTypeDef I2C_h2;
	GPIO_InitTypeDef SCL_SDA_config;           // configure GPIOs for I2C data and clock lines
#endif

#endif //define SETUP_H
