#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"

#include "stm32f7xx.h"
#include "stm32746g_discovery.h"

#include "main.h"

typedef enum {
    PRESSED, NOT_PRESSED
} button_state_t;

button_state_t button_status;

osThreadId LedTaskHandle;
osThreadId ButtonTaskHandle;

void StartLedTask(void const * argument);
void StartButtonTask(void const * argument);

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	USART1_UART_Init();

	LED1_GPIO_CLK_ENABLE();

	BSP_LED_Init(LED1);

    /* definition and creation of LedTask */
    osThreadDef(LedTask, StartLedTask, osPriorityNormal, 0, 128);
    LedTaskHandle = osThreadCreate(osThread(LedTask), NULL);

    /* definition and creation of ButtonTask */
    osThreadDef(ButtonTask, StartButtonTask, osPriorityNormal, 0, 128);
    ButtonTaskHandle = osThreadCreate(osThread(ButtonTask), NULL);

    /* Start scheduler */
    osKernelStart();

    /* We should never get here as control is now taken by the scheduler */
    while (1) {
    }
}

void StartLedTask(void const * argument)
{
    while (1) {
        if (button_status == PRESSED) {
            HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_SET);
        } else if (button_status == NOT_PRESSED) {
            HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_RESET);
        }
        osDelay(50);
    }
}

void StartButtonTask(void const * argument)
{
    while (1) {
        if (HAL_GPIO_ReadPin(GPIOI, GPIO_PIN_11)) {
            button_status = PRESSED;
        } else {
            button_status = NOT_PRESSED;
        }
        osDelay(50);
    }
}
