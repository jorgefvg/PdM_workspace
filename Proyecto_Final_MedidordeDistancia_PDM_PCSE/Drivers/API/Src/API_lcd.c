/// @file API_lcd.c
/// @version 1.0
/// @date 14/04/2024
/// @author Ing. Jorge Vasquez
/// @title API de manejo del LCD de alto nivel
/// @brief funciones lcd_port.c de alto nivel

/* Includes ------------------------------------------------------------------*/
#include "API_lcd.h"
#include "API_i2c.h"
#include "API_lcd_port.h"

/* Definicion de Funciones --------------------------------------------------------*/
/**
 * @brief  lcd_send_cmd Envio de 4 comando por el LCD
 * @param  char le paso un comando.
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */

void lcd_send_cmd(char cmd) {
	char data_u, data_1;

	uint8_t data_t[4];

	data_u = cmd & 0xf0;
	data_1 = (cmd << 4) & 0xf0;
	data_t[0] = data_u | 0x0C; //en=1, rs=0
	data_t[1] = data_u | 0x08; //en=0, rs=0
	data_t[2] = data_1 | 0x0C; //en=1, rs=0
	data_t[3] = data_1 | 0x08; //en=0, rs=0

	I2C_transmitir_cmd(SLAVE_ADDRESS_LCD, (uint8_t*) data_t, LCD_LARGO_VALORES, LCD_TIEMPO_ESPERA);
}

/**
 * @brief  lcd_send_data Envio de 4 datos por el LCD
 * @param  char le paso un dato.
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
void lcd_send_data(char data) {

	char data_u, data_1;

	uint8_t data_t[4];

	data_u = (data & 0xf0);
	data_1 = ((data<<4)&0xf0);
	data_t[0] = data_u | 0x0D; //en=1, rs=0
	data_t[1] = data_u | 0x09; //en=0, rs=0
	data_t[2] = data_1 | 0x0D; //en=1, rs=0
	data_t[3] = data_1 | 0x09; //en=0, rs=0

	I2C_transmitir_data(SLAVE_ADDRESS_LCD, (uint8_t*) data_t, LCD_LARGO_VALORES, LCD_TIEMPO_ESPERA);
}

/**
 * @brief  lcd_clear limpia la pantalla LCD16x2
 * @param  void
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
void lcd_clear (void)
{
	lcd_send_cmd (0x80);
	for (int i=0; i<70; i++)
	{
		lcd_send_data (' ');
	}
}

/**
 * @brief  lcd_put_cur funcion para la posicion de escritura en la pantalla LCD16x2
 * @param  int mandamos posicion de la fila y columna
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
void lcd_put_cur(int row, int col)
{
	switch (row)
	{
	case 0:
		col |= 0x80;
		break;
	case 1:
		col |= 0xC0;
		break;
	}

	lcd_send_cmd (col);
}

/**
 * @brief  lcd_init Inicializa la pantalla LCD16x2, 4 bits de inicializacion
 * @param  void
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
void lcd_init(void) {

	HAL_Delay(50); //>40ms
	lcd_send_cmd(0x30);
	HAL_Delay(5); //>4.1ms
	lcd_send_cmd(0x30);
	HAL_Delay(1); //>100us
	lcd_send_cmd(0x30);
	HAL_Delay(10);
	lcd_send_cmd(0x20); // modo 4 bits
	HAL_Delay(10);

	//inicializacion del display
	lcd_send_cmd(0x28); //Conjunto de funciones -->DL=0 (modo 4 bits), N=1(Pantalla lcd de 2 lineas), F=0 (5x8 caracteres)
	HAL_Delay(1);
	lcd_send_cmd(0x08); //Display on/off control --> D=0, C=0, B=0 ---> display off
	HAL_Delay(1);
	lcd_send_cmd(0x01); //clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd(0x06); //modo de entrada establecido --> I/D = 1 (incremento del cursor) & S=0(noshift)
	HAL_Delay(1);
	lcd_send_cmd(0x0C); //Display on/off control --> D=1, C=0, B=0. (Cursor y parpadeo de los 2 ultimos bits)
}

/**
 * @brief  lcd_send_string mandamos cadenas de caracteres al LCD
 * @param  char
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
void lcd_send_string(char *str) {
	while (*str) lcd_send_data(*str++);
}

