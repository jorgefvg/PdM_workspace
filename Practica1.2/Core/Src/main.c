
#include "main.h"
#include "SysConfig.h"
#include "Gpio.h"

int main(void)
{
	HAL_Init(); //Inicializando la libreria hal
	SysConfigClock();
	Gpio_Led_Init();
	Gpio_But_Init();
	while(1)
	{
		if(Gpio_But_Read() == HIGH)
		{
			Gpio_Led_Write(HIGH);
			HAL_Delay(200);
			Gpio_Led_Write(LOW);
			HAL_Delay(200);
			Gpio_Led2_Write(HIGH);
			HAL_Delay(200);
			Gpio_Led2_Write(LOW);
			HAL_Delay(200);
			Gpio_Led3_Write(HIGH);
			HAL_Delay(200);
			Gpio_Led3_Write(LOW);
			HAL_Delay(200);
		}
		else
		{
			Gpio_Led_Write(HIGH);
			HAL_Delay(200);
			Gpio_Led_Write(LOW);
			HAL_Delay(200);
			Gpio_Led3_Write(HIGH);
			HAL_Delay(200);
			Gpio_Led3_Write(LOW);
			HAL_Delay(200);
			Gpio_Led2_Write(HIGH);
			HAL_Delay(200);
			Gpio_Led2_Write(LOW);
			HAL_Delay(200);
		 }
	}
	return 0;
}
