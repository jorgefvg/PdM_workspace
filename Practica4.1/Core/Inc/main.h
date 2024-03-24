#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"       // Contiene las definiciones y funciones específicas del microcontrolador STM32F4
#include "stm32f4xx_hal_gpio.h"
#include "API_delay.h"

/* Estado del modelo */
typedef enum {
	BUTTON_UP,      // Botón suelto
	BUTTON_FALLING, // Apretando botón
	BUTTON_DOWN,    // Boton precionado
	BUTTON_RAISING, // Soltando botón
} debounceState_t;

void Error_Handler(void);

/* Definiciones privadas */
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOA
#define LD3_Pin GPIO_PIN_1
#define LD3_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* Private function prototypes */
void debounceFSM_init(debounceState_t *currentState, debounceState_t initialValue);// debe cargar el estado inicial
void debounceFSM_update(debounceState_t *currentState, delay_t *delay);// debe leer las entradas, resolver la lógica
                                                                       // de transición de estados y actualizar las salidas
void buttonPressed(void);// debe encender el LED1 (Led Color Blanco)
void buttonReleased(void);// debe apagar el LED3 (Led Color Azul)

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
