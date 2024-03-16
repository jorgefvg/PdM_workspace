
#include "main.h"
#include "API_delay.h"
//Led1 externo (color blanco) ubicado en el pin0 GPIOA
//Led2 (color verde) es el unico que trae la placa ubicado en el pin5 GPIOA
//Led3 externo (color azul) ubicado en el pin1 GPIOA

/* Inclusiones privadas -------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* Variables privadas ---------------------------------------------------------*/
GPIO_TypeDef* LD_GPIO_Port[3] = {LD1_GPIO_Port, LD2_GPIO_Port, LD3_GPIO_Port};
uint16_t LD_Pin[3] = {LD1_Pin, LD2_Pin, LD3_Pin};
delay_t ledDelay; // Retardo no bloqueante para los LEDs
UART_HandleTypeDef huart2;


/* Prototipos de funciones privadas -----------------------------------------------*/

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void Toggle_LED_Sequence(uint8_t sequenceIndex);
static void MX_USART2_UART_Init(void);

/**
 * @brief  Punto de entrada de la aplicación.
 * @retval int
 */

int main(void)
{
	/* Configuración del MCU */
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	uint8_t sequenceIndex = 0; // Variable para controlar el índice de la secuencia de LEDs
	delayInit(&ledDelay, LED_TIME); // Inicializar el retardo no bloqueante para los LEDs con una duración de 200 ms

	/* Bucle infinito */
	while (1)
	{

		// Verificar si el pulsador ha sido presionado
		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
		{
			HAL_Delay(50);
			if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
			{
				sequenceIndex++;
				if (sequenceIndex >= 6)
				{
					sequenceIndex = 0;
				}
				while (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
				{
					// Esperar a que se suelte el pulsador
				}
			}
		}
		// Llamar a la función para alternar la secuencia de los LEDs
		Toggle_LED_Sequence(sequenceIndex);

	}
}

// Función para alternar la secuencia de los LEDs
void Toggle_LED_Sequence(uint8_t sequenceIndex)
{
	const uint8_t sequences[6][3] = {
			{1, 2, 3},  // Secuencia 1: LED1, LED2, LED3
			{1, 3, 2},  // Secuencia 2: LED1, LED3, LED2
			{2, 1, 3},  // Secuencia 3: LED2, LED1, LED3
			{2, 3, 1},  // Secuencia 4: LED2, LED3, LED1
			{3, 2, 1},  // Secuencia 5: LED3, LED2, LED1
			{3, 1, 2}   // Secuencia 6: LED3, LED1, LED2
	};

	const uint8_t* sequence = sequences[sequenceIndex];

	for (int i = 0; i < 3; i++) {
		uint8_t led = sequence[i];
		HAL_GPIO_WritePin(LD_GPIO_Port[led - 1], LD_Pin[led - 1], GPIO_PIN_SET);
		delayWrite(&ledDelay, LED_TIME); // Iniciar el retardo no bloqueante para mantener el LED encendido durante 200 ms
		while (!delayRead(&ledDelay)) {
			// Esperar hasta que el retardo no bloqueante haya finalizado
		}
		HAL_GPIO_WritePin(LD_GPIO_Port[led - 1], LD_Pin[led - 1], GPIO_PIN_RESET);
		delayWrite(&ledDelay, LED_TIME); // Iniciar el retardo no bloqueante para mantener el LED apagado durante 200 ms
		while (!delayRead(&ledDelay)) {
			// Esperar hasta que el retardo no bloqueante haya finalizado
		}
	}
}


/* Configuración del sistema de reloj */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Inicializar los relojes de la CPU, AHB y APB
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void)
{

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

	/*Cofigure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : L2_Pin */
	GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{

	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */
