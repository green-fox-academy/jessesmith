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

	int INCREMENT = 1;

    /* GPIOI Periph clock enable */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    GPIOF->MODER |= (GPIO_MODER_MODER10_0); // Connecting GPIOF port enabled on pin 10
    GPIOF->MODER |= (GPIO_MODER_MODER9_0); // Connecting GPIOF port enabled on pin 10
    GPIOF->MODER |= (GPIO_MODER_MODER8_0); // Connecting GPIOF port enabled on pin 10
    GPIOF->MODER |= (GPIO_MODER_MODER7_0); // Connecting GPIOF port enabled on pin 10
    GPIOF->MODER |= (GPIO_MODER_MODER6_0); // Connecting GPIOF port enabled on pin 10

//    GPIOB->MODER |= (GPIO_MODER_MODER4_1);

    int delay = 100000;
    int count = 6, prev = 7;

    for (int c = 0; c < 50; c++) {

    	GPIOF->BSRR = (1 << count); //Activate pin 6
		for (int i = 0; i < delay; i++);
		GPIOF->BSRR = (1 << (prev + 16)); //Turn off 7
		for (int i = 0; i < delay; i++);

		prev = count;

		if (count == 10) {
			INCREMENT = 0;
		}
		if (count == 6) {
			INCREMENT = 1;
		}

		if (INCREMENT) {
			count++;
		} else {
			count--;
		}
    }

    GPIOF->BSRR = (1 << 26 | 1 << 25 | 1 << 24 | 1 << 23 | 1 << 22); //Turn off all go home zzzzzz
}
