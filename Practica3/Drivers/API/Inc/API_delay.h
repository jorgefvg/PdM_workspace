#ifndef API_DELAY_H
#define API_DELAY_H

#include <stdint.h> // Para incluir el tipo uint32_t
#include <stdbool.h> // Para incluir el tipo bool_t

typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct {
	tick_t startTime; // Marca de tiempo inicial
	tick_t duration; // Duración del retardo
	bool_t running; // Estado del retardo (en ejecución o no)
} delay_t;        // Estructura para representar un retardo

void delayInit(delay_t *delay, tick_t duration); // Inicializa la estructura de retardo con la duración especificada
bool_t delayRead(delay_t *delay); // Lee el estado del retardo y devuelve true si el retardo ha terminado,
//si no ha terminado devuelve false
void delayWrite(delay_t *delay, tick_t duration); // Actualiza la duración del retardo con el valor especificado

#endif // API_DELAY_H
