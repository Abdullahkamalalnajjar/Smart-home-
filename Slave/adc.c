 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega32 ADC driver
 *
 * Author: ABDUALLAH KAMAL
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "adc_registers.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init( const ADC_ConfigType * Config_Ptr)
{
	ADMUX_REG.Bytes=  (((Config_Ptr->volt_ref) )<<6);
	ADMUX_REG.Bytes &= 0xE0;     /*SET FIRST 5 BIT ZEROS*/
	ADCSRA_REG.Bits.ADEN_bit=1; /*ENABLE MODUEL ADC*/
	ADCSRA_REG.Bits.ADIE_bit=0; /*DISABLE ADC INTERRPUT */
	/*ADC PRRSCALER  F_CPU/8 */
	ADCSRA_REG.Bytes &= 0xF8 | Config_Ptr->prescaler;

}

uint16 ADC_readChannel(uint8 channel_num)
{
ADMUX_REG.Bytes|= channel_num & 0x07;
ADCSRA_REG.Bits.ADSC_bit=1;
while(ADCSRA_REG.Bits.ADIF_bit==0){};  /*waiting data send*/
ADCSRA_REG.Bits.ADIF_bit=0; /*set ADIF 0*/
return ADC;
}
