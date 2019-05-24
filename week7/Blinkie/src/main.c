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
			
int main(void)
{

    HAL_Init();

    LED1_GPIO_CLK_ENABLE();

    /* Configure LED1 */
    BSP_LED_Init(LED1);

    while(1) {
    	BSP_LED_Toggle(LED1);

    	HAL_Delay(1000);
    }

 }
