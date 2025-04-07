################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/pex/pex.c 

OBJS += \
./Core/Src/pex/pex.o 

C_DEPS += \
./Core/Src/pex/pex.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/pex/%.o Core/Src/pex/%.su Core/Src/pex/%.cyclo: ../Core/Src/pex/%.c Core/Src/pex/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-pex

clean-Core-2f-Src-2f-pex:
	-$(RM) ./Core/Src/pex/pex.cyclo ./Core/Src/pex/pex.d ./Core/Src/pex/pex.o ./Core/Src/pex/pex.su

.PHONY: clean-Core-2f-Src-2f-pex

