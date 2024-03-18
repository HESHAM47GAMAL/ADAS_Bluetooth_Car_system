################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/TIMER1/TIMER1_config.c \
../MCAL/TIMER1/TIMER1_program.c 

OBJS += \
./MCAL/TIMER1/TIMER1_config.o \
./MCAL/TIMER1/TIMER1_program.o 

C_DEPS += \
./MCAL/TIMER1/TIMER1_config.d \
./MCAL/TIMER1/TIMER1_program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/TIMER1/%.o: ../MCAL/TIMER1/%.c MCAL/TIMER1/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


