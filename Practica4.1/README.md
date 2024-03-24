# Practica 4
### Objetivo:
Implementar un MEF para trabajar con anti-rebotes por software. 


https://github.com/jorgefvg/PdM_workspace/assets/161152623/49342a8e-9790-4b8b-bd0f-8983c86580ed


### Punto 1:
1. Crear un nuevo proyecto como copia del proyecto realizado para la práctica 3.
2. Implementar una MEF anti-rebote que permita leer el estado del pulsador de la placa NUCLEO-F4 y generar acciones o eventos ante un flanco descendente o ascendente, de acuerdo al siguiente diagrama:
<img width="411" alt="MEF" src="https://github.com/jorgefvg/practica/assets/161152623/bfd29720-eb3b-4667-a359-b9fbc851124f">

El estado inicial de la MEF debe ser BUTTON_UP.

3. Implementar dentro de main.c, las funciones:
```javascript
void debounceFSM_init();      // debe cargar el estado inicial
void debounceFSM_update();   // debe leer las entradas, resolver la lógica de transición de estados y actualizar las salidas
void buttonPressed();       // debe encender el LED
void buttonReleased();     // debe apagar el LED 
```
Queremos que el microcontrolador detecte el estado del botón:

<img width="429" alt="Estados" src="https://github.com/jorgefvg/practica/assets/161152623/1cc310d5-5581-4e24-86ab-381fe1c63fbb">

4. El tiempo de anti-rebote debe ser de 40 ms con un retardo no bloqueante como los implementados en la práctica 3.
La función debounceFSM_update() debe llamarse periódicamente.
### main.c
Acontinuacion se muestra parte del codigo, resaltando lo mas importante de este:
```javascript
int main(void)
 {
  HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();

	// Inicializando la estructura para el retardo no bloqueante
	delayInit(&ledDelay, 40); 
	
	// Inicializando la MEF Anti-Rebote con el estado inicial BUTTON_UP
	debounceState_t state;
	debounceFSM_init(&state, BUTTON_UP);

	/* Bucle infinito */
	while (1) {
		// Actualizar la MEF Anti-Rebote y controlar los LEDs
		debounceFSM_update(&state, &ledDelay);
	}
	return 0;
}
```
La función debounceFSM_init() inicializa la MEF Anti-Rebote con el estado inicial especificado. Este recibe como parametros un puntero al estado actual de la MEF (currentState) y el estado inicial deseado (initialValue).
```javascript
/* Inicializando la máquina de estados debounce */
void debounceFSM_init(debounceState_t *currentState, debounceState_t initialValue)
{
	// Se establece el estado inicial de la MEF
	*currentState = initialValue;
}
```
La función debounceFSM_update() se encarga de actualizar la MEF Anti-Rebote y controlar los flancos del pulsador. Recibe como parámetros un puntero al estado actual de la MEF (currentState) y un puntero a la estructura de retardo no bloqueante para controlar el LED (delay).

Esta función contiene un switch-case que maneja los diferentes estados de la MEF Anti-Rebote y toma acciones según los flancos detectados en el pulsador. También utiliza el retardo no bloqueante para controlar el LED.
```javascript
/* Actualiza la máquina de estados debounce */
void debounceFSM_update(debounceState_t *currentState, delay_t *delay)
{
	switch (*currentState)
	{
	case BUTTON_UP:
		// Si el botón PC13 de la placa está presionado (flanco descendente)
		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
		{
			*currentState = BUTTON_FALLING;
		}
		break;

	case BUTTON_FALLING:
		// Si el botón sigue presionado y ha pasado el retardo
		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET && delayRead(delay))
		{
			*currentState = BUTTON_DOWN;
			buttonPressed();
		}
		else
		{
			*currentState = BUTTON_UP;
		}
		break;

	case BUTTON_DOWN:
		// Si el botón ha sido soltado (flanco ascendente)
		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET)
		{
			*currentState = BUTTON_RAISING;
		}
		break;

	case BUTTON_RAISING:
		// Si el botón sigue soltado y ha pasado el retardo
		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET && delayRead(delay))
		{
			*currentState = BUTTON_UP;
			buttonReleased();
		}
		else
		{
			*currentState = BUTTON_DOWN;
		}
		break;

	default:
		/* Manejar estado inesperado (Error) */
		Error_Handler();
	}
}
```
La función buttonPressed() se encarga de manejar el evento de botón presionado. Es llamada cuando se detecta un flanco descendente del pulsador. En este caso, invierte el estado del LED1, es decir, si estaba encendido lo apaga, y si estaba apagado lo enciende.
```javascript
/* Maneja el evento de botón presionado */
void buttonPressed(void)
{
	HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
}
```
La función buttonReleased() se encarga de manejar el evento de botón soltado. Es llamada cuando se detecta un flanco ascendente del pulsador. En este caso, invierte el estado del LED3, es decir, si estaba encendido lo apaga, y si estaba apagado lo enciende.
```javascript
/* Maneja el evento de botón soltado */
void buttonReleased(void)
{
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
}
```
