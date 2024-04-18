/// @file API_uart.c
/// @version 1.0
/// @date 14/04/2024
/// @author Ing. Jorge Vasquez
/// @title API de inicializacion de la uart
/// @brief funciones de inicializacion de la uart

/* Includes ------------------------------------------------------------------*/
#include "API_uart.h"
#include "API_Init.h"

extern UART_HandleTypeDef huart2;

/* Definicion de Funciones --------------------------------------------------------*/
/**
 * @brief USART2 Funcion de Inicializacion
 * @param None
 * @retval None
 */
bool uart_Init() {

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */
	// Imprimir por la terminal serie un mensaje de que se a inicializado la uart
	uint8_t msg[] = "Iniciando UART\r\n";
	HAL_UART_Transmit(&huart2, msg, sizeof(msg), HAL_MAX_DELAY);

	return true;
	/* USER CODE END USART2_Init 2 */

}

