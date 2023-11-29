/*
 * app.h
 *
 *  Created on: ٢١‏/١١‏/٢٠٢٣
 *      Author: A Store
 */


#ifndef SLAVE_H_
#define SLAVE_H_
#include "std_types.h"


#define  adminPasswordAddress  0x0311
#define  guestPasswordAddress  0x0322
#define GET_READY 0x01
#define READY 0x02


#define ENTER_ADMIN_MODE        0
#define ENTER_GUEST_MODE        1
#define CHECK_ADMIN_MODE        0
#define CHECK_GUEST_MODE        1

#define SELECT_ROOM1            1
#define SELECT_ROOM2            2
#define SELECT_ROOM3            3
#define SELECT_ROOM4            4
#define ADMIN_MORE_OPTION       4

#define SELECT_ROOM4_ADMIN      1
#define SELECT_TV               2
#define SELECT_AIR_CONDITIONING 3
#define ADMIN_RET_OPTION        4

#define SELECT_SET_TEMPERATURE  1
#define SELECT_AIR_COND_CTRL    2
#define SELECT_AIR_COND_RET     0

/****************************   number of ticks to run timeout ***************************/
#define ADMIN_TIMEOUT (uint16)3000
#define GUEST_TIMEOUT (uint16)2000
/*****************************************************************************************/

/****************************   Show menu codes  *****************************************/
#define MAIN_MENU            (uint8)1
#define MORE_MENU            (uint8)2
#define ROOM1_MENU           (uint8)3
#define ROOM2_MENU           (uint8)4
#define ROOM3_MENU           (uint8)5
#define ROOM4_MENU           (uint8)6
#define TV_MENU              (uint8)7
#define AIRCONDITIONING_MENU (uint8)8
#define AIRCOND_CTRL_MENU    (uint8)9
#define TEMPERATURE_MENU     (uint8)10
/*****************************************************************************************/





#define NOT_STORED   0xFF
#define NOT_SELECTED 0xFF
#define NOT_PRESSED 0xFF


#define BLOCK_MODE_TIME		   (uint32)20000
#define CHARACTER_PREVIEW_TIME (uint16)300
#define DEGREES_SYMBOL		   (uint8)0xDF

/*********************************** PIN Configuration ***********************************/
#define PASS_SIZE       (uint8)2
#define TRIES_ALLOWED   (uint8)3
#define PASSWORD_SYMBOL (uint8)'*'
#define ASCII_ZERO      (uint8)'0'

#define PASS_NOT_SET (uint8)0xFF
#define PASS_SET     (uint8)0x01

#define ADMIN_PASS_STATUS_ADDRESS (uint16)0X100
#define GUEST_PASS_STATUS_ADDRESS (uint16)0X101
#define EEPROM_ADMIN_ADDRESS      (uint16)0X102
#define EEPROM_GUEST_ADDRESS      (uint16)0X106
#define LOGIN_BLOCKED_ADDRESS     (uint16)0X10A
/*****************************************************************************************/

/************************************   Login configurations *****************************/
#define NO_MODE (uint8)0
#define ADMIN   (uint8)1
#define GUEST   (uint8)2
/*****************************************************************************************/




#define ENTER_ADMIN_MODE 0
#define ENTER_GUEST_MODE 1

#define ROOM1_STATUS    0x11
#define ROOM2_STATUS    0x12
#define ROOM3_STATUS    0x13
#define ROOM4_STATUS    0x14
#define TV_STATUS 		0x15
#define AIR_COND_STATUS 0x16

#define ROOM1_TURN_ON    0x21
#define ROOM2_TURN_ON    0x22
#define ROOM3_TURN_ON    0x23
#define ROOM4_TURN_ON    0x24
#define TV_TURN_ON 		 0x25
#define AIR_COND_TURN_ON 0x26

#define ROOM1_TURN_OFF    0x31
#define ROOM2_TURN_OFF    0x32
#define ROOM3_TURN_OFF    0x33
#define ROOM4_TURN_OFF    0x34
#define TV_TURN_OFF 	  0x35
#define AIR_COND_TURN_OFF 0x36
#define BUZZER_ON         0x37
#define BUZZER_OFF        0x38

#define SET_TEMPERATURE 0x40

#define DEFAULT_ACK    0xFF
#define DEMAND_RESPONSE 0xFF

#define ON_STATUS   0x01
#define OFF_STATUS  0x00


/***************PINS OF ROOM ************/
#define PORT_LED    PORTC_ID
#define ROOM1_PIN   PIN5_ID
#define ROOM2_PIN   PIN4_ID
#define ROOM3_PIN   PIN3_ID
#define ROOM4_PIN   PIN2_ID


enum{
	FINISH,DONE
};
typedef enum{
	ADMIN_MODE,GUEST_MODE
}Mode;

typedef enum{
	MATCHED,UNMATCHED
}Matching;
typedef enum{
	ON,OFF,RET
}control;
typedef enum{
	ROOM1,ROOM2,ROOM3,ROOM4,MORE,TV,COND,CONTROL_AIR,SET_TEMP
}ROOMS;
void syncMicroController(void);
void setAdminPassword(uint8 *password,uint8 *password_admin);
void setGuestPassword(uint8 *password,uint8 *password_guest);
void getPassword(uint8 *passwod);
void recievePassword(uint8 *password);
uint8 matchingCheck(uint8 * password , uint8 * password_2);
void writePasswordToEeprom(uint8* password, uint16 address) ;
void readPasswordFromEeprom(uint8* password, uint16 address);
void LED_vTurnOn(uint8 portname,uint8 pinnumber);
void turnOn(ROOMS room);
void guestMode(uint8 * password , uint8*password_guest );
void adminMode(uint8 * password , uint8*password_admin );
void selectMode(uint8* password,uint8* password_admin , uint8 * password_guest);
void turnOff(ROOMS room);


#endif /* SLAVE_H_ */
