/// @file API_lcd_port.c
/// @version 1.0
/// @date 14/04/2024
/// @author Ing. Jorge Vasquez
/// @title API de manejo del LCD de bajo nivel
/// @brief funciones lcd_port.c de bajo nivel

/* Includes ------------------------------------------------------------------*/
#include"API_lcd_port.h"
#include "API_lcd.h"
#include"API_Init.h"

extern I2C_HandleTypeDef hi2c1;

/* Definicion de Funciones --------------------------------------------------------*/
/**
 * @brief  I2C_transmitir_cmd Funcion que me permite mandar comandos por el puerto I2C.
 * @param &hi2c1 Instancia de la estructura del puerto I2C.
 * @param SLAVE_ADDRESS_LCD Dirreccion del esclavo, del PCF8574T es 0x4E.
 * @param data_t Cadena de caracteres (de cuatro posiciones) que contine los datos que le pasemos.
 * @param LCD_LARGO_VALORES Cantidad de caracteres que le enviamos de data_t.
 * @param LCD_TIEMPO_ESPERA Tiempo de duracion de la funcion.
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
void I2C_transmitir_cmd(uint16_t direccion, uint8_t *data_t, uint8_t tamano,
		uint8_t tiempo_espera){
	if(HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, data_t, LCD_LARGO_VALORES ,LCD_TIEMPO_ESPERA)!=HAL_OK)Error_Handler();

}

/**
 * @brief  I2C_transmitir_data Funcion que me permite mandar datos por el puerto I2C.
 * @param &hi2c1 Instancia de la estructura del puerto I2C.
 * @param SLAVE_ADDRESS_LCD Dirreccion del esclavo, del PCF8574T es 0x4E.
 * @param data_t Cadena de caracteres (de cuatro posiciones) que contine los datos que le pasemos.
 * @param LCD_LARGO_VALORES Cantidad de caracteres que le enviamos de data_t.
 * @param LCD_TIEMPO_ESPERA Tiempo de duracion de la funcion.
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
void I2C_transmitir_data(uint16_t direccion, uint8_t *data_t, uint8_t tamano,
		uint8_t tiempo_espera){
	if(HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, data_t, LCD_LARGO_VALORES ,LCD_TIEMPO_ESPERA)!=HAL_OK)Error_Handler();

}
