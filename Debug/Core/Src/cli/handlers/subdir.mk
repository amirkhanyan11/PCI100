################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/cli/handlers/handlers.c 

OBJS += \
./Core/Src/cli/handlers/handlers.o 

C_DEPS += \
./Core/Src/cli/handlers/handlers.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/cli/handlers/%.o Core/Src/cli/handlers/%.su Core/Src/cli/handlers/%.cyclo: ../Core/Src/cli/handlers/%.c Core/Src/cli/handlers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-cli-2f-handlers

clean-Core-2f-Src-2f-cli-2f-handlers:
	-$(RM) ./Core/Src/cli/handlers/handlers.cyclo ./Core/Src/cli/handlers/handlers.d ./Core/Src/cli/handlers/handlers.o ./Core/Src/cli/handlers/handlers.su

.PHONY: clean-Core-2f-Src-2f-cli-2f-handlers

