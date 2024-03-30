#ifndef API_UART_H
#define API_UART_H

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

bool uartInit();
void uartSendString(uint8_t *pstring);
void uartSendStringSize(uint8_t *pstring, uint16_t size);
void uartReceiveStringSize(uint8_t *pstring, uint16_t size);

#endif /* API_UART_H */
