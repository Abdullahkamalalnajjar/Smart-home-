/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: header file for the PWM driver
 *
 * Author: ABDULLAH KAMAL
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PWM_OUTPUT_PORT_ID     PORTB_ID
#define PWM_OUTPUT_PIN_ID      PIN3_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void PWM_Timer0_init (void);


void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
