/// @file API_HCSRO4.c
/// @version 1.0
/// @date 14/04/2024
/// @author Ing. Jorge Vasquez
/// @title API sensor ultrasonico
/// @brief funciones del sensor ultrasonico

/* Includes ------------------------------------------------------------------*/
#include "API_HCSR04.h"
#include "API_timer.h"
#include "main.h"

TIM_HandleTypeDef htim3;

/* Declaracion de Variables -------------------------------------------------------*/
static uint32_t valor1, valor2, periodo; // valor1 =Tiempo subida del pulso ECHO, valor2 = tiempo bajada del pulso ECHO
static uint8_t v = 0; //flag: si el primer valor es capturado o es el segundo.
distance_t distancia;

/* Definicion de Funciones --------------------------------------------------------*/
/**
 * @brief  HAL_TIM_IC_CaptureCallback Funcion para calcular el ancho de pulso del echo, rutina de servicio de interrupcion
 * @param  TIM_HandleTypeDef
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	// Identificamos el canal que se disparo
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {

		//verificamos si es primera lectura
		if (v == 0) {
			//calculo del momento de subida
			valor1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			v = 1; //
			//cambiamos de polaridad
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_FALLING);
		} else if (v == 1) {
			// calculo del momento de bajada
			valor2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			 //una macro que reinicia el contador
			__HAL_TIM_SET_COUNTER(htim, 0);

			if (valor2 > valor1) {
				//periodo en microsegundos
				periodo = valor2 - valor1;
			}
			//volver cero para que vuelva a hacer otras lecturas
			v = 0;
			// cambio de polaridad
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
		}
	}
}

/**
 * @brief  API_HCSR04_Measure Mide la distancia al objeto
 * @param  void
 * @return distance_t devuelve el valor de la distancia en formato cadena tipo char
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
distance_t API_HCSR04_Measure(void)
{
	/*** Comienzo de la rutina de medicion ***/
	HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
	HAL_Delay(10); //10 us de espera
	HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);

	/*** Iniciar Timer y medir ancgo de pulso ***/
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);

	distancia = periodo/58; //Distancia en cm
	return distancia;
}
