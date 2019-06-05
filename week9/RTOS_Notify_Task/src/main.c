/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
#include "FreeRTOS.h"
#include "task.h"

#include "stm32f7xx.h"
#include "stm32746g_discovery.h"

#include "main.h"

/*
 * What to do when an assertion fails
 */
void vAssertCalled(uint32_t ulLine, const char *pcFile){};

TaskHandle_t xTaskHandle1 = NULL;
TaskHandle_t xTaskHandle2 = NULL;

void vTask1_handler(void *params);
void vTask2_handler(void *params);

#ifdef USE_SEMIHOSTING
extern void initialise_monitor_handles();
#endif

#define TRUE 1
#define FALSE 0

int count = 0;

int main(void)
{
#ifdef USE_SEMIHOSTING
  initialise_monitor_handles();
  printf("Using SemiHosting\n");
#endif
  	HAL_Init();
	SystemClock_Config();
  	USART1_UART_Init();

  xTaskCreate(
      vTask1_handler,
      "Task1",
      configMINIMAL_STACK_SIZE * 10,
      NULL,
      2,
      &xTaskHandle1);

  xTaskCreate(
      vTask2_handler,
      "Task2",
      configMINIMAL_STACK_SIZE * 10,
      NULL,
      1,
      &xTaskHandle2);

  vTaskStartScheduler();

  for (;;);
}

void vTask1_handler(void *params)
{
  while (1)
  {
      if (count % 10 == 0) {
    	  xTaskNotify(xTaskHandle2, count, eSetValueWithOverwrite);
      }
      count++;
      vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vTask2_handler(void *params)
{
	uint32_t passed_value = 0;
    while (1)
    {
      if (xTaskNotifyWait(0, 0, &passed_value, 10) == TRUE) {
    	  printf("in task 2 woken by notification %d\r\n", passed_value);
      } else {
    	  printf("in task 2 woken by sleep timeout \r\n");
      }
      vTaskDelay(pdMS_TO_TICKS(500));
    }
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
