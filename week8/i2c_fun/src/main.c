#include "stm32f7xx.h"
#include "stm32746g_discovery.h"

#define UART_PUTCHAR int __io_putchar(int ch)
#define UART_GETCHAR int __io_getchar()

#define TRUE 1
#define FALSE 0

/* 7 bit address of an I2C sensor shifted to left 1 bit, leaving place for W/R bit,
 * which is inserted by the HAL_I2C_Master_Transmit and HAL_I2C_Master_Receive */
#define TEMP_SENSOR_ADDRESS (0b1001000 << 1)

#define	HT16K33_ADDRESS		(0b1110000 << 1)

/* regiszter címek */
#define SYSTEM_SETUP_REG	0x20
#define ROW_INT_SET_REG		0xA0
#define DISPLAY_SETUP_REG	0x80

/* regiszter értékek */
#define STANDBY_MODE		(0 << 0)
#define NORMAL_MODE			(1 << 0)
#define OUTPUT_MODE			(0 << 0)
#define DISP_ON_BLINK_OFF	(1 << 0)

/* hőmérséklet szenzor */
#define	TC74_ADDRESS		(0b1001000 << 1)

/* regiszter címek */
#define READ_TEMP_REG		(0x00)
#define	CONFIG_REG			(0x01)

/* regiszter értékek */
#define	TEMP_STANDBY_MODE	(1 << 7)
#define	TEMP_NORMAL_MODE	(0 << 7)
#define	DATA_READY			(0 << 6)
#define	DATA_NOT_READY		(1 << 6)


UART_HandleTypeDef huart1;

void SystemClock_Config(void);
void USART1_UART_Init(void);
void Error_Handler(void);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);

void I2C_Init_1(void);
void I2C_Init_2(void);

uint8_t uart_data_in[100];
uint8_t recv_data_char;
int uart_rx_count = 0;
int uart_rx_complete = FALSE;

I2C_HandleTypeDef I2C_handle;            // defining the I2C configuration structure
GPIO_InitTypeDef SCL_SDA_config;           // configure GPIOs for I2C data and clock lines

uint8_t temp;
I2C_HandleTypeDef hi2c1;

uint8_t normal_mode = (SYSTEM_SETUP_REG | NORMAL_MODE);
uint8_t output_mode = (ROW_INT_SET_REG | OUTPUT_MODE);
uint8_t no_blinking = (DISPLAY_SETUP_REG | DISP_ON_BLINK_OFF);
uint8_t max_brightness = (0xE0 | 0x0F);


/* a számjegyeket a http://dotmatrixtool.com oldalon generáltam a következő beállításokkal:
 - Width: 8px
 - Height: 8px
 - Byte Orger: Row Major
 - Endian: Little Endian
 */
const uint8_t digits[10][8] = {
		{ 0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e },	//0
		{ 0x04, 0x06, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e },	//1
		{ 0x0e, 0x11, 0x10, 0x10, 0x08, 0x04, 0x02, 0x1f },	//2
		{ 0x0e, 0x11, 0x10, 0x0c, 0x10, 0x10, 0x11, 0x0e },	//3
		{ 0x10, 0x18, 0x14, 0x12, 0x11, 0x1f, 0x10, 0x10 },	//4
		{ 0x1f, 0x01, 0x01, 0x0f, 0x10, 0x10, 0x11, 0x0e },	//5
		{ 0x0e, 0x11, 0x01, 0x0f, 0x11, 0x11, 0x11, 0x0e },	//6
		{ 0x1f, 0x10, 0x10, 0x08, 0x04, 0x02, 0x02, 0x02 },	//7
		{ 0x0e, 0x11, 0x11, 0x0e, 0x11, 0x11, 0x11, 0x0e },	//8
		{ 0x0e, 0x11, 0x11, 0x11, 0x1e, 0x10, 0x11, 0x0e }	//9
};

const uint8_t celsuis[8] = { 0x60, 0x60, 0x1e, 0x33, 0x81, 0x81, 0x33, 0x1e };

const uint8_t clear[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t temp_normal_mode = TEMP_NORMAL_MODE;
uint8_t temp_read_reg = READ_TEMP_REG;

void print_number(int num) {
	int i;
	for (i = 0; i < 8; i++) {
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, i * 2,
		I2C_MEMADD_SIZE_8BIT, &digits[num][i], 1, 100);
	}
}

void print_celsius(void) {
	int i;
	for (i = 0; i < 8; i++) {
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, i * 2,
		I2C_MEMADD_SIZE_8BIT, &celsuis[i], 1, 100);
	}
}

void dot_matrix_init(void) {
	HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDRESS, &normal_mode, 1, 100);
	HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDRESS, &output_mode, 1, 100);
	HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDRESS, &no_blinking, 1, 100);
	//HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDRESS, &max_brightness, 1, 100);
	HAL_Delay(50);
}

void temp_sensor_init(void) {
	HAL_I2C_Mem_Write(&hi2c1, TC74_ADDRESS, CONFIG_REG, I2C_MEMADD_SIZE_8BIT,
			&temp_normal_mode, 1, 100);

	I2C_handle.Instance             = I2C1;
	I2C_handle.Init.Timing          = 0x40912732;
	I2C_handle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;

	HAL_I2C_Init(&I2C_handle);
}

