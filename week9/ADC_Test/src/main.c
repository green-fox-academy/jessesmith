#include "main.h"
#include "setup.h"

GPIO_InitTypeDef gpio_adc_pin;
ADC_HandleTypeDef adc_handle;
ADC_ChannelConfTypeDef adc_channel_config;

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
//    adc_handle.Init.NbrOfDiscConversion = 2;
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
int main(void)
{
	HAL_Init();
	SystemClock_Config();
	USART1_UART_Init();

	init_adc();

    int adc_val;

    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(ADC_IRQn);

	HAL_ADC_Start_IT(&adc_handle);

    while (1) {
//        HAL_Delay(250);
//        HAL_ADC_Start(&adc_handle);
//        if (HAL_ADC_PollForConversion(&adc_handle, 10) == HAL_OK) {
//            adc_val = HAL_ADC_GetValue(&adc_handle);
//            printf("ADC1 value: %d.\r\n", adc_val_1);
//            printf("ADC2 value: %d.\r\n", adc_val_2);
//        }
//        if (HAL_ADC_PollForConversion(&adc_handle, 10) == HAL_OK) {
//                    adc_val = HAL_ADC_GetValue(&adc_handle);
//                    printf("ADC2 value: %d.\r\n", adc_val);
//        //            printf("ADC2 value: %d.\r\n", adc_val_2);
//                }
//        HAL_ADC_Stop(&adc_handle);
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
        printf("ADC1 value: %d.\r\n", adc_val_1);
        counter++;
	} else {
        adc_val_2 = HAL_ADC_GetValue(&adc_handle);
        printf("ADC2 value: %d.\r\n", adc_val_2);
        counter--;
    }
    for (int i = 0; i < 100000; i++);
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
