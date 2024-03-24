#include "API_delay.h"
void Error_Handler(void);

/* Inicializa la estructura de retardo no bloqueante */
void delayInit(delay_t *delay, tick_t duration) {
	if (delay == NULL || duration <= 0 ){
			Error_Handler();
		}

	delay->duration = duration;
	delay->running = false;                                    //Inicializa el flag running en false
}

/* Lee el retardo no bloqueante y devuelve true si ha finalizado */
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

/* Actualiza o cambia la duración del retardo no bloqueante */
void delayWrite(delay_t *delay, tick_t duration) {
	if (delay == NULL || duration <= 0 ){
			Error_Handler();
		}

	delay->duration = duration;                               //Se actualiza la duración del retardo
}

