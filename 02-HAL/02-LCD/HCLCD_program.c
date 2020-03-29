/*
 * HCLCD_program.c
 *
 *  Created on: 25 Mar 2020
 *      Author: Basma Abdelhakim
 */

#include "STD_TYPES.h"

#include "HCLCD_interface.h"
#include "HCLCD_config.h"

#include  "GPIO.h"

/***********************************************************************************************
        Definition  of the required GPIO structure to configure GPIO pins of LCD */

GPIO_t CLCD_PINS = { .pin = CLCD_RS | CLCD_RW | CLCD_E | CLCD_D0 | CLCD_D1
		| CLCD_D2 | CLCD_D3 | CLCD_D4 | CLCD_D5 | CLCD_D6 | CLCD_D7 , .mode =
				MODE_OUTPUT_SPEED_10, .port = CLCD_PORT };

/***********************************************************************************************/

/*******************************************(Macros)********************************************/
#define  IDEL_PROCESS            0U
#define WRITE_STRING_PROCESS     1U
#define CLEAR_PROCESS            2U
#define MOVE_CURSOR_PROCESS      3U

#define INITIALIZATION_DELAY     0U
#define FUNCTION_SET_COMMAND     1U
#define DISPLAY_ON_OFF_COMMAND   2U
#define DISPLAY_CLEAR_COMMAND    3U
#define ENTRY_MODE_SET           4U

 /**********************************************************************************************/


/***************************************Prototypes*********************************************/
static u8 HCLCD_initProcess(void);
static void HCLCD_writeStringProcess(void);
static void HCLCD_clearProcess(void);
static void HCLCD_moveCursorProcess(void);

/***********************************************************************************************/


/***************************************Global variables****************************************/
static u32 CLCD_DATA_PINS[8] = { CLCD_D0, CLCD_D1, CLCD_D2, CLCD_D3, CLCD_D4,
		CLCD_D5, CLCD_D6, CLCD_D7 };
static u8 INIT_COMPLETED_FLAG;
static u8 CURRENT_PROCESS;
static u8 lenght;
static u8 word[255];
static u8 REQUESTED_ROW;
static u8 REQUESTED_COLUMN;

notify_t WRITE_DONE_NOTIFICATION;
notify_t CLEAR_DONE_NOTIFICATION;
notify_t MOVE_CURSOR_DONE_NOTIFICATION;
/***********************************************************************************************/


/******************************************Functions********************************************/

/***********************************************************************************************/
ERROR_STATUS HCLCD_init(void) {

	ERROR_STATUS returnValue = GPIO_initPin(&CLCD_PINS);

	return returnValue;
}

/***********************************************************************************************/
ERROR_STATUS HCLCD_writeString(const u8 * userWord, u8 userLenght) {

	ERROR_STATUS returnValue;
	u8 wordIndex;

	if (userWord != NULL) {
		if (CURRENT_PROCESS == IDEL_PROCESS) {
			CURRENT_PROCESS = WRITE_STRING_PROCESS;

			for (wordIndex = 0; wordIndex < userLenght; wordIndex++) {
				word[wordIndex] = userWord[wordIndex];
			}
			lenght = userLenght;
			returnValue = status_Ok;
		} else {
			returnValue = status_NOk;
		}
	}
	else{
		returnValue = status_NOk;
	}
	return returnValue;
}


/***********************************************************************************************/
ERROR_STATUS HCLCD_writeDoneApp(notify_t appFunction){

	ERROR_STATUS returnValue;

	if(appFunction != NULL){
		WRITE_DONE_NOTIFICATION=appFunction;
		returnValue=status_Ok;
	}
	else{
		returnValue=status_NOk;
	}
	return returnValue;
}

/***********************************************************************************************/
ERROR_STATUS HCLCD_clear(void) {

	ERROR_STATUS returnValue;

	if (CURRENT_PROCESS == IDEL_PROCESS) {
		CURRENT_PROCESS = CLEAR_PROCESS;
		returnValue = status_Ok;
	} else {
		returnValue = status_NOk;
	}
	return returnValue;
}

/***********************************************************************************************/
ERROR_STATUS HCLCD_clearDoneApp(notify_t appFunction){

	ERROR_STATUS returnValue;
	if(appFunction != NULL){
		CLEAR_DONE_NOTIFICATION=appFunction;
		returnValue=status_Ok;
	}
	else{
		returnValue=status_NOk;
	}
	return returnValue;
}

/***********************************************************************************************/
ERROR_STATUS HCLCD_moveCursorLocation(u8 row , u8 column){

	ERROR_STATUS returnValue;

	if (CURRENT_PROCESS == IDEL_PROCESS) {
			CURRENT_PROCESS = MOVE_CURSOR_PROCESS;
			REQUESTED_ROW=row;
			REQUESTED_COLUMN=column;
			returnValue = status_Ok;
		} else {
			returnValue = status_NOk;
		}
		return returnValue;

}
/***********************************************************************************************/
ERROR_STATUS HCLCD_moveCursorDoneApp(notify_t appFunction){

	ERROR_STATUS returnValue;

	if(appFunction != NULL){
			MOVE_CURSOR_DONE_NOTIFICATION=appFunction;
			returnValue=status_Ok;
		}
		else{
			returnValue=status_NOk;
		}
		return returnValue;
}
/***********************************************************************************************/

