################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/cli/cli.c \
../Core/Src/cli/key_handlers.c 

OBJS += \
./Core/Src/cli/cli.o \
./Core/Src/cli/key_handlers.o 

C_DEPS += \
./Core/Src/cli/cli.d \
./Core/Src/cli/key_handlers.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/cli/%.o Core/Src/cli/%.su Core/Src/cli/%.cyclo: ../Core/Src/cli/%.c Core/Src/cli/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-cli

clean-Core-2f-Src-2f-cli:
	-$(RM) ./Core/Src/cli/cli.cyclo ./Core/Src/cli/cli.d ./Core/Src/cli/cli.o ./Core/Src/cli/cli.su ./Core/Src/cli/key_handlers.cyclo ./Core/Src/cli/key_handlers.d ./Core/Src/cli/key_handlers.o ./Core/Src/cli/key_handlers.su

.PHONY: clean-Core-2f-Src-2f-cli

