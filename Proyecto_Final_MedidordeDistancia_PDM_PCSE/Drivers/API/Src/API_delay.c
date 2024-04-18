/// @file API_delay.c
/// @version 1.0
/// @date 14/04/2024
/// @author Ing. Jorge Vasquez
/// @title API de manejo de retardos no bloqueantes
/// @brief Funciones para los retardos no bloqueantes

/* Includes ------------------------------------------------------------------*/
#include "API_delay.h"
#include "API_Init.h"
#include "main.h"

/* Definicion de Funciones --------------------------------------------------------*/
/**
 * @brief  delayInit Inicializa la estructura de retardo no bloqueante
 * @param  delay_t puntero a la estructura de la demora
 * @param  tick_t  duracion de la demora
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
void delayInit(delay_t *delay, tick_t duration) {
	if (delay == NULL || duration <= 0 ){
		Error_Handler();
	}

	delay->duration = duration;
	delay->running = false;                                    //Inicializa el flag running en false
}

/**
 * @brief  delayRead Lee el retardo no bloqueante y devuelve true si ha finalizado
 * @param  delay_t puntero a la estructura de la demora
 * @return true si el retardo a terminado, false si el retardo aun no a finalizado
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
bool_t delayRead(delay_t *delay) {
	if (!delay->running) {                                    // Si el retardo no se ha ejecutado, se inicia y se registra el tiempo de inicio
		delay->startTime = HAL_GetTick();                     // Toma una marca de tiempo
		delay->running = true;                                // Cambia running a true
		return false;
	} else {                                                  // Si el retardo está en ejecución, se verifica si ha finalizado
		tick_t currentTime = HAL_GetTick();                   // Obtiene el tiempo actual
		tick_t elapsedTime = currentTime - delay->startTime;  // Saber si el tiempo de retardo se cumplio

		if (elapsedTime >= delay->duration) {                 // Si ha pasado el tiempo establecido, se finaliza el retardo y devuelve true
			delay->running = false;
			return true;                                      // El retardo a terminado.
		} else {                                              // Si el retardo aún no ha finalizado, devuelve false
			return false;
		}
	}
}

/**
 * @brief  delayWrite Actualiza o cambia la duración del retardo no bloqueante
 * @param  delay_t puntero a la estructura de la demora
 * @param  tick_t  duracion de la demora
 * @return void
 * @author Ing. Jorge Vasquez
 * @version 1.0
 * @date 14/04/2024
 */
void delayWrite(delay_t *delay, tick_t duration) {
	if (delay == NULL || duration <= 0 ){
		Error_Handler();
	}

	delay->duration = duration;                               //Se actualiza la duración del retardo
}
