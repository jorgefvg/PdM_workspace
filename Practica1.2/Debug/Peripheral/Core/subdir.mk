################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripheral/Core/Gpio.c \
../Peripheral/Core/SysConfig.c 

OBJS += \
./Peripheral/Core/Gpio.o \
./Peripheral/Core/SysConfig.o 

C_DEPS += \
./Peripheral/Core/Gpio.d \
./Peripheral/Core/SysConfig.d 


# Each subdirectory must supply rules for building sources it contributes
Peripheral/Core/%.o Peripheral/Core/%.su Peripheral/Core/%.cyclo: ../Peripheral/Core/%.c Peripheral/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I"/home/jv/STM32CubeIDE/workspace_1.14.0/PdM_workspace/PdM_workspace/Practica1.2/Peripheral/Inc" -I"/home/jv/STM32CubeIDE/workspace_1.14.0/PdM_workspace/PdM_workspace/Practica1.2/Core/Inc" -I"/home/jv/STM32CubeIDE/workspace_1.14.0/PdM_workspace/PdM_workspace/Practica1.2/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/jv/STM32CubeIDE/workspace_1.14.0/PdM_workspace/PdM_workspace/Practica1.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/home/jv/STM32CubeIDE/workspace_1.14.0/PdM_workspace/PdM_workspace/Practica1.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/jv/STM32CubeIDE/workspace_1.14.0/PdM_workspace/PdM_workspace/Practica1.2/Drivers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Peripheral-2f-Core

clean-Peripheral-2f-Core:
	-$(RM) ./Peripheral/Core/Gpio.cyclo ./Peripheral/Core/Gpio.d ./Peripheral/Core/Gpio.o ./Peripheral/Core/Gpio.su ./Peripheral/Core/SysConfig.cyclo ./Peripheral/Core/SysConfig.d ./Peripheral/Core/SysConfig.o ./Peripheral/Core/SysConfig.su

.PHONY: clean-Peripheral-2f-Core

