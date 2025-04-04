################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/lexer/lexer.c 

OBJS += \
./Core/Src/lexer/lexer.o 

C_DEPS += \
./Core/Src/lexer/lexer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/lexer/%.o Core/Src/lexer/%.su Core/Src/lexer/%.cyclo: ../Core/Src/lexer/%.c Core/Src/lexer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-lexer

clean-Core-2f-Src-2f-lexer:
	-$(RM) ./Core/Src/lexer/lexer.cyclo ./Core/Src/lexer/lexer.d ./Core/Src/lexer/lexer.o ./Core/Src/lexer/lexer.su

.PHONY: clean-Core-2f-Src-2f-lexer

