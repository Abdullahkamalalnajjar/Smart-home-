
 /******************************************************************************
 * File Name: Timer0_registers.c
 *
 * Description: DEFINATION  TIMER0 REGISTERS
 *
 * Author: ABDUALLAH Al-Najjar
 *
 *******************************************************************************/

#include "std_types.h"

typedef union {
	uint8 Bytes;
	 struct{

		 uint8 CS00_bit:1;
		 uint8 CS01_bit:1;
		 uint8 CS02_bit:1;
		 uint8 WGM01_bit:1;
		 uint8 COM00_bit:1;
		 uint8 COM01_bit:1;
		 uint8 WGM00_bit:1;
	     uint8 FOC0_bit:1;

	}Bits;

}TCCR0_Reg_type;

typedef union {
	uint8 Bytes;
	 struct{

		 uint8 TOIE0_bit:1;
		 uint8 OCIE0_bit:1;
		 uint8 TOIE1_bit:1;
		 uint8 OCIE1B_bit:1;
		 uint8 OCIE1A_bit:1;
		 uint8 TICIE1_bit:1;
		 uint8 TOIE2_bit:1;
	     uint8 OCIE2_bit:1;

	}Bits;

}TIMSK_Reg_type;
