#include "main.h"

//Led1 externo (color blanco) ubicado en el pin0 GPIOA
//Led2 (color verde) es el unico que trae la placa ubicado en el pin5 GPIOA
//Led3 externo (color azul) ubicado en el pin1 GPIOA

/* Inclusiones privadas -------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* Variables privadas ---------------------------------------------------------*/
delay_t ledDelay; // Retardo no bloqueante para los LEDs
UART_HandleTypeDef huart2;

/* Prototipos de funciones privadas -----------------------------------------------*/

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void Error_Handler(void);
/**
 * @brief  Punto de entrada de la aplicación.
 * @retval int
 */

int main(void) {
	/* Configuración del MCU */
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

/* Inicializando la máquina de estados debounce */
void debounceFSM_init(debounceState_t *currentState, debounceState_t initialValue)
{
	// Se establece el estado inicial de la MEF
	*currentState = initialValue;
}

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

/* Maneja el evento de botón presionado */
void buttonPressed(void)
{
	HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
}
/* Maneja el evento de botón soltado */
void buttonReleased(void)
{
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
}


/* Configuración del sistema de reloj */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configurar la tensión de salida del regulador interno principal
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	/** Inicializar los osciladores RCC según los parámetros especificados
	 * en la estructura RCC_OscInitStruct.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 16;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Inicializar los relojes de la CPU, AHB y APB
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

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
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, LD1_Pin | LD3_Pin | LD2_Pin, GPIO_PIN_RESET);

	/*Cofigure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : L1,L2,L3_Pin */
	GPIO_InitStruct.Pin = LD1_Pin | LD3_Pin | LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {

	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */
