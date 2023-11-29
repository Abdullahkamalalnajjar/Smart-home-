/*
 * app.c
 *
 *  Created on: ٢١‏/١١‏/٢٠٢٣
 *      Author: A Store
 */

#include "Slave.h"
#include "external_eeprom.h"
#include "uart.h"
#include "gpio.h"
#include "dcmotor.h"
#include "lm35_sensor.h"
#include "adc.h"
#include <util/delay.h>


uint8 g_matchingCheck;
uint8 password[PASS_SIZE];
uint8 password_admin[PASS_SIZE];
uint8 password_guest[PASS_SIZE];
uint8 g_mode;
uint8 request;
uint8 option;
uint8 g_stateRoom;
uint8 ret=0;
uint8 temp;
int main(void){
	GPIO_setupPinDirection(PORTC_ID, PIN2_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID, PIN3_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID, PIN4_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID, PIN5_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID, PIN6_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID, PIN7_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN2_ID,PIN_OUTPUT);

	DCMOTOR_init();
	/*Initializing UART*/
	UART_init(9600);
	ADC_ConfigType CONFIG = {PRESCALER_8,AVCC };
	ADC_init(&CONFIG);
	_delay_ms(100);
	setGuestPassword(password,password_guest);
	setAdminPassword(password,password_admin);

	while(1){
		ret=0;
		request = UART_recieveByte();
		switch(request){
		case ADMIN_MODE:
			adminMode(password,password_admin);
			break;
		case GUEST_MODE:
			guestMode(password,password_guest);
			break;
		}



	}
}


/********************/
void recievePassword(uint8 * password){
	uint8 i;
	for(i=0;i<PASS_SIZE ;i++)
		password[i]=UART_recieveByte();
	_delay_ms(200);
}



void setAdminPassword(uint8 *password,uint8 *password_admin){
	recievePassword(password);
	recievePassword(password_admin);
	g_matchingCheck=matchingCheck(password,password_admin);
	while(g_matchingCheck==UNMATCHED){
		UART_sendByte(UNMATCHED);
		recievePassword(password);
		recievePassword(password_admin);
		g_matchingCheck=matchingCheck(password,password_admin);
	}
	UART_sendByte(MATCHED);
	writePasswordToEeprom(password_admin,adminPasswordAddress);
}

void writePasswordToEeprom(uint8* password, uint16 address) {
	uint8 i = 0;

	// Write bytes from the password array to EEPROM starting at the specified address
	for(i=0 ;i<PASS_SIZE; i++){
		EEPROM_writeByte(address + i, password[i]);
		_delay_ms(300);


	}

}
void readPasswordFromEeprom(uint8* password, uint16 address) {
	uint8 i = 0;

	// Read bytes from EEPROM starting at the specified address and store them in the password array
	for(i=0;i<PASS_SIZE;i++) {
		EEPROM_readByte(address + i, &(password[i]));
		_delay_ms(300);

	}


}
uint8 matchingCheck(uint8 * password , uint8 * password_2){
	uint8 i,j=0;
	for(i=0 ; i<PASS_SIZE; i++){
		if(password[i]==password_2[i]){
			j++;
		}

	}
	if(j==i)
		return MATCHED;
	else
		return UNMATCHED;
}
void setGuestPassword(uint8 *password,uint8 *password_guest){

	recievePassword(password);
	recievePassword(password_guest);
	g_matchingCheck=matchingCheck(password,password_guest);
	while(g_matchingCheck==UNMATCHED){
		UART_sendByte(UNMATCHED);
		recievePassword(password);
		recievePassword(password_guest);
		g_matchingCheck=matchingCheck(password,password_guest);
	}
	UART_sendByte(MATCHED);
	writePasswordToEeprom(password_guest,guestPasswordAddress);
}

