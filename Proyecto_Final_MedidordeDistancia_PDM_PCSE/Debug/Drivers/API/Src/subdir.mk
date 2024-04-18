################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/API_HCSR04.c \
../Drivers/API/Src/API_Init.c \
../Drivers/API/Src/API_delay.c \
../Drivers/API/Src/API_gpio.c \
../Drivers/API/Src/API_i2c.c \
../Drivers/API/Src/API_lcd.c \
../Drivers/API/Src/API_lcd_port.c \
../Drivers/API/Src/API_state.c \
../Drivers/API/Src/API_timer.c \
../Drivers/API/Src/API_uart.c 

OBJS += \
./Drivers/API/Src/API_HCSR04.o \
./Drivers/API/Src/API_Init.o \
./Drivers/API/Src/API_delay.o \
./Drivers/API/Src/API_gpio.o \
./Drivers/API/Src/API_i2c.o \
./Drivers/API/Src/API_lcd.o \
./Drivers/API/Src/API_lcd_port.o \
./Drivers/API/Src/API_state.o \
./Drivers/API/Src/API_timer.o \
./Drivers/API/Src/API_uart.o 

C_DEPS += \
./Drivers/API/Src/API_HCSR04.d \
./Drivers/API/Src/API_Init.d \
./Drivers/API/Src/API_delay.d \
./Drivers/API/Src/API_gpio.d \
./Drivers/API/Src/API_i2c.d \
./Drivers/API/Src/API_lcd.d \
./Drivers/API/Src/API_lcd_port.d \
./Drivers/API/Src/API_state.d \
./Drivers/API/Src/API_timer.d \
./Drivers/API/Src/API_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su Drivers/API/Src/%.cyclo: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/jv/Pruebas/Proyecto_Final_MedidordeDistancia_PDM_PCSE/Drivers/API" -I"/home/jv/Pruebas/Proyecto_Final_MedidordeDistancia_PDM_PCSE/Drivers/API/Inc" -I"/home/jv/Pruebas/Proyecto_Final_MedidordeDistancia_PDM_PCSE/Drivers/API/Src" -I"/home/jv/Pruebas/Proyecto_Final_MedidordeDistancia_PDM_PCSE/Drivers" -I"/home/jv/Pruebas/Proyecto_Final_MedidordeDistancia_PDM_PCSE/Core/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/API_HCSR04.cyclo ./Drivers/API/Src/API_HCSR04.d ./Drivers/API/Src/API_HCSR04.o ./Drivers/API/Src/API_HCSR04.su ./Drivers/API/Src/API_Init.cyclo ./Drivers/API/Src/API_Init.d ./Drivers/API/Src/API_Init.o ./Drivers/API/Src/API_Init.su ./Drivers/API/Src/API_delay.cyclo ./Drivers/API/Src/API_delay.d ./Drivers/API/Src/API_delay.o ./Drivers/API/Src/API_delay.su ./Drivers/API/Src/API_gpio.cyclo ./Drivers/API/Src/API_gpio.d ./Drivers/API/Src/API_gpio.o ./Drivers/API/Src/API_gpio.su ./Drivers/API/Src/API_i2c.cyclo ./Drivers/API/Src/API_i2c.d ./Drivers/API/Src/API_i2c.o ./Drivers/API/Src/API_i2c.su ./Drivers/API/Src/API_lcd.cyclo ./Drivers/API/Src/API_lcd.d ./Drivers/API/Src/API_lcd.o ./Drivers/API/Src/API_lcd.su ./Drivers/API/Src/API_lcd_port.cyclo ./Drivers/API/Src/API_lcd_port.d ./Drivers/API/Src/API_lcd_port.o ./Drivers/API/Src/API_lcd_port.su ./Drivers/API/Src/API_state.cyclo ./Drivers/API/Src/API_state.d ./Drivers/API/Src/API_state.o ./Drivers/API/Src/API_state.su ./Drivers/API/Src/API_timer.cyclo ./Drivers/API/Src/API_timer.d ./Drivers/API/Src/API_timer.o ./Drivers/API/Src/API_timer.su ./Drivers/API/Src/API_uart.cyclo ./Drivers/API/Src/API_uart.d ./Drivers/API/Src/API_uart.o ./Drivers/API/Src/API_uart.su

.PHONY: clean-Drivers-2f-API-2f-Src

