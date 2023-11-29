################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Master.c \
../gpio.c \
../keypad.c \
../lcd.c \
../spi.c \
../test.c \
../timer1.c \
../timer_driver.c \
../uart.c 

OBJS += \
./Master.o \
./gpio.o \
./keypad.o \
./lcd.o \
./spi.o \
./test.o \
./timer1.o \
./timer_driver.o \
./uart.o 

C_DEPS += \
./Master.d \
./gpio.d \
./keypad.d \
./lcd.d \
./spi.d \
./test.d \
./timer1.d \
./timer_driver.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


