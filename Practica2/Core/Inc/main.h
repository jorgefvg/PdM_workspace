
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include <stdint.h> // Biblioteca estándar para tipos de datos (stdint.h)
#include <stdbool.h> // Biblioteca estándar para tipos booleanos (stdbool.h)


typedef uint32_t tick_t; // Tipo de dato para almacenar el tiempo, redefino un tipo de dato entero sin signo de 32 bits de nombre tick_t
typedef bool bool_t; // Tipo de dato booleano, ya se true o false

typedef struct {
   tick_t startTime; // Marca de tiempo inicial
   tick_t duration; // Duración del retardo
   bool_t running; // Estado del retardo (en ejecución o no)
} delay_t;

void Error_Handler(void);

/**
  * @brief Inicializa el retardo con la duración especificada.
  * @param delay: Puntero a la estructura de retardo.
  * @param duration: Duración del retardo en milisegundos.
  */
void delayInit(delay_t* delay, tick_t duration);

/**
  * @brief Verifica el estado del retardo.
  * @param delay: Puntero a la estructura de retardo.
  * @return Estado del retardo (true si el retardo se ha completado, false en caso contrario).
  */
bool_t delayRead(delay_t* delay);

/**
  * @brief Cambia la duración del retardo existente.
  * @param delay: Puntero a la estructura de retardo.
  * @param duration: Nueva duración del retardo en milisegundos.
  */
void delayWrite(delay_t* delay, tick_t duration);

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

#define LED2_TIME 100


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
