## Practica 5.2
### Punto 2
Sobre el ejercicio de la práctica 4, implementar un programa que utilice el módulo de uart para informar al usuario cuando se producen los flancos ascendente y descendente.


https://github.com/jorgefvg/PdM_workspace/assets/161152623/fd4656bc-2640-41a8-83e1-5638c63e7541


1. Copiar los archivos fuente API_delay.c, API_delay.h, API_debounce.c, API_debounce.h de la practica 4.2 y los archivos fuente API_uart.c, API_uart.h de la Practica5.1, ubicarlos en el proyecto dentro de las carpetas /drivers/API/src y /drivers/API/inc, respectivamente.
### main.c
Acontinuacion se muestra parte del programa que se implemento:
```javascript
int main(void) {
	/* Configuración del MCU */
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();

	// Inicializando la estructura para el retardo no bloqueante
	delayInit(&ledDelay, 40);

	// Inicializando la MEF Anti-Rebote con el estado inicial BUTTON_UP
	debounceFSM_init(&state, BUTTON_UP);

	uint32_t toggleFrequency = 100;

	if (!uartInit())
	{
		// En caso de que la inicialización falle, parpadea el LED de la placa para indicar que hay un problema con la UART
		while (1)
		{
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			HAL_Delay(1000);
		}
	}

	/* Bucle infinito */
	while (1) {
		debounceFSM_update(&state, &ledDelay);

		if (readKey())
		{
			// Cambia la frecuencia de alternancia entre 100 ms y 500 ms
			if (toggleFrequency == 100)
			{
				toggleFrequency = 500;
				// Envia un mensaje por la UART cuando se detecta un flanco ascendente
				uint8_t msg[] = "Flanco ascendente detectado\r\n";
				uartSendString(msg);

				// Encender el LED1 al detectar el flanco ascendente
				HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
			}
			else
			{
				toggleFrequency = 100;
				// Envia un mensaje por la UART cuando se detecta un flanco descendente
				uint8_t msg[] = "Flanco descendente detectado\r\n";
				uartSendString(msg);

				// Encender el LED3 al detectar el flanco descendente
				HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
			}
			// Espera un tiempo para que los LEDs estén encendidos
			HAL_Delay(100);

			// Apagar ambos LEDs después de un tiempo
			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);

			// Establecer la nueva frecuencia para el LED2
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
El LED2 ubicado en la placa nucleo-F401RE comenzará a parpadear con una frecuencia de 100 ms. Cada vez que se presione el botón de la placa, la frecuencia cambiará a 500ms.
Se utiliza el módulo de uart para informar al usuario cuando se producen los flancos ascendente y descendente.
