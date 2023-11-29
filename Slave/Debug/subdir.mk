################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Slave.c \
../Timer0_registers.c \
../adc.c \
../adc_registers.c \
../dcmotor.c \
../external_eeprom.c \
../gpio.c \
../i2c.c \
../lm35_sensor.c \
../pwm.c \
../spi.c \
../test.c \
../timer1.c \
../uart.c 

OBJS += \
./Slave.o \
./Timer0_registers.o \
./adc.o \
./adc_registers.o \
./dcmotor.o \
./external_eeprom.o \
./gpio.o \
./i2c.o \
./lm35_sensor.o \
./pwm.o \
./spi.o \
./test.o \
./timer1.o \
./uart.o 

C_DEPS += \
./Slave.d \
./Timer0_registers.d \
./adc.d \
./adc_registers.d \
./dcmotor.d \
./external_eeprom.d \
./gpio.d \
./i2c.d \
./lm35_sensor.d \
./pwm.d \
./spi.d \
./test.d \
./timer1.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


