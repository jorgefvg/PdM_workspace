/// @file main.c
/// @version 1.0
/// @date 06/04/2024
/// @author Ing. Jorge Vasquez
/// @title funcion principal
/// @brief archivo que maneja el main principal del dispositivo

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_gpio.h"
#include "API_Init.h"
#include "API_lcd.h"
#include "API_i2c.h"
#include "API_timer.h"
#include "API_uart.h"
#include "API_HCSR04.h"
#include "API_delay.h"
#include "API_state.h"
#include "API_lcd_port.h"
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
typedef enum{ //Define los estados de la MEF principal de INITIAL-READ-WRITE
	INITIAL,
	READ,
	WRITE,
} State_t;

/* Private define ------------------------------------------------------------*/
#define TIME_MESSAGE 400
#define TIME_INITIAL 2000
#define TIME_READ 2000
#define TIME_WRITE 2000
#define LED1 LD1_Pin //LED BLANCO
#define LED2 LD2_Pin //LED VERDE
#define LED3 LD3_Pin //LED AZUL
#define TIME_LED1 200
#define TIME_LED2 200
#define TIME_LED3 200

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
State_t actualState;
distance_t Distance;

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	delay_t delay_TIME_MESSAGE; //Para visualizacion de datos
	delay_t delay_INITIAL;
	delay_t delay_READ;
	delay_t delay_WRITE;
	delay_t delay_TIME_LED1;
	delay_t delay_TIME_LED2;
	delay_t delay_TIME_LED3;

	/* MCU Configuration--------------------------------------------------------*/
	HAL_Init();
	SystemClock_Config();

	delayInit(&delay_TIME_MESSAGE, TIME_MESSAGE);
	delayInit(&delay_INITIAL, TIME_INITIAL);
	delayInit(&delay_READ, TIME_READ);
	delayInit(&delay_WRITE, TIME_WRITE);
	delayInit(&delay_TIME_LED1, TIME_LED1);
	delayInit(&delay_TIME_LED2, TIME_LED2);
	delayInit(&delay_TIME_LED3, TIME_LED3);

	/* Initialize all configured peripherals */
	//Inicializa todos los perifericos a usar por la MEF
	GPIO_Init();
	uart_Init();
	I2C1_Init();
	TIM3_Init();
	lcd_init();

	actualState = INITIAL;
	delayRead(&delay_TIME_MESSAGE);
	delayRead(&delay_INITIAL); //Inicia conteo del delay la primera vez que se ejecuta
	delayRead(&delay_READ);
	delayRead(&delay_WRITE);
	delayRead(&delay_TIME_LED1);
	delayRead(&delay_TIME_LED2);
	delayRead(&delay_TIME_LED3);

	/* Infinite loop */
	while (1) {

		switch (actualState)
		{
		case INITIAL: //estado inicial de la MEF
			if(delayRead(&delay_INITIAL))    //Cuando se cumple el tiempo establecido
			{
				actualState = READ;          //Pasa al siguiente estado
				LedOff_GPIO(LED1);
			}
			if(delayRead(&delay_TIME_MESSAGE))
			{
				API_Initial();
			}
			if(delayRead(&delay_TIME_LED1))
			{
				Ledtoggle_GPIO(LED1);
			}
			break;

		case READ: //Estado de lectura de datos de la MEF
			if(delayRead(&delay_READ))
			{
				actualState = WRITE;
				LedOff_GPIO(LED2);
			}
			if(delayRead(&delay_TIME_MESSAGE))
			{
				API_Read_Measuring();
				Distance = API_distance();
			}
			if(delayRead(&delay_TIME_LED2))
			{
				Ledtoggle_GPIO(LED2);
			}
			break;

		case WRITE: //Estado de escritura de datos de la MEF
			if(delayRead(&delay_WRITE))
			{
				actualState = READ; //Pasa al estado anterior
				LedOff_GPIO(LED3);
			}
			if(delayRead(&delay_TIME_MESSAGE))
			{
				API_Write_LCD16X2(Distance);
				API_Write_UART(Distance);
			}
			if(delayRead(&delay_TIME_LED3))
			{
				Ledtoggle_GPIO(LED3);
			}
			break;

		default:
			Error_Handler();
			break;
		}
	}
}