void adminMode(uint8 * password , uint8*password_admin ){
	recievePassword(password);
	readPasswordFromEeprom(password_admin,adminPasswordAddress);
	g_matchingCheck=matchingCheck(password,password_admin);
	while(g_matchingCheck!=MATCHED){
		UART_sendByte(UNMATCHED);
		recievePassword(password);
		readPasswordFromEeprom(password_admin,adminPasswordAddress);
		g_matchingCheck=matchingCheck(password,password_admin);

	}
	UART_sendByte(MATCHED);


	/************/

	do{
		option=UART_recieveByte();

		switch(option){
		case ROOM1:
			if(GPIO_readPin(PORTC_ID,PIN5_ID)==LOGIC_LOW){
				UART_sendByte(OFF);
			}else{
				UART_sendByte(ON);

			}
			g_stateRoom=UART_recieveByte();
			if(g_stateRoom==ON){
				turnOn(ROOM1);
			}else if(g_stateRoom==OFF){
				turnOff(ROOM1);
			}else{
				ret=1;
			}
			break;
		case ROOM2:
			if(GPIO_readPin(PORTC_ID,PIN4_ID)==LOGIC_LOW){
				UART_sendByte(OFF);
			}else{
				UART_sendByte(ON);

			}
			g_stateRoom=UART_recieveByte();
			if(g_stateRoom==ON){
				turnOn(ROOM2);
			}else if(g_stateRoom==OFF){
				turnOff(ROOM2);
			}else{
				ret=1;
			}
			break;
		case ROOM3:
			if(GPIO_readPin(PORTC_ID,PIN3_ID)==LOGIC_LOW){
				UART_sendByte(OFF);
			}else{
				UART_sendByte(ON);

			}
			g_stateRoom=UART_recieveByte();
			if(g_stateRoom==ON){
				turnOn(ROOM3);
			}else if(g_stateRoom==OFF){
				turnOff(ROOM3);
			}else{
				ret=1;
			}
			break;
		case MORE:
			option=UART_recieveByte();
			switch(option){
			case ROOM4:
				if(GPIO_readPin(PORTC_ID,PIN2_ID)==LOGIC_LOW){
					UART_sendByte(OFF);
				}else{
					UART_sendByte(ON);

				}
				g_stateRoom=UART_recieveByte();
				if(g_stateRoom==ON){
					turnOn(ROOM4);
				}else if(g_stateRoom==OFF){
					turnOff(ROOM4);
				}else{
					ret=1;
				}
				break;
			case TV:
				if(GPIO_readPin(PORTC_ID,PIN6_ID)==LOGIC_LOW){
					UART_sendByte(OFF);
				}else{
					UART_sendByte(ON);

				}
				g_stateRoom=UART_recieveByte();
				if(g_stateRoom==ON){
					turnOn(TV);
				}else if(g_stateRoom==OFF){
					turnOff(TV);
				}else{
					ret=1;
				}
				break;
			case COND:
				if(UART_recieveByte()==SET_TEMP){
					temp=LM35_getTemperature();
					UART_sendByte(temp);
					if(temp>49){
						GPIO_writePin(PORTD_ID,PIN2_ID,LOGIC_HIGH);
						_delay_ms(2000);
						GPIO_writePin(PORTD_ID,PIN2_ID,LOGIC_LOW);

					}else{
						GPIO_writePin(PORTD_ID,PIN2_ID,LOGIC_LOW);

					}
				}

				else{
					if(GPIO_readPin(PORTC_ID,PIN7_ID)==LOGIC_LOW){
						UART_sendByte(OFF);
					}else{
						UART_sendByte(ON);

					}
					g_stateRoom=UART_recieveByte();
					if(g_stateRoom==ON){
						turnOn(COND);
						DcMotor_Rotate(CW,100);
					}else if(g_stateRoom==OFF){
						turnOff(COND);
						DcMotor_Rotate(STOP,0);

					}else{
						ret=1;
					}
				}
				break;
			}


			break;

		}
	}while(ret!=1);

}
void guestMode(uint8 * password , uint8*password_guest ){
	recievePassword(password);
	readPasswordFromEeprom(password_guest,guestPasswordAddress);
	g_matchingCheck=matchingCheck(password,password_guest);
	while(g_matchingCheck!=MATCHED){
		UART_sendByte(UNMATCHED);
		recievePassword(password);
		readPasswordFromEeprom(password_guest,guestPasswordAddress);
		g_matchingCheck=matchingCheck(password,password_guest);

	}
	UART_sendByte(MATCHED);


	/************/


	option=UART_recieveByte();

	switch(option){
	case ROOM1:
		if(GPIO_readPin(PORTC_ID,PIN5_ID)==LOGIC_LOW){
			UART_sendByte(OFF);
		}else{
			UART_sendByte(ON);

		}
		g_stateRoom=UART_recieveByte();
		if(g_stateRoom==ON){
			turnOn(ROOM1);
		}else if(g_stateRoom==OFF){
			turnOff(ROOM1);
		}
		break;
	case ROOM2:
		if(GPIO_readPin(PORTC_ID,PIN4_ID)==LOGIC_LOW){
			UART_sendByte(OFF);
		}else{
			UART_sendByte(ON);

		}
		g_stateRoom=UART_recieveByte();
		if(g_stateRoom==ON){
			turnOn(ROOM2);
		}else if(g_stateRoom==OFF){
			turnOff(ROOM2);
		}
		break;
	case ROOM3:
		if(GPIO_readPin(PORTC_ID,PIN3_ID)==LOGIC_LOW){
			UART_sendByte(OFF);
		}else{
			UART_sendByte(ON);

		}
		g_stateRoom=UART_recieveByte();
		if(g_stateRoom==ON){
			turnOn(ROOM3);
		}else if(g_stateRoom==OFF){
			turnOff(ROOM3);
		}
		break;
	case ROOM4:
		if(GPIO_readPin(PORTC_ID,PIN2_ID)==LOGIC_LOW){
			UART_sendByte(OFF);
		}else{
			UART_sendByte(ON);

		}
		g_stateRoom=UART_recieveByte();
		if(g_stateRoom==ON){
			turnOn(ROOM4);
		}else if(g_stateRoom==OFF){
			turnOff(ROOM4);
		}
		break;



	}
}
void turnOn(ROOMS room){
	switch(room){
	case ROOM1:
		GPIO_writePin(PORTC_ID,PIN5_ID,LOGIC_HIGH);
		break;
	case ROOM2:
		GPIO_writePin(PORTC_ID,PIN4_ID,LOGIC_HIGH);
		break;
	case ROOM3:
		GPIO_writePin(PORTC_ID,PIN3_ID,LOGIC_HIGH);
		break;
	case ROOM4:
		GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_HIGH);
		break;
	case TV:
		GPIO_writePin(PORTC_ID,PIN6_ID,LOGIC_HIGH);
		break;
	case COND:
		GPIO_writePin(PORTC_ID,PIN7_ID,LOGIC_HIGH);
		break;


	default:
		break;
	}

}
void turnOff(ROOMS room){
	switch(room){
	case ROOM1:
		GPIO_writePin(PORTC_ID,PIN5_ID,LOGIC_LOW);
		break;
	case ROOM2:
		GPIO_writePin(PORTC_ID,PIN4_ID,LOGIC_LOW);
		break;
	case ROOM3:
		GPIO_writePin(PORTC_ID,PIN3_ID,LOGIC_LOW);
		break;
	case ROOM4:
		GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_LOW);
		break;
	case TV:
		GPIO_writePin(PORTC_ID,PIN6_ID,LOGIC_LOW);
		break;
	case COND:
		GPIO_writePin(PORTC_ID,PIN7_ID,LOGIC_LOW);
		break;
	default:
		break;
	}
}

void LED_vTurnOn(uint8 portname,uint8 pinnumber)

{
	GPIO_writePin(portname,pinnumber,LOGIC_HIGH);
	GPIO_writePin(PORTC_ID,PIN5_ID,LOGIC_HIGH);

}
