
#include "main.h"
#include "API_debounce.h"
#include "API_delay.h"
#include "API_uart.h"

//Led1 externo (color blanco) ubicado en el pin0 GPIOA
//Led2 (color verde) es el unico que trae la placa ubicado en el pin5 GPIOA
//Led3 externo (color azul) ubicado en el pin1 GPIOA

/* Inclusiones privadas -------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* Variables privadas ---------------------------------------------------------*/
static delay_t ledDelay;                   // Retardo no bloqueante para los LEDs
static debounceState_t state;              // Estado actual de la MEF Anti-Rebote

/* Prototipos de funciones privadas -----------------------------------------------*/

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/**
 * @brief  Punto de entrada de la aplicación.
 * @retval int
 */

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
