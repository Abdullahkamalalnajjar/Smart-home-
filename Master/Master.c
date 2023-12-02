/*
 * app.c
 *
 *  Created on: ٢١‏/١١‏/٢٠٢٣
 *      Author: A Store
 */

#include "Master.h"
#include "timer_driver.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "gpio.h"
#include <avr/io.h>
#include "timer1.h"
#include "common_macros.h"
#include <util/delay.h>


uint8 password[PASS_SIZE];
uint8 g_matchingCheck;
uint8 response;//the response of the slave that is sent back based on the command of the master
uint8 temp;
uint8 g_seconds;
uint8 ret=0;

int main(void){
	SREG=(1<<7);
	GPIO_setupPinDirection(PORTC_ID, PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID, PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID, PIN2_ID,PIN_OUTPUT);
	UART_init(9600);
	LCD_init();
	LCD_displayString("Welcome to smart");
	LCD_moveCursor(1,0);
	LCD_displayString("home system");
	_delay_ms(400);
	LCD_clearScreen();
	_delay_ms(100);
	setGuestPassword(password);
	setAdminPassword(password);


	while(1){
		ret=0;
		selectMode(password);

	}


}


/*******get password from key pad ******/
void getPassword(uint8 *password){
	uint8 i ,key;
	for (i=0 ; i<PASS_SIZE; i++){
		key= KEYPAD_getPressedKey();
		delaySeconds(1);
		password[i]=key;
		LCD_displayCharacter('*');
		_delay_ms(300);

	}

}
/********************/
void sendPassword(uint8 * password){
	uint8 i;
	for(i=0 ; i<PASS_SIZE ; i++){
		UART_sendByte(password[i]);
		_delay_ms(300);

	}
}


void setAdminPassword(uint8 *password){
	delaySeconds(0.25);
	LCD_displayString("Set Admin pass");
	LCD_moveCursor(1,0);
	LCD_displayString("Admin pass:");
	getPassword(password);
	sendPassword(password);
	LCD_clearScreen();
	LCD_displayString("Set Admin pass ");
	LCD_moveCursor(1,0);
	LCD_displayString("again pass:");
	getPassword(password);
	sendPassword(password);
	g_matchingCheck=UART_recieveByte();
	while(g_matchingCheck==UNMATCHED){
		LCD_clearScreen();
		LCD_displayString("Error try again!!");
		_delay_ms(300);
		LCD_clearScreen();
		LCD_displayString("Set Admin pass");
		LCD_moveCursor(1,0);
		LCD_displayString("again pass:");
		getPassword(password);
		sendPassword(password);
		LCD_clearScreen();

		LCD_displayString("Set Admin pass ");
		LCD_moveCursor(1,0);
		LCD_displayString("again Admin pass:");
		getPassword(password);
		sendPassword(password);
		g_matchingCheck=UART_recieveByte();
	}
	LCD_clearScreen();

	LCD_displayString("Admin Successful !");
	_delay_ms(300);
	LCD_clearScreen();
}
void setGuestPassword(uint8 *password){
	delaySeconds(0.25);
	LCD_displayString("Set Guest pass");
	LCD_moveCursor(1,0);
	LCD_displayString("Guest pass:");
	getPassword(password);
	sendPassword(password);
	LCD_clearScreen();

	LCD_displayString("Set Guest pass");
	LCD_moveCursor(1,0);
	LCD_displayString("pass again:");
	getPassword(password);
	sendPassword(password);
	g_matchingCheck=UART_recieveByte();
	while(g_matchingCheck==UNMATCHED){
		LCD_clearScreen();
		LCD_displayString("Error try again!!");
		_delay_ms(300);
		LCD_clearScreen();
		LCD_displayString("Set Guest pass");
		LCD_moveCursor(1,0);
		LCD_displayString("Guest pass:");
		getPassword(password);
		sendPassword(password);
		LCD_clearScreen();
		LCD_displayString("Set Guest pass");
		LCD_moveCursor(1,0);
		LCD_displayString("Guest pass:");
		getPassword(password);
		sendPassword(password);
		g_matchingCheck=UART_recieveByte();
	}
	LCD_clearScreen();

	LCD_displayString("Guest Successful !");
	_delay_ms(300);
	LCD_clearScreen();
}

