
#ifndef API_INC_API_HCSR04_H_
#define API_INC_API_HCSR04_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include <stdio.h>

/* Exported types ------------------------------------------------------------*/
typedef int distance_t; //para la variable distancia

/* Exported functions prototypes ---------------------------------------------*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim); //Calcula el ancho de pulso del pin ECHO
distance_t API_HCSR04_Measure(void); //Mide la distancia al objeto

#endif /* API_INC_API_HCSR04_H_ */