/****************************************Static functions **************************************/

/***********************************************************************************************/
static u8 HCLCD_initProcess(void) {

	static u8 currentInitState = FUNCTION_SET_COMMAND;
	static u8 counter = 0;
	u8 iterator;
	u8 returnValue = status_NOk;
    static u8 CLCD_E_value=0;
	if (counter >= 20) {
		switch (currentInitState) {
		case FUNCTION_SET_COMMAND:
			GPIO_directReadPin(CLCD_PORT,CLCD_E, &CLCD_E_value);
			if (CLCD_E_value) {
				/*CLCD_E =0*/
				GPIO_directWritePin(CLCD_PORT ,CLCD_E, PIN_RESET);
				currentInitState = DISPLAY_ON_OFF_COMMAND;
			} else {
				/*FUNCTION_SET_COMMAND actions
				 1. Set RS and RW to zero
				 2. Write Function Set configuration*/

				GPIO_directWritePin(CLCD_PORT ,CLCD_RS, PIN_RESET);
				GPIO_directWritePin(CLCD_PORT ,CLCD_RW, PIN_RESET);

				u8 functionConfiguration[8] = { PIN_RESET, PIN_RESET, CLCD_CHARACTER_FONT,
				CLCD_LINES_DISPLAYED, PIN_SET, PIN_SET, PIN_RESET, PIN_RESET };
				for (iterator = 0; iterator < 8; iterator++) {
					GPIO_directWritePin(CLCD_PORT, CLCD_DATA_PINS[iterator],
							functionConfiguration[iterator]);
				}
				/*Let CLCD_E = 1*/
				GPIO_directWritePin(CLCD_PORT, CLCD_E, PIN_SET);
			}
			break;
		case DISPLAY_ON_OFF_COMMAND:
			/*If CLCD_E == 1*/
			GPIO_directReadPin(CLCD_PORT,CLCD_E, &CLCD_E_value);
			if (CLCD_E_value) {
				/*CLCD_E =0*/
				GPIO_directWritePin(CLCD_PORT, CLCD_E, PIN_RESET);
				currentInitState = DISPLAY_CLEAR_COMMAND;
			} else {
				/*Display On/Off COMMAND actions
				 1. Set RS and RW to zero
				 2. Write ON/OFF configuration*/

				GPIO_directWritePin(CLCD_PORT, CLCD_RS, PIN_RESET);
				GPIO_directWritePin(CLCD_PORT, CLCD_RW, PIN_RESET);

				/*ON/OFF configuration*/
				u8 ON_OFF_configuration[8] = { CLCD_BLINK_MODE,
				CLCD_CURSOR_MODE,
				CLCLD_DIAPLY_MODE, PIN_SET, PIN_RESET, PIN_RESET, PIN_RESET, PIN_RESET};
				for (iterator = 0; iterator < 8; iterator++) {
					GPIO_directWritePin(CLCD_PORT, CLCD_DATA_PINS[iterator],
							ON_OFF_configuration[iterator]);
				}
				/*Let CLCD_E = 1*/
				GPIO_directWritePin(CLCD_PORT, CLCD_E, PIN_SET);
			}
			break;
		case DISPLAY_CLEAR_COMMAND:
			/*If CLCD_E == 1*/
			GPIO_directReadPin(CLCD_PORT,CLCD_E, &CLCD_E_value);
			if (CLCD_E_value) {
				/*CLCD_E =0*/
				GPIO_directWritePin(CLCD_PORT, CLCD_E, PIN_RESET);
				INIT_COMPLETED_FLAG = 1;
			} else {
				/*DISPLAY_CLEAR_COMMAND actions
				 1. Set RS and RW to zero
				 2. Write Clear configuration*/

				GPIO_directWritePin(CLCD_PORT, CLCD_RS, PIN_RESET);
				GPIO_directWritePin(CLCD_PORT, CLCD_RW, PIN_RESET);

				/*Clear configuration*/
				GPIO_directWritePin(CLCD_PORT, CLCD_D0, PIN_SET);
				GPIO_directWritePin(CLCD_PORT, CLCD_D1, PIN_RESET);
				GPIO_directWritePin(CLCD_PORT, CLCD_D2, PIN_RESET);
				GPIO_directWritePin(CLCD_PORT, CLCD_D3, PIN_RESET);
				GPIO_directWritePin(CLCD_PORT, CLCD_D4, PIN_RESET);
				GPIO_directWritePin(CLCD_PORT, CLCD_D5, PIN_RESET);
				GPIO_directWritePin(CLCD_PORT, CLCD_D6, PIN_RESET);
				GPIO_directWritePin(CLCD_PORT, CLCD_D7, PIN_RESET);


				/*Let CLCD_E = 1*/
				GPIO_directWritePin(CLCD_PORT, CLCD_E, PIN_SET);
			}
			break;
		}
	} else {
		counter++;
	}

	return returnValue;
}
/***********************************************************************************************/
static void HCLCD_writeStringProcess(void) {

/*
  Write process steps:
               1.Set RS to 1.
               2.Set RW to 0.
               3.write data.
               4. EnablePulse.
 */
	static u8 currentChar = 0;
	u8 index;
	u8 pinValue;
    static u8 CLCD_E_value;
	/*If CLCD_E == 1*/
	GPIO_directReadPin(CLCD_PORT,CLCD_E, &CLCD_E_value);
	if (CLCD_E_value) {
		/*CLCD_E =0*/
		GPIO_directWritePin(CLCD_PORT, CLCD_E, PIN_RESET);
	} else {
		if (lenght == currentChar) {
			CURRENT_PROCESS = IDEL_PROCESS;
			currentChar = 0;
			WRITE_DONE_NOTIFICATION();
		} else {
			GPIO_directWritePin(CLCD_PORT, CLCD_RS, PIN_SET);
			GPIO_directWritePin(CLCD_PORT, CLCD_RW, PIN_RESET);

              /*B=01000010*/
			for (index = 0; index < 8; index++) {
				pinValue = (word[currentChar] >> index) & 0x01;
				GPIO_directWritePin(CLCD_PORT, CLCD_DATA_PINS[index],
						pinValue);
			}
			/*Let CLCD_E = 1*/
			GPIO_directWritePin(CLCD_PORT, CLCD_E, PIN_SET);
			currentChar++;
		}

	}
}


