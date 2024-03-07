
#include "main.h"
#include "SysConfig.h"
#include "Gpio.h"

int main(void)
{
	HAL_Init(); //Inicializando la libreria hal
	SysConfigClock();
	Gpio_Led_Init();
	while(1)
	{
		//Gpio_Led_Toggle();//Probando Toggle
		//HAL_Delay(100);//Cada 100ms se enciende el led
		Gpio_Led_Write(HIGH); //Probando ed Debuger
		HAL_Delay(200);
		Gpio_Led_Write(LOW);
		HAL_Delay(200);
		Gpio_Led2_Write(HIGH);//Probando ed Debuger
		HAL_Delay(200);
		Gpio_Led2_Write(LOW);
		HAL_Delay(200);
		Gpio_Led3_Write(HIGH); //Probando ed Debuger
		HAL_Delay(200);
		Gpio_Led3_Write(LOW);
		HAL_Delay(200);

	}
}
