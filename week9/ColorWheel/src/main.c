#include "main.h"
#include "setup.h"

GPIO_InitTypeDef gpio_adc_pin;
ADC_HandleTypeDef adc_handle;
ADC_ChannelConfTypeDef adc_channel_config;


/* the timer's config structure */
TIM_HandleTypeDef timer_handle2;
TIM_HandleTypeDef timer_handle3;
TIM_HandleTypeDef timer_handle5;

/* the output compare channel's config structure */
TIM_OC_InitTypeDef pwm_config;

/* pin config: we cannot use the green user LED because it's not connected to an output compare channel so we use PA15 */
GPIO_InitTypeDef PA15_LED_config;
GPIO_InitTypeDef PB4_LED_config;
GPIO_InitTypeDef PI0_LED_config;


volatile uint8_t counter = 1;

volatile int adc_val_1;
volatile int adc_val_2;


void init_adc()
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

void init_LEDs()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    PA15_LED_config.Pin = GPIO_PIN_15;
    PA15_LED_config.Mode = GPIO_MODE_AF_PP; /* configure as output, in PUSH-PULL mode */
    PA15_LED_config.Pull = GPIO_NOPULL;
    PA15_LED_config.Speed = GPIO_SPEED_HIGH;
    PA15_LED_config.Alternate = GPIO_AF1_TIM2;  /* we need this alternate function to use TIM2 in OC mode */

    HAL_GPIO_Init(GPIOA, &PA15_LED_config);

    __HAL_RCC_GPIOB_CLK_ENABLE();

    PB4_LED_config.Pin = GPIO_PIN_4	;
    PB4_LED_config.Mode = GPIO_MODE_AF_PP; /* configure as output, in PUSH-PULL mode */
    PB4_LED_config.Pull = GPIO_NOPULL;
    PB4_LED_config.Speed = GPIO_SPEED_HIGH;
    PB4_LED_config.Alternate = GPIO_AF2_TIM3;  /* we need this alternate function to use TIM2 in OC mode */

    HAL_GPIO_Init(GPIOB, &PB4_LED_config);

    __HAL_RCC_GPIOI_CLK_ENABLE();

    PI0_LED_config.Pin = GPIO_PIN_0;
    PI0_LED_config.Mode = GPIO_MODE_AF_PP; /* configure as output, in PUSH-PULL mode */
    PI0_LED_config.Pull = GPIO_NOPULL;
    PI0_LED_config.Speed = GPIO_SPEED_HIGH;
    PI0_LED_config.Alternate = GPIO_AF2_TIM5;  /* we need this alternate function to use TIM2 in OC mode */

    HAL_GPIO_Init(GPIOI, &PI0_LED_config);
}

void init_timers()
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    timer_handle2.Instance = TIM2;
    timer_handle2.Init.Prescaler = 16 - 1; // 108000000/108=1000000 -> speed of 1 count-up: 1/1000000 s = 0.001 ms
    timer_handle2.Init.Period = 100 - 1; // 100 x 0.001 ms = 10 ms = 0.01 s period
    timer_handle2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    timer_handle2.Init.CounterMode = TIM_COUNTERMODE_UP;

    /* configuring the timer in PWM mode instead of calling HAL_TIM_Base_Init(&timer_handle) */
    HAL_TIM_PWM_Init(&timer_handle2);


    __HAL_RCC_TIM3_CLK_ENABLE();

    timer_handle3.Instance = TIM3;
    timer_handle3.Init.Prescaler = 16 - 1; // 108000000/108=1000000 -> speed of 1 count-up: 1/1000000 s = 0.001 ms
    timer_handle3.Init.Period = 100 - 1; // 100 x 0.001 ms = 10 ms = 0.01 s period
    timer_handle3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    timer_handle3.Init.CounterMode = TIM_COUNTERMODE_UP;

    /* configuring the timer in PWM mode instead of calling HAL_TIM_Base_Init(&timer_handle) */
    HAL_TIM_PWM_Init(&timer_handle3);


    __HAL_RCC_TIM5_CLK_ENABLE();

    timer_handle5.Instance = TIM5;
    timer_handle5.Init.Prescaler = 16 - 1; // 108000000/108=1000000 -> speed of 1 count-up: 1/1000000 s = 0.001 ms
    timer_handle5.Init.Period = 100 - 1; // 100 x 0.001 ms = 10 ms = 0.01 s period
    timer_handle5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    timer_handle5.Init.CounterMode = TIM_COUNTERMODE_UP;

    /* configuring the timer in PWM mode instead of calling HAL_TIM_Base_Init(&timer_handle) */
    HAL_TIM_PWM_Init(&timer_handle5);
}

