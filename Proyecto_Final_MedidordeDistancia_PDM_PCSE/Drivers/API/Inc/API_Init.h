
#ifndef API_INC_API_INIT_H_
#define API_INC_API_INIT_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include <stdio.h>

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void assert_failed(uint8_t *file, uint32_t line);
void SystemClock_Config(void);


#endif /* API_INC_API_INIT_H_ */
