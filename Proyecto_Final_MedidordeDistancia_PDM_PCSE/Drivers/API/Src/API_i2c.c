/// @file API_i2c.c
/// @version 1.0
/// @date 14/04/2024
/// @author Ing. Jorge Vasquez
/// @title API de manejo I2C
/// @brief funciones I2C.c

/* Includes ------------------------------------------------------------------*/
#include "API_i2c.h"
#include "API_Init.h"

I2C_HandleTypeDef hi2c1;

/* Definicion de Funciones --------------------------------------------------------*/
/**
 * @brief I2C Funcion de Inicializacion
 * @param None
 * @retval None
 */
void I2C1_Init(void) {

	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
		Error_Handler();
	}

}


