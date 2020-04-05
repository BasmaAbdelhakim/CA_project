################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../05-OS/SCHEDULER_config.c \
../05-OS/SCHEDULER_program.c 

OBJS += \
./05-OS/SCHEDULER_config.o \
./05-OS/SCHEDULER_program.o 

C_DEPS += \
./05-OS/SCHEDULER_config.d \
./05-OS/SCHEDULER_program.d 


# Each subdirectory must supply rules for building sources it contributes
05-OS/%.o: ../05-OS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DNDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