/***********************************************************************************************/
static void HCLCD_clearProcess(void) {
    static u8 CLCD_E_value;
	/*If CLCD_E == 1*/
	GPIO_directReadPin(CLCD_PORT,CLCD_E, &CLCD_E_value);
	if (CLCD_E_value) {
		/*CLCD_E =0*/
		GPIO_directWritePin(CLCD_PORT,CLCD_E,PIN_RESET);
		CURRENT_PROCESS = IDEL_PROCESS;
		CLEAR_DONE_NOTIFICATION();
	} else {
		/*DISPLAY_CLEAR_COMMAND actions
		 1. Set RS and RW to zero
		 2. Write Clear configuration*/
		GPIO_directWritePin(CLCD_PORT, CLCD_RS, PIN_RESET);
		GPIO_directWritePin(CLCD_PORT, CLCD_RW, PIN_RESET);

		/*Clear configuration*/
		GPIO_directWritePin(CLCD_PORT, CLCD_D0, PIN_SET);
		GPIO_directWritePin(CLCD_PORT, CLCD_D1, PIN_RESET);
		GPIO_directWritePin(CLCD_PORT, CLCD_D2, PIN_RESET);
		GPIO_directWritePin(CLCD_PORT, CLCD_D3, PIN_RESET);
		GPIO_directWritePin(CLCD_PORT, CLCD_D4, PIN_RESET);
		GPIO_directWritePin(CLCD_PORT, CLCD_D5, PIN_RESET);
		GPIO_directWritePin(CLCD_PORT, CLCD_D6, PIN_RESET);
		GPIO_directWritePin(CLCD_PORT, CLCD_D7, PIN_RESET);

		/*Let CLCD_E = 1*/
		GPIO_directWritePin(CLCD_PORT, CLCD_E, PIN_SET);
	}
}

/***********************************************************************************************/
static void HCLCD_moveCursorProcess(void){
	u8 location = REQUESTED_ROW + REQUESTED_COLUMN;
	u8 index;
	u8 pinValue;
    static u8 CLCD_E_value;
	/*If CLCD_E == 1*/
	GPIO_directReadPin(CLCD_PORT,CLCD_E, &CLCD_E_value);
	if (CLCD_E_value) {
		/*CLCD_E =0*/
		GPIO_directWritePin(CLCD_PORT, CLCD_E, PIN_RESET);
		CURRENT_PROCESS = IDEL_PROCESS;
		MOVE_CURSOR_DONE_NOTIFICATION();
	} else {
		/*Set RS and RW to 0 */
		GPIO_directWritePin(CLCD_PORT, CLCD_RS, PIN_RESET);
		GPIO_directWritePin(CLCD_PORT, CLCD_RW, PIN_RESET);

		for (index = 0; index < 8; index++) {
			pinValue = (location >> index) & 0x01;
			GPIO_directWritePin(CLCD_PORT, CLCD_DATA_PINS[index], pinValue);

		}
		/*Let CLCD_E = 1*/
		GPIO_directWritePin(CLCD_PORT, CLCD_E, PIN_SET);
	}
}
/***********************************************************************************************/



/****************************************LCD Runnable********************************************/
void HCLCD_task(void) {
	if (INIT_COMPLETED_FLAG) {
		switch (CURRENT_PROCESS) {
		case IDEL_PROCESS:
			break;
		case WRITE_STRING_PROCESS:
			HCLCD_writeStringProcess();
			break;
		case CLEAR_PROCESS:
			HCLCD_clearProcess();
			break;
		case MOVE_CURSOR_PROCESS:
			HCLCD_moveCursorProcess();
			break;
		}
	} else {
		HCLCD_initProcess();
	}

}

/***********************************************************************************************/


























