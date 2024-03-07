/*
 * SysConfig.c
 *
 *  Created on: Mar 5, 2024
 *      Author: jv
 */

#include "SysConfig.h"

bool SysConfigClock(void)
{
	RCC_OscInitTypeDef oscInit = {0};
	RCC_ClkInitTypeDef clkInit = {0};

	oscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE; //tipo de oscilador externo H
	oscInit.HSEState = RCC_HSE_ON; //Habilito el oscilador externo, lo enciendo
	oscInit.PLL.PLLSource = RCC_PLLSOURCE_HSE; //Indicamos la fuente en el PLL y utilizamos la fuente externa
	oscInit.PLL.PLLState = RCC_PLL_ON; //Habilito la fuente externa del PLL
	oscInit.PLL.PLLM = 4; //colocamos el valor de M que es 4, el de N=84, P=2, Q=7. ver en archivo.ioc
	oscInit.PLL.PLLN = 84;
	oscInit.PLL.PLLP = RCC_PLLP_DIV2; //aqui sera 2 pero ya existe un macro que hace la division
	oscInit.PLL.PLLQ = 7;
	//por el momento tengo solo los parametros, ahora le pido al HAL que me los configure
	//oscilador con su dirreccion, la estructura que cree oscInit
	if(HAL_RCC_OscConfig(&oscInit) != HAL_OK)
	{
		return false;
	}

	clkInit.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
			            RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2; //configuramos todo los tipos de clock
	clkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; //Vamos a utilizar el PLL como la fuente
	clkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkInit.APB1CLKDivider = RCC_HCLK_DIV2;
	clkInit.APB2CLKDivider = RCC_HCLK_DIV1;

	//pedimos que me lo configure el hall, y el valor de latency segun el datashet es 2 para frecuencia de 84 MHZ
	if(HAL_RCC_ClockConfig(&clkInit, FLASH_LATENCY_2) != HAL_OK)
	{
		return false;
	}
	return true;
}