void activeAdminMode(void){
	GPIO_writePin(PORTC_ID,PIN0_ID,LOGIC_HIGH);
}
void disableAdminMode(void){
	GPIO_writePin(PORTC_ID,PIN0_ID,LOGIC_LOW);
}
void disableGuestMode(void){
	GPIO_writePin(PORTC_ID,PIN1_ID,LOGIC_LOW);
}
void activeGuestMode(void){
	GPIO_writePin(PORTC_ID,PIN1_ID,LOGIC_HIGH);
}
void activeAlarm(void){
	GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_HIGH);
}
void disableAlarm(void){
	GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_LOW);
}

void selectMode(uint8* password){
	uint8 key;
	LCD_clearScreen();
	LCD_displayString("Select Mode:");
	LCD_moveCursor(1,0);
	LCD_displayString("0:Admin 1:Guest ");
	key=KEYPAD_getPressedKey();
	_delay_ms(300);
	switch(key){
	case 0:
		UART_sendByte(ADMIN_MODE);
		adminMode(password);
		break;
	case 1:
		UART_sendByte(GUEST_MODE);
		guestMode(password);
		break;
	default:
		LCD_clearScreen();
		LCD_displayString("Plz Enter 0 or 1!");
		_delay_ms(400);
		LCD_clearScreen();
	}
}
void adminMode(uint8* passowrd){
	uint8 key;
	LCD_clearScreen();
	LCD_displayString("Admin Mode:");
	LCD_moveCursor(1,0);
	LCD_displayString("Enter pass: ");
	getPassword(password);
	sendPassword(password);
	g_matchingCheck=UART_recieveByte();
	while(g_matchingCheck!=MATCHED){
		LCD_clearScreen();
		LCD_displayString("password invalid!");
		_delay_ms(300);
		LCD_clearScreen();
		LCD_displayString("Admin Mode:");
		LCD_moveCursor(1,0);
		LCD_displayString("Enter pass: ");
		getPassword(password);
		sendPassword(password);
		g_matchingCheck=UART_recieveByte();
	}
	if(g_matchingCheck==MATCHED){
		LCD_clearScreen();
		disableGuestMode();
		activeAdminMode();
		LCD_displayString("You now in admin mode");
		_delay_ms(300);
		do{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"1:Room1 2:Room2");
			LCD_displayStringRowColumn(1,0,"3:Room3 4:More");
			key=KEYPAD_getPressedKey();
			_delay_ms(400);
			if(key==1){
				UART_sendByte(ROOM1);
				LCD_clearScreen();
				LCD_displayString("ROOM1 S:");
				response=UART_recieveByte();
				if(response==OFF){
					LCD_displayString("OFF");
				}else{
					LCD_displayString("ON");

				}
				LCD_moveCursor(1,0);
				LCD_displayString("1-ON 2-OFF 0-RET");
				key=KEYPAD_getPressedKey();
				_delay_ms(400);
				if(key==1){
					UART_sendByte(ON);
				}else if(key==2){
					UART_sendByte(OFF);

				}else if(key==0){
					UART_sendByte(RET);
					ret=1;

				}
			}else if(key==2){
				UART_sendByte(ROOM2);
				LCD_clearScreen();
				LCD_displayString("ROOM2 S:");
				response=UART_recieveByte();
				if(response==OFF){
					LCD_displayString("OFF");
				}else{
					LCD_displayString("ON");

				}
				LCD_moveCursor(1,0);
				LCD_displayString("1-ON 2-OFF 0-RET");
				key=KEYPAD_getPressedKey();
				_delay_ms(400);
				if(key==1){
					UART_sendByte(ON);
				}else if(key==2){
					UART_sendByte(OFF);

				}else if(key==0){
					UART_sendByte(RET);
					ret=1;

				}
			}else if(key==3){
				UART_sendByte(ROOM3);
				LCD_clearScreen();
				LCD_displayString("ROOM3 S:");
				response=UART_recieveByte();
				if(response==OFF){
					LCD_displayString("OFF");
				}else{
					LCD_displayString("ON");

				}
				LCD_moveCursor(1,0);
				LCD_displayString("1-ON 2-OFF 0-RET");
				key=KEYPAD_getPressedKey();
				_delay_ms(400);
				if(key==1){
					UART_sendByte(ON);
				}else if(key==2){
					UART_sendByte(OFF);

				}else if(key==0){

					UART_sendByte(RET);
					ret=1;

				}
			}else if(key==4){
				UART_sendByte(MORE);
				LCD_clearScreen();
				LCD_displayString("1:ROOM4 2:TV");
				LCD_moveCursor(1,0);
				LCD_displayString("3:Air 4:GARAG");
				key=KEYPAD_getPressedKey();
				_delay_ms(500);
				switch(key){
				case 1:
					UART_sendByte(ROOM4);
					LCD_clearScreen();
					LCD_displayString("ROOM4 S:");
					response=UART_recieveByte();
					if(response==OFF){
						LCD_displayString("OFF");
					}else{
						LCD_displayString("ON");

					}
					LCD_moveCursor(1,0);
					LCD_displayString("1-ON 2-OFF 0-RET");
					key=KEYPAD_getPressedKey();
					_delay_ms(500);
					if(key==1){
						UART_sendByte(ON);
					}else if(key==2){
						UART_sendByte(OFF);

					}else if(key==0){
						UART_sendByte(RET);
						ret=1;

					}
					break;
				case 2:
					UART_sendByte(TV);
					LCD_clearScreen();
					LCD_displayString("TV S:");
					response=UART_recieveByte();
					if(response==OFF){
						LCD_displayString("OFF");
					}else{
						LCD_displayString("ON");

					}
					LCD_moveCursor(1,0);
					LCD_displayString("1-ON 2-OFF 0-RET");
					key=KEYPAD_getPressedKey();
					_delay_ms(500);
					if(key==1){
						UART_sendByte(ON);
					}else if(key==2){
						UART_sendByte(OFF);

					}else if(key==0){
						UART_sendByte(RET);
						ret=1;

					}
					break;
				case 3:

					UART_sendByte(COND);
					LCD_clearScreen();
					LCD_displayString("1:Set Temperature");
					LCD_moveCursor(1,0);
					LCD_displayString("2:Control 3:RET");
					key=KEYPAD_getPressedKey();
					_delay_ms(500);
					switch(key){
					case 1:
						UART_sendByte(SET_TEMP);
						temp=UART_recieveByte();
						LCD_clearScreen();
						LCD_displayString("TEMP= ");
						LCD_intgerToString(temp);
						_delay_ms(500);
						if(temp>49){
							GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_HIGH);
						}else{
							GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_LOW);
						}
						break;
					case 2:
						UART_sendByte(CONTROL_AIR);
						LCD_clearScreen();
						LCD_displayString("AIR S:");
						response=UART_recieveByte();
						if(response==OFF){
							LCD_displayString("OFF");
						}else{
							LCD_displayString("ON");

						}
						LCD_moveCursor(1,0);
						LCD_displayString("1-ON 2-OFF 0-RET");
						key=KEYPAD_getPressedKey();
						_delay_ms(500);
						if(key==1){
							UART_sendByte(ON);
						}else if(key==2){
							UART_sendByte(OFF);

						}else if(key==0){
							UART_sendByte(RET);
							ret=1;
						}
						break;
					}
					break;
					case 4:
						UART_sendByte(GARAG);
						LCD_clearScreen();
						response=UART_recieveByte();
						if(response==EXIST_OBJECT){
							activeAlarm();
							LCD_displayString("Exist object");
							delaySeconds(3);
						}else{
							disableAlarm();
							LCD_displayString("No object here");
							delaySeconds(3);


						}

				}


			}

		}while(ret!=1);

	}

}
void guestMode(uint8 *password){
	uint8 key;
	LCD_clearScreen();
	LCD_displayString("Guest Mode:");
	LCD_moveCursor(1,0);
	LCD_displayString("Enter pass: ");
	getPassword(password);
	sendPassword(password);
	g_matchingCheck=UART_recieveByte();
	while(g_matchingCheck!=MATCHED){
		LCD_clearScreen();
		LCD_displayString("password invalid!");
		_delay_ms(300);
		LCD_clearScreen();
		LCD_displayString("Guest Mode:");
		LCD_moveCursor(1,0);
		LCD_displayString("Enter pass: ");
		getPassword(password);
		sendPassword(password);
		g_matchingCheck=UART_recieveByte();
	}
	if(g_matchingCheck==MATCHED){
		LCD_clearScreen();
		disableAdminMode();
		activeGuestMode();
		LCD_displayString("You now in Guest mode");
		_delay_ms(300);
		LCD_clearScreen();

		LCD_displayStringRowColumn(0,0,"1:Room1 2:Room2");
		LCD_displayStringRowColumn(1,0,"3:Room3 4:Room4");
		key=KEYPAD_getPressedKey();
		_delay_ms(400);
		if(key==1){
			UART_sendByte(ROOM1);
			LCD_clearScreen();
			LCD_displayString("ROOM1 S:");
			response=UART_recieveByte();
			if(response==OFF){
				LCD_displayString("OFF");
			}else{
				LCD_displayString("ON");

			}
			LCD_moveCursor(1,0);
			LCD_displayString("1-ON 2-OFF 0-RET");
			key=KEYPAD_getPressedKey();
			_delay_ms(400);
			if(key==1){
				UART_sendByte(ON);
			}else if(key==2){
				UART_sendByte(OFF);

			}else if(key==0){
				UART_sendByte(RET);
			}
		}else if(key==2){
			UART_sendByte(ROOM2);
			LCD_clearScreen();
			LCD_displayString("ROOM2 S:");
			response=UART_recieveByte();
			if(response==OFF){
				LCD_displayString("OFF");
			}else{
				LCD_displayString("ON");

			}
			LCD_moveCursor(1,0);
			LCD_displayString("1-ON 2-OFF 0-RET");
			key=KEYPAD_getPressedKey();
			_delay_ms(400);
			if(key==1){
				UART_sendByte(ON);
			}else if(key==2){
				UART_sendByte(OFF);

			}else if(key==0){
				UART_sendByte(RET);
			}
		}else if(key==3){
			UART_sendByte(ROOM3);
			LCD_clearScreen();
			LCD_displayString("ROOM3 S:");
			response=UART_recieveByte();
			if(response==OFF){
				LCD_displayString("OFF");
			}else{
				LCD_displayString("ON");

			}
			LCD_moveCursor(1,0);
			LCD_displayString("1-ON 2-OFF 0-RET");
			key=KEYPAD_getPressedKey();
			_delay_ms(400);
			if(key==1){
				UART_sendByte(ON);
			}else if(key==2){
				UART_sendByte(OFF);

			}else if(key==0){
				UART_sendByte(RET);
			}
		}else if(key==4){

			UART_sendByte(ROOM4);
			LCD_clearScreen();
			LCD_displayString("ROOM4 S:");
			response=UART_recieveByte();
			if(response==OFF){
				LCD_displayString("OFF");
			}else{
				LCD_displayString("ON");

			}
			LCD_moveCursor(1,0);
			LCD_displayString("1-ON 2-OFF 0-RET");
			key=KEYPAD_getPressedKey();
			_delay_ms(500);
			if(key==1){
				UART_sendByte(ON);
			}else if(key==2){
				UART_sendByte(OFF);

			}else if(key==0){
				UART_sendByte(RET);
			}


		}
	}


}


void delaySeconds(uint8 sec)
{
	/* setting the callBack function to count seconds */
	Timer1_setCallBack(countSec);

	/* timer1 configurations to count sec per interrupt */
	Timer1_ConfigType timer1Config = {0,31250,F_CPU_256,CTC};

	Timer1_init(&timer1Config);

	while(g_seconds < sec){}
	g_seconds = 0;

	Timer1_deInit();
}
void countSec(void)
{
	g_seconds++;
}


