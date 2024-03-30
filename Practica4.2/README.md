### Objetivo
Implementar un módulo de software en un archivo fuente API_debounce.c con su correspondiente archivo de cabecera API_debounce.h y ubicarlos en el proyecto dentro de las carpetas /drivers/API/src y /drivers/API/inc, respectivamente.


https://github.com/jorgefvg/PdM_workspace/assets/161152623/6e2e68e2-9654-4458-a415-384ad6a84d5a


### Punto 2:
1. En API_debounce.h se deben ubicar los prototipos de las funciones públicas y las declaraciones:
### API_debounce.h
```javascript
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
```
/* La función readKey debe leer una variable interna del módulo y devolver true o false si la tecla fue presionada.  Si devuelve true, debe resetear (poner en false) el estado de la variable.*/
bool_t readKey();

2. En API_debounce.c se deben ubicar las declaraciones privadas, los prototipos de las funciones privadas y la implementación de todas las funciones del módulo, privadas y públicas:
La declaración de debounceState_t debe ser privada en el archivo .c y la variable de estado de tipo debounceState_t debe ser global privada (con static).
Declarar una variable tipo bool_t global privada que se ponga en true cuando ocurre un flanco descendente y se ponga en false cuando se llame a la función readKey();
Implementar un programa que cambie la frecuencia de parpadeo del LED entre 100 ms y 500 ms cada vez que se presione la tecla.  El programa debe usar las funciones anti-rebote del módulo API_debounce y los retardos no bloqueantes del módulo API_delay y la función readKey.
### API_debounce.c
```javascript
#include "API_debounce.h"

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
```
La variable privada global keyPressed se utiliza para almacenar el estado de la tecla. Se inicializa como false en la función debounceFSM_init, y su valor puede cambiar cuando ocurren flancos ascendentes o descendentes.

debounceFSM_init(debounceState_t *currentState, debounceState_t initialValue): Esta función inicializa la MEF Anti-Rebote. Recibe como argumentos un puntero a la variable currentState, que almacenará el estado actual de la MEF, y un valor initialValue, que indica el estado inicial de la MEF. Además, inicializa la variable global keyPressed en false.

debounceFSM_update(debounceState_t *currentState, delay_t *delay): Esta función actualiza la MEF Anti-Rebote en cada iteración del programa principal. Recibe como argumentos un puntero a la variable currentState, que almacena el estado actual de la MEF, y un puntero a la estructura delay_t, que es utilizada para implementar los retardos no bloqueantes. Dependiendo del estado actual de la MEF y del estado del pulsador, se realiza la transición entre estados y se activa la variable keyPressed en caso de que ocurra un flanco ascendente o descendente.

bool_t readKey(void): Esta función se utiliza para leer el estado interno de la MEF Anti-Rebote y determinar si ocurrió un flanco descendente en el pulsador. Retorna true si ocurrió un flanco descendente y false en caso contrario. Además, resetea el estado interno de la MEF almacenado en keyPressed para futuros flancos.

### main.c
Se declaran las siguientes variables globales privadas:
```javascript
/* Variables privadas ---------------------------------------------------------*/
delay_t ledDelay;                   // Retardo no bloqueante para los LEDs
debounceState_t state;              // Estado actual de la MEF Anti-Rebote
```
Se inicia la configuración de los periféricos y variables globales:
```javascript
int main(void) {
	/* Configuración del MCU */
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();

	// Inicializando la estructura para el retardo no bloqueante
	delayInit(&ledDelay, 40);

	// Inicializando la MEF Anti-Rebote con el estado inicial BUTTON_UP
	debounceFSM_init(&state, BUTTON_UP);

	uint32_t toggleFrequency = 100;

	/* Bucle infinito */
	while (1) {
		debounceFSM_update(&state, &ledDelay);

		if (readKey())
		{
			// Cambia la frecuencia de alternancia entre 100 ms y 500 ms
			if (toggleFrequency == 100)
			{
				toggleFrequency = 500;
			}
			else
			{
				toggleFrequency = 100;
			}

			delayWrite(&ledDelay, toggleFrequency);
		}

		// Alternar LED2 cada duración del retraso
		if (delayRead(&ledDelay))
		{
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		}
	}

	return 0;
}
```
Dentro del While, se actualiza la MEF Anti-Rebote mediante la función debounceFSM_update(&state, &ledDelay). Luego se verifica si ocurrió un flanco descendente en el pulsador utilizando la función readKey(). Si ocurrió un flanco, se cambia la frecuencia de toggleo (osea de encendido y apagado del led) entre 100 ms y 500 ms y se actualiza la variable ledDelay con el nuevo valor. Finalmente, se realiza el toggle del LED2 cada vez que se alcanza el retardo establecido en ledDelay.
