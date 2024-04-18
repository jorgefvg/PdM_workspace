
#ifndef API_INC_API_LCD_PORT_H_
#define API_INC_API_LCD_PORT_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include <stdio.h>

/* Exported functions prototypes ---------------------------------------------*/
void I2C_transmitir_cmd(uint16_t direccion, uint8_t *data_t, uint8_t tamano, uint8_t tiempo_espera);
void I2C_transmitir_data(uint16_t direccion, uint8_t *data_t, uint8_t tamano, uint8_t tiempo_espera);

#endif /* API_INC_API_LCD_PORT_H_ */
