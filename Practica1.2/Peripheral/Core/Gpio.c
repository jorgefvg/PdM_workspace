/*
 * Gpio.c
 *
 *  Created on: Mar 5, 2024
 *      Author: jv
 */
#include "Gpio.h"

void Gpio_Led_Init(void)
{
	//PA5 Pin donde se encuentra el led en la placa , usare entonces el GPIOA
	//Para utilizar los GPIO o un periferico es necesario activar un reloj
	GPIO_InitTypeDef gpioInit = {0};//Agrego la estructura tal como lo hice en SysConfig,

	__HAL_RCC_GPIOA_CLK_ENABLE();//Macro que me permite habilitar el reloj del GPIOA

	gpioInit.Pin = GPIO_PIN_5 | GPIO_PIN_0 |GPIO_PIN_1; //Pin 5, 0 ,1 somo salida
	gpioInit.Mode = GPIO_MODE_OUTPUT_PP;//El modo en que trabajara el led sera Push-pull
	gpioInit.Pull = GPIO_NOPULL;//No utilizare pull-up o pulldown, en la placa tengo GPIOA, B ,C ,D ,H, cada uno con 16 pines y se pueden usar como pull-up o down interno.
	gpioInit.Speed = GPIO_SPEED_FREQ_LOW;//El cambio entre cero y uno sera baja

	HAL_GPIO_Init(GPIOA, &gpioInit);//me pide el puerto y la dirreccion de la estructura, para que hal me haga la configuracion

}

void Gpio_Led_Write(gpio_state state)
{
	if(state == HIGH)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); //GPIO_PIN_SET me coloca un 1 al pin
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); //Si mande un LOW se apaga
	}
}

void Gpio_Led2_Write(gpio_state state)
{
	if(state == HIGH)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET); //GPIO_PIN_SET me coloca un 1 al pin
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET); //Si mande un LOW se apaga
	}
}

void Gpio_Led3_Write(gpio_state state)
{
	if(state == HIGH)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); //GPIO_PIN_SET me coloca un 1 al pin
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); //Si mande un LOW se apaga
	}
}

/*void Gpio_Led_Toggle(void)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);//Esta funcion cada vez que la llamo me enciende y apaga el led
}
*/
//Configurando el pulsador
void Gpio_But_Init(void)
{
	//El boton se encuentra en el PC13 de la placa nucleo. se encuentra a tierra pero cambiare esto
	GPIO_InitTypeDef gpioInit = {0};//Agrego la estructura tal como lo hice en SysConfig,

	__HAL_RCC_GPIOC_CLK_ENABLE();//Macro que me permite habilitar el reloj del GPIOC

	gpioInit.Pin = GPIO_PIN_13; //Pin 13
	gpioInit.Mode = GPIO_MODE_INPUT;//El modo de entrada para leer la informacion
	gpioInit.Pull = GPIO_PULLUP; //Habilito la Pullup interna, como el pin esta a cero, con un PULLUP siempre el pin estara en 1 y al precionarlo cambia a 0
	gpioInit.Speed = GPIO_SPEED_FREQ_LOW;//El cambio entre cero y uno sera baja

	HAL_GPIO_Init(GPIOC, &gpioInit);
}

gpio_state Gpio_But_Read(void)
{
	return (bool)HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
}
