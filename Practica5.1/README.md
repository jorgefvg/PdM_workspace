## Practica 5.1
### Objetivo:
Implementar un módulo de software sencillo para trabajar con la UART. 


https://github.com/jorgefvg/PdM_workspace/assets/161152623/f23dbd91-aee0-4129-a3d0-2fe5f4491b10


### Punto 1:
1. Implementar un módulo de software en un archivos fuente API_uart.c con su correspondiente archivo de cabecera API_uart.h y ubicarlos en el proyecto dentro de  las carpetas /drivers/API/src y /drivers/API/inc, respectivamente.
2. En API_uart.h se deben ubicar los prototipos de las funciones públicas.
```javascript
bool_t uartInit();
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);
```
3. En API_uart.c se deben ubicar los prototipos de las funciones privadas y la implementación de todas las funciones de módulo, privadas y públicas.
uartInit() inicializa la UART.  Adicionalmente, imprime por la terminal serie un mensaje con sus parámetros de configuración.
La función devuelve:
true: si la inicialización es exitosa.
false: si la inicialización no es exitosa.
```javascript
bool uartInit() {
	// Inicialización del periférico UART
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;

	if (HAL_UART_Init(&huart2) != HAL_OK) {
		// Si la inicialización falla, devolvemos false
		return false;
	}

	// Imprimir por la terminal serie un mensaje con los parámetros de configuración
	uint8_t msg[] = "Iniciando UART\r\n";
	HAL_UART_Transmit(&huart2, msg, sizeof(msg), HAL_MAX_DELAY);

	return true;
}
```
uartSendString(uint8_t *pstring) recibe un puntero a un string que se desea enviar por la UART completo (hasta el caracter ‘\0’) y utiliza la función de la HAL, HAL_UART_Transmit(...) para transmitir el string.
```javascript
void uartSendString(uint8_t *pstring) {
	// Utilizar la función HAL para transmitir el string completo
	HAL_UART_Transmit(&huart2, pstring, strlen((const char *)pstring), HAL_MAX_DELAY);
}
```
uartSendStringSize(uint8_t * pstring, uint16_t size) recibe un puntero a un string que se desea enviar por la UART y un entero con la cantidad de caracteres que debe enviar. La función utiliza HAL_UART_Transmit(...) para transmitir el string.
```javascript
void uartSendStringSize(uint8_t *pstring, uint16_t size) {
	// Utilizar la función HAL para transmitir el string con el tamaño especificado
	HAL_UART_Transmit(&huart2, pstring, size, HAL_MAX_DELAY);
}
```
uartReceiveStringSize(uint8_t * pstring, uint16_t size); Utiliza la función HAL para recibir datos por la UART.
```javascript
void uartReceiveStringSize(uint8_t *pstring, uint16_t size) {
	// Utilizar la función HAL para recibir datos por la UART
	HAL_UART_Receive(&huart2, pstring, size, HAL_MAX_DELAY);
}
```
### main.c
Acontinuacion se muestra parte del codigo que se implemento:
```javascript
int main(void) {
	/* Configuración del MCU */
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();

	// Inicializar la UART
	if (!uartInit()) {
		// En caso de que la inicialización falle, parpadea el LED de la placa para indicar que hay un problema con la UART
		while (1) {
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			HAL_Delay(500);
		}
	}

	uint8_t txBuffer[] = "Hola UART\r\n";
	uint8_t rxBuffer[20];

	/* Infinite loop */
	while (1)
	{

		// Enviar un mensaje por la UART
		uartSendString(txBuffer);

		// Recibir datos por la UART
		uartReceiveStringSize(rxBuffer, sizeof(rxBuffer));

		// Esperar un tiempo antes de repetir el envío y la recepción
		HAL_Delay(1000);

	}
}
```
