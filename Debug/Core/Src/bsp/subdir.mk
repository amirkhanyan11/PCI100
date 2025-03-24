################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/bsp/bsp.c \
../Core/Src/bsp/help.c 

OBJS += \
./Core/Src/bsp/bsp.o \
./Core/Src/bsp/help.o 

C_DEPS += \
./Core/Src/bsp/bsp.d \
./Core/Src/bsp/help.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/bsp/%.o Core/Src/bsp/%.su Core/Src/bsp/%.cyclo: ../Core/Src/bsp/%.c Core/Src/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-bsp

clean-Core-2f-Src-2f-bsp:
	-$(RM) ./Core/Src/bsp/bsp.cyclo ./Core/Src/bsp/bsp.d ./Core/Src/bsp/bsp.o ./Core/Src/bsp/bsp.su ./Core/Src/bsp/help.cyclo ./Core/Src/bsp/help.d ./Core/Src/bsp/help.o ./Core/Src/bsp/help.su

.PHONY: clean-Core-2f-Src-2f-bsp

