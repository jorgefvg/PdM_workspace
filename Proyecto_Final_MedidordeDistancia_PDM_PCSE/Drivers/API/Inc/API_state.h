
#ifndef API_INC_API_STATE_H_
#define API_INC_API_STATE_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include <stdio.h>

/* Exported types ------------------------------------------------------------*/
typedef char char_t; //Para cadena dist[6] que se usará en conversion de int a char
/* Exported types ------------------------------------------------------------*/
typedef uint16_t led_t;

/* Exported functions prototypes ---------------------------------------------*/
void LedOff_GPIO(led_t LED); //Apaga el led que se le indique
void Ledtoggle_GPIO(led_t LED); //Parpadeo del led que se le indique
distance_t API_distance(void); //Obtiene el valor de la distancia
void API_Initial(void); //Muestra en LCD mensaje de inicializacion
void API_Read_Measuring(void);//Muestra en LCD mensaje de estado lectura datos
void API_Write_LCD16X2(distance_t distance); //Muestra la medicion de la distancia por el LCD16x2
void API_Write_UART(distance_t distancia);// Muestra la medicion de la distancia por la UART

#endif /* API_INC_API_STATE_H_ */
