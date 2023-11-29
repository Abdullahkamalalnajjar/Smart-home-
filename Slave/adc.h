 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega32 ADC driver
 *
 * Author: ABDUALLAH KAMAL
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56




typedef enum {
	AREF,
	AVCC,
	RESERVED,
	INTERNAL256V
}ADC_VoltRefernceType;



typedef enum {
  PRESCALER_2,
  PRESCALER_2I,
  PRESCALER_4,
  PRESCALER_8,
  PRESCALER_16,
  PRESCALER_32,
  PRESCALER_64,
  PRESCALER_128
}ADC_PRESCALERType;

typedef struct {

	ADC_VoltRefernceType volt_ref;
	ADC_PRESCALERType    prescaler;
}ADC_ConfigType;

void ADC_init( const ADC_ConfigType * Config_Ptr);

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/





uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