void init_PWMs()
{
    /*
     * 50% * 0.01 s = 0.005 s: 0.005 low, then 0.005 s high;
     * our eyes are not able to notice that it is a vibrating light
    */
    pwm_config.Pulse = 50;
    pwm_config.OCMode = TIM_OCMODE_PWM1;
    pwm_config.OCPolarity = TIM_OCPOLARITY_HIGH;
    pwm_config.OCFastMode = TIM_OCFAST_ENABLE;

    HAL_TIM_PWM_ConfigChannel(&timer_handle2, &pwm_config, TIM_CHANNEL_1);

    /*
	 * 50% * 0.01 s = 0.005 s: 0.005 low, then 0.005 s high;
	 * our eyes are not able to notice that it is a vibrating light
	*/
	pwm_config.Pulse = 50;
	pwm_config.OCMode = TIM_OCMODE_PWM1;
	pwm_config.OCPolarity = TIM_OCPOLARITY_HIGH;
	pwm_config.OCFastMode = TIM_OCFAST_ENABLE;

	HAL_TIM_PWM_ConfigChannel(&timer_handle3, &pwm_config, TIM_CHANNEL_1);

	/*
	 * 50% * 0.01 s = 0.005 s: 0.005 low, then 0.005 s high;
	 * our eyes are not able to notice that it is a vibrating light
	*/
	pwm_config.Pulse = 50;
	pwm_config.OCMode = TIM_OCMODE_PWM1;
	pwm_config.OCPolarity = TIM_OCPOLARITY_HIGH;
	pwm_config.OCFastMode = TIM_OCFAST_ENABLE;

	HAL_TIM_PWM_ConfigChannel(&timer_handle5, &pwm_config, TIM_CHANNEL_4);
}

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	USART1_UART_Init();

	init_adc();
	init_LEDs();
	init_timers();
	init_PWMs();


    HAL_TIM_PWM_Start(&timer_handle2, TIM_CHANNEL_1); //blue
    HAL_TIM_PWM_Start(&timer_handle3, TIM_CHANNEL_1); //green
    HAL_TIM_PWM_Start(&timer_handle5, TIM_CHANNEL_4); //red

    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(ADC_IRQn);

	HAL_ADC_Start_IT(&adc_handle);

    while (1) {
    }
}

void ADC_IRQHandler(void)
{
    HAL_ADC_IRQHandler(&adc_handle);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    /* deciding whether CH1 or CH8 measurement is active */
    if (!counter) {
        adc_val_1 = HAL_ADC_GetValue(&adc_handle);
//        printf("ADC1 value: %d.\r\n", adc_val_1);
        counter++;
	} else {
        adc_val_2 = HAL_ADC_GetValue(&adc_handle);
//        printf("ADC2 value: %d.\r\n", adc_val_2);
        counter--;
    }

    int blueness = adc_val_2 / 20;

	if (blueness > 100)
		blueness = 100;
	blueness = 100 - blueness;
//	printf("blueness: %d\r\n", blueness);

    int redness = adc_val_1 / 20;

	if (redness > 100)
		redness = 100;
	redness = 100 - redness;
//	printf("redness: %d\r\n", redness);

	int greenness = (adc_val_2 + adc_val_1) / 40;

	if (greenness > 100)
		greenness = 100;
	greenness = 100 - greenness;
//	printf("greenness: %d\r\n", greenness);


	__HAL_TIM_SET_COMPARE(&timer_handle2, TIM_CHANNEL_1, blueness);
	__HAL_TIM_SET_COMPARE(&timer_handle3, TIM_CHANNEL_1, greenness);
	__HAL_TIM_SET_COMPARE(&timer_handle5, TIM_CHANNEL_4, redness);

//    for (int i = 0; i < 500000; i++);
}

UART_PUTCHAR
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

UART_GETCHAR
{

uint8_t ch8;

HAL_UART_Receive(&huart1,&ch8,1,HAL_MAX_DELAY);

return ch8;

}
