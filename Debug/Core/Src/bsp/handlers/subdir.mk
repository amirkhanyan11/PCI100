################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/bsp/handlers/handlers.c 

OBJS += \
./Core/Src/bsp/handlers/handlers.o 

C_DEPS += \
./Core/Src/bsp/handlers/handlers.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/bsp/handlers/%.o Core/Src/bsp/handlers/%.su Core/Src/bsp/handlers/%.cyclo: ../Core/Src/bsp/handlers/%.c Core/Src/bsp/handlers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-bsp-2f-handlers

clean-Core-2f-Src-2f-bsp-2f-handlers:
	-$(RM) ./Core/Src/bsp/handlers/handlers.cyclo ./Core/Src/bsp/handlers/handlers.d ./Core/Src/bsp/handlers/handlers.o ./Core/Src/bsp/handlers/handlers.su

.PHONY: clean-Core-2f-Src-2f-bsp-2f-handlers

