/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the ATmega32 PWM driver
 *
 * Author: ABDULLAH KAMAL
 *
 *******************************************************************************/

#include <avr/io.h>
#include "pwm.h"
#include "Timer0_registers.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void PWM_Timer0_init (void)
{
	TCNT0 = 0; // Set Timer Initial Value to 0
	GPIO_setupPinDirection(PWM_OUTPUT_PORT_ID, PWM_OUTPUT_PIN_ID, PIN_OUTPUT); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.
	/* configure the timer
		 * 1. Fast PWM mode FOC0=0
		 * 2. Fast PWM Mode WGM01=1 & WGM00=1
		 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
		 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
    */
	TCCR0_REG.Bits.WGM00_bit=1;
	TCCR0_REG.Bits.WGM01_bit=1;
	TCCR0_REG.Bits.COM01_bit=1;
	TCCR0_REG.Bits.CS01_bit=1;
}

void PWM_Timer0_Start(uint8 duty_cycle)
{
	OCR0  = duty_cycle;


}
