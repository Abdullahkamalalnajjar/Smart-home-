 /******************************************************************************
 * File Name: TIMER0_registers.h
 *
 * Description: DEFINATION  TIMER0 REGISTERS
 *
 * Author: ABDUALLAH Al-Najjar
 *
 *******************************************************************************/

#ifndef TIMER0_REGISTERS_H_
#define TIMER0_REGISTERS_H_

#include "Timer0_registers.c"

#define TCCR0_REG (*(volatile TCCR0_Reg_type*)0x53)

#define TIMSK_REG (*(volatile TIMSK_Reg_type*)0x59)



#endif /* TIMER0_REGISTERS_H_ */
