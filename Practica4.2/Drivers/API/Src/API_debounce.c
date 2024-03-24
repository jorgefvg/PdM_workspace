#include "API_debounce.h"
#include "API_delay.h"
// Variable privada global para almacenar el estado de la tecla
static bool_t keyPressed = false;

/* Inicializando la máquina de estados debounce */
void debounceFSM_init(debounceState_t *currentState, debounceState_t initialValue) {
	// Se establece el estado inicial de la MEF
	*currentState = initialValue;
	// Inicializamos la variable global keyPressed en falso
	keyPressed = false;
}

/* Actualiza la máquina de estados debounce */
void debounceFSM_update(debounceState_t *currentState, delay_t *delay) {
	switch (*currentState) {
	case BUTTON_UP:
		// Si el botón PC13 de la placa está presionado (flanco descendente)
		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET) {
			*currentState = BUTTON_FALLING;
		}
		break;
	case BUTTON_FALLING:
		// Si el botón sigue presionado y ha pasado el retardo
		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET && delayRead(delay)) {
			*currentState = BUTTON_DOWN;
			// Se activó un flanco descendente, establecemos keyPressed en true
			keyPressed = true;
		} else {
			*currentState = BUTTON_UP;
		}
		break;
	case BUTTON_DOWN:
		// Si el botón ha sido soltado (flanco ascendente)
		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET) {
			*currentState = BUTTON_RAISING;
		}
		break;
	case BUTTON_RAISING:
		// Si el botón sigue soltado y ha pasado el retardo
		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET && delayRead(delay)) {
			*currentState = BUTTON_UP;
			// Se activó un flanco ascendente, establecemos keyPressed en false
			keyPressed = false;
		} else {
			*currentState = BUTTON_DOWN;
		}
		break;
	default:
		// Manejo de estado inesperado
		Error_Handler();
		break;
	}
}

bool_t readKey(void) {
	bool_t keyStatus = keyPressed; // Leemos el estado de la tecla almacenado en keyPressed
	keyPressed = false;            // Reseteamos el estado de keyPressed para la siguiente lectura
	return keyStatus;              // Devolvemos el estado de la tecla
}
