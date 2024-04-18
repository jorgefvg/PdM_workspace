/// @file API_state.c
/// @version 1.0
/// @date 14/04/2024
/// @author Ing. Jorge Vasquez
/// @title API de manejo de los estados de la MEF
/// @brief Funciones de la MEF

/* Includes ------------------------------------------------------------------*/
#include "API_lcd.h"
#include "API_HCSR04.h"
#include "API_state.h"

UART_HandleTypeDef huart2;

/* Variables Privadas -------------------------------------------------------------*/
distance_t distance; //asignar Variable int devuelta por funcion medicion en la API_HCSR04.c
static char_t dist[6]; //Convierte el valor entero "distancia" a una cadena, porque para poder imprimir los datos en la pantalla
                       //lcd 16x2 debemos de convertir los datos enteros a una cadena de caracteres

/* Declaracion de variables -------------------------------------------------------*/
//Valores esperados para LED: LD1_Pin|LD3_Pin|LD2_Pin
led_t LED;

/* Definicion de Funciones --------------------------------------------------------*/
/**
 * @brief  LedOff_GPIO Apaga el Led.
 * @param  led_t LED: LD1_Pin|LD3_Pin|LD2_Pin.
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */

void LedOff_GPIO(led_t LED)
{
	HAL_GPIO_WritePin(GPIOA, LED, GPIO_PIN_RESET);
}

/**
 * @brief  Ledtoggle_GPIO parpadeo del Led
 * @param  led_t LED: LD1_Pin|LD3_Pin|LD2_Pin.
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
void Ledtoggle_GPIO(led_t LED)
{
	HAL_GPIO_TogglePin(GPIOA, LED);
}

/**
 * @brief  API_distance Obtine el valor de la distancia.
 * @param  void.
 * @return distance_t devuelve el valor de la distancia en formato cadena tipo char
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
distance_t API_distance(void)
{
	distance = API_HCSR04_Measure(); //Hace la medicion con API_HCSR04.c y guarda en "distance"
	return distance;
}

/**
 * @brief  API_Initial Muestra en LCD mensaje de estado de Inicializacion.
 * @param  void.
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
void API_Initial(void)
{
	/*** Mostrar en lcd ***/
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("Proyecto Sensor");
	lcd_put_cur(1, 0);
	lcd_send_string("  Ultrasonico ");
}

/**
 * @brief  API_Read_Measuring Muestra en LCD mensaje de estado de Lectura.
 * @param  void.
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
void API_Read_Measuring(void)
{
	/*** Mostrar en lcd ***/
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("    HC-SR04     ");
	lcd_put_cur(1, 0);
	lcd_send_string("   Midiendo..  ");
}

/**
 * @brief  API_Write_LCD16X2 Muestra en LCD mensaje de estado de Escritura.
 * @param  void.
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
void API_Write_LCD16X2(distance_t distance)
{	/* Convierte entero a cadena char para mostrar valor en LCD */
	sprintf(dist, "%d", distance);
	/*** Mostrar en lcd ***/
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("    HC-SR04     ");
	lcd_put_cur(1, 0);
	lcd_send_string("Distancia: ");
	lcd_send_string(dist);
	lcd_send_string("cm");
}

/**
 * @brief  API_Write_UART Imprime el valor de la distancia por el puerto serial usart2.
 * @param  distance_t valor de la distancia.
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */

void API_Write_UART(distance_t distancia)
{
	char dato[40] = "";

	sprintf(dato, "Distancia = %d cm \r\n", distancia);
	HAL_UART_Transmit(&huart2, (uint8_t *)dato, sizeof(dato), 1000);
}
