 /******************************************************************************
 * File Name: adc_registers.c
 *
 * Description: DEFINATION  ADC REGISTERS
 *
 * Author: ABDUALLAH Al-Najjar
 *
 *******************************************************************************/
#include "std_types.h"

typedef union {
	uint8 Bytes;
	 struct{

		 uint8 MUX0_bit:1;
		 uint8 MUX1_bit:1;
		 uint8 MUX2_bit:1;
		 uint8 MUX3_bit:1;
		 uint8 MUX4_bit:1;
		 uint8 ADLAR_bit:1;
		 uint8 REFS0_bit:1;
	     uint8 REFS1_bit:1;

	}Bits;

}ADMUX_Reg_type;

typedef union {
	uint8 Bytes;
	 struct{

		 uint8 ADPS0_bit:1;
		 uint8 ADPS1_bit:1;
		 uint8 ADPS2_bit:1;
		 uint8 ADIE_bit:1;
		 uint8 ADIF_bit:1;
		 uint8 ADATE_bit:1;
		 uint8 ADSC_bit:1;
	     uint8 ADEN_bit:1;

	}Bits;

}ADCSRA_Reg_type;
