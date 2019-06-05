#include "stm32f7xx.h"
#include "stm32746g_discovery.h"

#include "setup.h"

#define UART_PUTCHAR int __io_putchar(int ch)
#define UART_GETCHAR int __io_getchar()
