/*
 * API_debounce.h
 *
 *  Created on: Mar 21, 2024
 *      Author: jv
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "main.h"
#include "API_delay.h"

/* Estado del modelo */
typedef enum {
	BUTTON_UP,      // Botón suelto
	BUTTON_FALLING, // Apretando botón
	BUTTON_DOWN,    // Boton precionado
	BUTTON_RAISING, // Soltando botón
} debounceState_t;

/* Private function prototypes */
void debounceFSM_init(debounceState_t *currentState, debounceState_t initialValue);// debe cargar el estado inicial
void debounceFSM_update(debounceState_t *currentState, delay_t *delay);// debe leer las entradas, resolver la lógica
                                                                       // de transición de estados y actualizar las salidas
bool_t readKey(void);

#endif /* API_INC_API_DEBOUNCE_H_ */
