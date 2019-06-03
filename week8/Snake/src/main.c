#include "main.h"
#include "setup.h"


#define TRUE 1
#define FALSE 0

typedef struct {
	int x;
	int y;
} point;


uint8_t uart_data_in[100];
uint8_t recv_data_char;
int uart_rx_count = 0;
int uart_rx_complete = FALSE;

void spawn_apple(void);

uint32_t rand_num (void);

uint8_t temp;

point apple = {0};

uint8_t board[8][8] = {
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
};

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

	__HAL_RCC_I2C1_CLK_ENABLE();        /* enable the clock of the used peripheral */

//	I2C_Init_1();
	I2C_Init_2();
	setup_GPIOs_for_i2c();
	dot_matrix_init();
	temp_sensor_init();

	uint8_t first_column = 0b11111111;
	uint8_t clear = 0;

	uint8_t read_temp_reg = 0;
	uint8_t read_temp_val;

	while (1) {
		HAL_Delay(2000);

//		HAL_I2C_Master_Transmit(&I2C_handle, TEMP_SENSOR_ADDRESS, &read_temp_reg, sizeof(read_temp_reg), 100);
//		HAL_I2C_Master_Receive(&I2C_handle, TEMP_SENSOR_ADDRESS, &read_temp_val, sizeof(read_temp_val), 100);

		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 0, I2C_MEMADD_SIZE_8BIT, &clear, 1, 100);
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 2, I2C_MEMADD_SIZE_8BIT, &clear, 1, 100);
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 4, I2C_MEMADD_SIZE_8BIT, &clear, 1, 100);
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 6, I2C_MEMADD_SIZE_8BIT, &clear, 1, 100);
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 8, I2C_MEMADD_SIZE_8BIT, &clear, 1, 100);
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 10, I2C_MEMADD_SIZE_8BIT, &clear, 1, 100);
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 12, I2C_MEMADD_SIZE_8BIT, &clear, 1, 100);
		HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 14, I2C_MEMADD_SIZE_8BIT, &clear, 1, 100);

		/* or using HAL_I2C_Mem_Read():
		HAL_I2C_Mem_Read(&I2C_handle, TEMP_SENSOR_ADDRESS, read_temp_reg, I2C_MEMADD_SIZE_8BIT,
		&read_temp_val, sizeof(read_temp_val), 100);
		*/
//		temp = read_temp_val;
//		if (temp != 255) {
//			uint8_t first_digit = temp / 10;
//			uint8_t second_digit = temp - first_digit * 10;
//			print_number(first_digit);
//			HAL_Delay(750);
//			print_number(second_digit);
//			HAL_Delay(750);
//			print_celsius();
//			HAL_Delay(750);
//		} else {
//			int i;
//			for (i = 0; i < 8; i++) {
//				HAL_I2C_Mem_Write(
//						&hi2c1,
//						HT16K33_ADDRESS,
//						i * 2,
//						I2C_MEMADD_SIZE_8BIT,
//						0,
//						1,
//						100);
//			}
//		}

		board[apple.x][apple.y] = 0;
		spawn_apple();
		board[apple.x][apple.y] = 1;

		uint8_t hex_board[8] = {0, 0, 0, 0, 0, 0, 0, 0};

		for (int i = 0; i < 8; i++) {
			int8_t row = 0;

			for (int j = 0; j < 8; j++) {
				if (board[i][j])
					row |= (1 << j);
			}
			printf("got row as %d\r\n", row);
			hex_board[i] = row;
		}

		for (int i = 0; i < 8; i++) {
			printf("writing %02x\r\n", hex_board[i]);
			HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, i * 2, I2C_MEMADD_SIZE_8BIT, &hex_board[i], 1, 100);
		}

//		printf("Temperature: %d\r\n", read_temp_val);
	}
}

void spawn_apple()
{
	apple.x = rand_num() % 8;
	apple.y = rand_num() % 8;
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

uint32_t rand_num (void)
{
   static unsigned int z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;
   unsigned int b;
   b  = ((z1 << 6) ^ z1) >> 13;
   z1 = ((z1 & 4294967294U) << 18) ^ b;
   b  = ((z2 << 2) ^ z2) >> 27;
   z2 = ((z2 & 4294967288U) << 2) ^ b;
   b  = ((z3 << 13) ^ z3) >> 21;
   z3 = ((z3 & 4294967280U) << 7) ^ b;
   b  = ((z4 << 3) ^ z4) >> 12;
   z4 = ((z4 & 4294967168U) << 13) ^ b;
   return (z1 ^ z2 ^ z3 ^ z4);
}
