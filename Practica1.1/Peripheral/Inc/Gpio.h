/*
 * Gpio.h
 *
 *  Created on: Mar 5, 2024
 *      Author: jv
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"

typedef enum
{
	LOW, //LOW = 0
	HIGH //HIGH = 1
}gpio_state;

void Gpio_Led_Init(void);//Funcion para inicializar mi led, la placa solo posee un led
//Para que mi led se encienda y se apague creo las siguientes funciones
void Gpio_Led_Write(gpio_state state);//Escritura, Al llamar la funcioo Led_Write y mando un HIGH enciendo p un LOW apaga
void Gpio_Led2_Write(gpio_state state);
void Gpio_Led3_Write(gpio_state state);

//void Gpio_Led_Toggle(void);//encender y apagar


#endif /* INC_GPIO_H_ */
