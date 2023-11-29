///*
// * app.c
// *
// *  Created on: ٢١‏/١١‏/٢٠٢٣
// *      Author: A Store
// */
//
//#include "Slave.h"
//#include "external_eeprom.h"
//#include "spi.h"
//#include "gpio.h"
//#include <util/delay.h>
//
//uint8 g_mode;
//uint8 g_stateRoom;
//uint8 g_matchingCheck;
//uint8 password[3];
//uint8 password_admin[3];
//uint8 password_guest[3];
//uint8 option;
//int main(void){
//	GPIO_setupPinDirection(PORTC_ID, PIN2_ID,PIN_OUTPUT);
//	GPIO_setupPinDirection(PORTC_ID, PIN3_ID,PIN_OUTPUT);
//	GPIO_setupPinDirection(PORTC_ID, PIN4_ID,PIN_OUTPUT);
//	GPIO_setupPinDirection(PORTC_ID, PIN5_ID,PIN_OUTPUT);
//	GPIO_setupPinDirection(PORTC_ID, PIN6_ID,PIN_OUTPUT);
//	GPIO_setupPinDirection(PORTC_ID, PIN7_ID,PIN_OUTPUT);
//	/*Initializing UART*/
//	SPI_initSlave();
//	syncMicroController();
//	setGuestPassword(password,password_guest);
//	setAdminPassword(password,password_admin);
//
//	while(1){
//		selectMode(password,password_admin,password_guest);
//	}
//}
//
//
///********************/
//void recievePassword(uint8 * password){
//	uint8 i;
//	for(i=0;i<PASS_SIZE ;i++)
//		password[i]=SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
//
//
//}
//
//
//void syncMicroController(void){
//
//	while(SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE)!=GET_READY){};
//	SPI_sendReceiveByte(READY);
//
//}
//void setAdminPassword(uint8 *password,uint8 *password_admin){
//	recievePassword(password);
//	recievePassword(password_admin);
//	g_matchingCheck=matchingCheck(password,password_admin);
//	while(g_matchingCheck==UNMATCHED){
//		SPI_sendReceiveByte(UNMATCHED);
//		recievePassword(password);
//		recievePassword(password_admin);
//		g_matchingCheck=matchingCheck(password,password_admin);
//	}
//	SPI_sendReceiveByte(MATCHED);
//	writePasswordToEeprom(password_admin,adminPasswordAddress);
//}
//
//void writePasswordToEeprom(uint8* password, uint16 address) {
//	uint8 i = 0;
//
//	// Write bytes from the password array to EEPROM starting at the specified address
//	for(i=0 ;i<PASS_SIZE; i++){
//		EEPROM_writeByte(address + i, password[i]);
//
//	}
//
//}
//void readPasswordFromEeprom(uint8* password, uint16 address) {
//	uint8 i = 0;
//
//	// Read bytes from EEPROM starting at the specified address and store them in the password array
//	for(i=0;i<PASS_SIZE;i++) {
//		EEPROM_readByte(address + i, &(password[i]));
//
//	}
//
//
//}
//uint8 matchingCheck(uint8 * password , uint8 * password_2){
//	uint8 i,j=0;
//	for(i=0 ; i<PASS_SIZE; i++){
//		if(password[i]==password_2[i]){
//			j++;
//		}
//
//	}
//	if(j==i)
//		return MATCHED;
//	else
//		return UNMATCHED;
//}
//void setGuestPassword(uint8 *password,uint8 *password_guest){
//
//	recievePassword(password);
//	recievePassword(password_guest);
//	g_matchingCheck=matchingCheck(password,password_guest);
//	while(g_matchingCheck==UNMATCHED){
//		SPI_sendReceiveByte(UNMATCHED);
//		recievePassword(password);
//		recievePassword(password_guest);
//		g_matchingCheck=matchingCheck(password,password_guest);
//	}
//	SPI_sendReceiveByte(MATCHED);
//	writePasswordToEeprom(password_guest,guestPasswordAddress);
//}
//void selectMode(uint8* password,uint8* password_admin , uint8 * password_guest){
//
//	g_mode=SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
//	switch(g_mode){
//	case ADMIN:
//		adminMode(password,password_admin);
//		break;
//	case GUEST:
//		guestMode(password,password_guest);
//		break;
//
//	}
//
//}
//void adminMode(uint8 * password , uint8*password_admin ){
//	recievePassword(password);
//	readPasswordFromEeprom(password_admin,adminPasswordAddress);
//	g_matchingCheck=matchingCheck(password,password_admin);
//	while(g_matchingCheck!=MATCHED){
//		SPI_sendReceiveByte(UNMATCHED);
//		recievePassword(password);
//		readPasswordFromEeprom(password_admin,adminPasswordAddress);
//		g_matchingCheck=matchingCheck(password,password_admin);
//
//	}
//	SPI_sendReceiveByte(MATCHED);
//	g_stateRoom=SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
//	_delay_ms(10); // Add an appropriate delay
//
//	option=SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
//	switch(option){
//	case ROOM1:
//		if(g_stateRoom==ON){
//			turnOn(ROOM1);
//		}else if(g_stateRoom==OFF){
//			turnOff(ROOM1);
//		}
//		break;
//	case ROOM2:
//		if(g_stateRoom==ON){
//			turnOn(ROOM1);
//		}else if(g_stateRoom==OFF){
//			turnOff(ROOM2);
//		}
//		break;
//	}
//
//}
//void guestMode(uint8 * password , uint8*password_guest ){
//	recievePassword(password);
//	readPasswordFromEeprom(password_guest,guestPasswordAddress);
//	g_matchingCheck=matchingCheck(password,password_guest);
//	while(g_matchingCheck!=MATCHED){
//		recievePassword(password);
//		readPasswordFromEeprom(password_guest,guestPasswordAddress);
//		g_matchingCheck=matchingCheck(password,password_guest);
//
//	}
//	SPI_sendReceiveByte(MATCHED);
//}
//void turnOn(ROOMS room){
//	switch(room){
//	case ROOM1:
//		GPIO_writePin(PORTC_ID,PIN5_ID,LOGIC_HIGH);
//		break;
//	case ROOM2:
//		GPIO_writePin(PORTC_ID,PIN4_ID,LOGIC_HIGH);
//		break;
//	case ROOM3:
//		GPIO_writePin(PORTC_ID,PIN3_ID,LOGIC_HIGH);
//		break;
//	case ROOM4:
//		GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_HIGH);
//		break;
//	case TV:
//		GPIO_writePin(PORTC_ID,PIN6_ID,LOGIC_HIGH);
//		break;
//	case COND:
//		GPIO_writePin(PORTC_ID,PIN7_ID,LOGIC_HIGH);
//		break;
//	}
//
//}
//void turnOff(ROOMS room){
//	switch(room){
//	case ROOM1:
//		GPIO_writePin(PORTC_ID,PIN5_ID,LOGIC_LOW);
//		break;
//	case ROOM2:
//		GPIO_writePin(PORTC_ID,PIN4_ID,LOGIC_LOW);
//		break;
//	case ROOM3:
//		GPIO_writePin(PORTC_ID,PIN3_ID,LOGIC_LOW);
//		break;
//	case ROOM4:
//		GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_LOW);
//		break;
//	case TV:
//		GPIO_writePin(PORTC_ID,PIN6_ID,LOGIC_LOW);
//		break;
//	case COND:
//		GPIO_writePin(PORTC_ID,PIN7_ID,LOGIC_LOW);
//		break;
//	}
//}
