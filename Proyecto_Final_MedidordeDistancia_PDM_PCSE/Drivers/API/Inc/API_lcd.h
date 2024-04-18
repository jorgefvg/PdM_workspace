
#ifndef API_INC_API_LCD_H_
#define API_INC_API_LCD_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include <stdio.h>

/* Private defines -----------------------------------------------------------*/
#define SLAVE_ADDRESS_LCD 0x4E /* 0100 1110 -> 0X4E Esto es para un driver PCF8574T */
#define LCD_TIEMPO_ESPERA 100 // tiempo de espera
#define LCD_LARGO_VALORES 4   // largo de valores a transmitir

/* Exported functions prototypes ---------------------------------------------*/
void lcd_send_cmd(char cmd); //Envio de 4 comandos por el lcd
void lcd_send_data(char data); //Envio de 4 datos por el lcd
void lcd_init(void); //Inicializa la pantalla LCD16x2, 4 bits de inicializacion
void lcd_send_string(char *str); //Mandamos cadenas de caracteres al LCD
void lcd_put_cur(int row, int col); //Funcion para la posicion de escritura en la pantalla LCD16x2
void lcd_clear (void); //Limpia la pantalla LCD16x2

#endif /* API_INC_API_LCD_H_ */
