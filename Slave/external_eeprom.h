/*
 * external_eeprom.c
 *
 *  Created on: ٠٦‏/١١‏/٢٠٢٣
 *      Author: A Store
 */

#ifndef EXTERNAL_EEPROM_H
#define EXTERNAL_EEPROM_H

#include "std_types.h"

/* ----------------------------------------------------------------------------
 *                      Preprocessor Macros                                   *
  ----------------------------------------------------------------------------*/
#define ERROR 0
#define SUCCESS 1

/* -----------------------------------------------------------------------------
 *                      Functions Prototypes                                   *
 ------------------------------------------------------------------------------*/
void EEPROM_init(void);
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);
 
#endif 