int16_t read_temperature(void) {
	/*
	 HAL_I2C_Master_Transmit(&hi2c1, TC74_ADDRESS, &temp_read_reg, 1, 100);
	 HAL_I2C_Master_Receive(&hi2c1, TC74_ADDRESS, &temp, 1, 100);
	 */

	if (HAL_I2C_Mem_Read(&hi2c1, TC74_ADDRESS, READ_TEMP_REG,
			I2C_MEMADD_SIZE_8BIT, &temp, 1, 100) != HAL_OK) {
		return -1;
	}
	HAL_Delay(50);
	return temp;
}

int main(void)
{

	HAL_Init();
	SystemClock_Config();
	USART1_UART_Init();

	HAL_UART_Receive_IT(&huart1, &recv_data_char, 1);

	SCL_SDA_config.Pin         = GPIO_PIN_8 | GPIO_PIN_9;  /* PB8: SCL, PB9: SDA */
	SCL_SDA_config.Pull        = GPIO_PULLUP;
	SCL_SDA_config.Mode        = GPIO_MODE_AF_OD;          /* configure in pen drain mode */
	SCL_SDA_config.Alternate   = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &SCL_SDA_config);

	__HAL_RCC_I2C1_CLK_ENABLE();        /* enable the clock of the used peripheral */

//	I2C_Init_1();
	I2C_Init_2();

	HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, SYSTEM_SETUP_REG,
	I2C_MEMADD_SIZE_8BIT, NORMAL_MODE, 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, ROW_INT_SET_REG,
	I2C_MEMADD_SIZE_8BIT, OUTPUT_MODE, 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, DISPLAY_SETUP_REG,
	I2C_MEMADD_SIZE_8BIT, DISP_ON_BLINK_OFF, 1, 100);

	dot_matrix_init();
	temp_sensor_init();

	/* számjegyek tesztelése
	 int i;
	 for (i = 0; i < 10; i++) {
	 print_number(i);
	 HAL_Delay(500);
	 }
	 */

	/* USER CODE END 2 */


	uint8_t first_column = 0b11111111;
	uint8_t clear = 0;

	uint8_t read_temp_reg = 0;
	uint8_t read_temp_val;

	while (1) {
		HAL_Delay(1000);

		HAL_I2C_Master_Transmit(&I2C_handle, TEMP_SENSOR_ADDRESS, &read_temp_reg, sizeof(read_temp_reg), 100);
		HAL_I2C_Master_Receive(&I2C_handle, TEMP_SENSOR_ADDRESS, &read_temp_val, sizeof(read_temp_val), 100);

		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 0, I2C_MEMADD_SIZE_8BIT, &first_column, 1, 100);
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 2, I2C_MEMADD_SIZE_8BIT, &clear, 1, 100);
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 4, I2C_MEMADD_SIZE_8BIT, &first_column, 1, 100);
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 6, I2C_MEMADD_SIZE_8BIT, &clear, 1, 100);
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 8, I2C_MEMADD_SIZE_8BIT, &clear, 1, 100);
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 10, I2C_MEMADD_SIZE_8BIT, &clear, 1, 100);
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 12, I2C_MEMADD_SIZE_8BIT, &clear, 1, 100);
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 14, I2C_MEMADD_SIZE_8BIT, &clear, 1, 100);

		/* or using HAL_I2C_Mem_Read():
		HAL_I2C_Mem_Read(&I2C_handle, TEMP_SENSOR_ADDRESS, read_temp_reg, I2C_MEMADD_SIZE_8BIT,
		&read_temp_val, sizeof(read_temp_val), 100);
		*/
		temp = read_temp_val;
		if (temp != 255) {
			uint8_t first_digit = temp / 10;
			uint8_t second_digit = temp - first_digit * 10;
			print_number(first_digit);
			HAL_Delay(750);
			print_number(second_digit);
			HAL_Delay(750);
			print_celsius();
			HAL_Delay(750);
		} else {
			int i;
			for (i = 0; i < 8; i++) {
				HAL_I2C_Mem_Write(
						&hi2c1,
						HT16K33_ADDRESS,
						i * 2,
						I2C_MEMADD_SIZE_8BIT,
						0,
						1,
						100);
			}
		}

		printf("Temperature: %d\r\n", read_temp_val);
	}
}

void I2C_Init_1(void)
{
	/* defining the UART configuration structure */
		I2C_handle.Instance             = I2C1;
		I2C_handle.Init.Timing          = 0x40912732;
		I2C_handle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;

		HAL_I2C_Init(&I2C_handle);
}

void I2C_Init_2(void)
{
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x00303D5B;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
		Error_Handler();
	}
	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE)
			!= HAL_OK) {
		Error_Handler();
	}
	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK) {
		Error_Handler();
	}
}

void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (recv_data_char == '\r') {
		uart_rx_complete = TRUE;
		uart_data_in[uart_rx_count++] = '\r';
		uart_data_in[uart_rx_count++] = '\n';
		HAL_UART_Transmit(huart, uart_data_in, uart_rx_count, HAL_MAX_DELAY);
		uart_rx_count = 0;
	} else {
		uart_data_in[uart_rx_count++] = recv_data_char;
	}

	HAL_UART_Receive_IT(&huart1, &recv_data_char, 1);
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

void USART1_UART_Init(void)
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

