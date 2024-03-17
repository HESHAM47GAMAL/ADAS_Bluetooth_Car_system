/******************************************************************************
 *
 * Module: Application
 *
 * File Name: Application_program.c
 *
 * Description: source file for implementation for all functionality for Application Specefic
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/



/**************************                   INCLUDES                   **************************/

#include "Application_interface.h"
#include "Application_private.h"
#include "../SERVICE/IVT.h"
#include <util/delay.h>





/**************************                   Enums                    **************************/
enum	E_LCD_PAGE{
	E_LCD_PAGE_MAIN,
	E_LCD_PAGE_RIGHT,
	E_LCD_PAGE_LEFT
};

enum	E_GBX{
	E_GBX_NEUTRAL,
	E_GBX_DRIVE,
	E_GBX_REVERSE,
	E_GBX_RETURN_TO_N
};


enum E_KEYPAD{
	E_KEYPAD_CCS_TOG,
	E_KEYPAD_LEFT_PAGE,
	E_KEYPAD_GEARBOX,
	E_KEYPAD_RIGHT_PAGE,
	E_KEYPAD_PLACEHOLDER4,
	E_KEYPAD_PLACEHOLDER5,
	E_KEYPAD_PLACEHOLDER6,
	E_KEYPAD_SPEED_LIMITER_DEC,
	E_KEYPAD_SPEED_LIMITER_TOG,
	E_KEYPAD_SPEED_LIMITER_INC
};

/**************************                   Global variable                   **************************/
volatile uint8 LCD_SELECT = E_LCD_PAGE_MAIN;
uint8 volatile KEYPAD_PRESSED = -1;
uint8  GBX_STATE = E_GBX_NEUTRAL;
uint8  GBX_IS_STILL_PRESSED = NO_Condition;



/**************************                   Function bodies                   **************************/


// Body of initialize function
void A_APPLICATION_VOID_INIT(void){
	//initialize LEDs needed
	LED_Init(YLW_LED_PORT,YLW_LED_PIN);
	LED_Init(RED_LED_PORT,RED_LED_PIN);

	//initialize Buzzer
	Buzzer_Init(BZR_PORT,BZR_PIN);

	//initialize LCD
	LCD_init();

	//initialize ADC
	ADC_Init();

	//initialize External interrupt
	INT0_init(RISING_EDGE_TRIGGER,INPUT_PIN);

	//initialize keypad
	Keypad_init();

}

/************************** LCD screen select function **************************/
void A_APPLICATION_VOID_MAIN_LCD_SCREEN_SELECT(){

	switch (LCD_SELECT) {
	case E_LCD_PAGE_MAIN:

		break;

	case E_LCD_PAGE_RIGHT:

		break;

	case E_LCD_PAGE_LEFT:

		break;
	default:
		break;
	}

}

/************************** Keypad button read check function **************************/
void A_APPLICATION_VOID_KEYPAD_BUTTON_READ(void){
	KEYPAD_PRESSED = Keypad_GetPressedKey();

	if((KEYPAD_PRESSED == E_KEYPAD_GEARBOX ))
	{
		A_APPLICATION_VOID_GBX_CHANGE();

	}
	else {
		GBX_IS_STILL_PRESSED = NO_Condition;
	}





	if (KEYPAD_PRESSED == E_KEYPAD_CCS_TOG) {

	}
	else {


	}

	if (KEYPAD_PRESSED == E_KEYPAD_LEFT_PAGE) {
LCD_ClearScreen();

	}
	else {


	}

	if (KEYPAD_PRESSED == E_KEYPAD_GEARBOX) {


	}
	else {


	}

	if (KEYPAD_PRESSED == E_KEYPAD_RIGHT_PAGE) {


	}
	else {


	}

	if (KEYPAD_PRESSED == E_KEYPAD_SPEED_LIMITER_DEC) {

	}
	else {


	}

	if (KEYPAD_PRESSED == E_KEYPAD_SPEED_LIMITER_TOG) {

		LCD_MoveCursor(2,2);
		LCD_DisplayCharacter((KEYPAD_PRESSED + '0'));

	}
	else {


	}

	if (KEYPAD_PRESSED == E_KEYPAD_SPEED_LIMITER_INC) {
		LCD_MoveCursor(2,2);
		LCD_DisplayCharacter((KEYPAD_PRESSED + '0'));


	}
	else {

	}




}




void A_APPLICATION_VOID_MAIN_LCD_LOAD(void){
	LCD_MoveCursor(3,0);
	LCD_DisplayString((const uint8 * )"CCS");

	LCD_MoveCursor(3,5);
	LCD_DisplayString((const uint8 * )"BAS");

	LCD_MoveCursor(3,10);
	LCD_DisplayString((const uint8 * )"SL");

	LCD_MoveCursor(0,9);
	LCD_DisplayString((const uint8 * )"S: 999 Km/h");

	LCD_MoveCursor(1,13);
	LCD_DisplayString((const uint8 * )"R N D");

	_delay_ms(2000);
	LCD_ClearScreen();
	A_APPLICATION_VOID_MAIN_LCD_STATICS();




}


void A_APPLICATION_VOID_MAIN_LCD_STATICS(void){
	LCD_MoveCursor(0,9);
	LCD_DisplayString((const uint8 * )"S:     KM/h");

	LCD_MoveCursor(1,13);
	LCD_DisplayString((const uint8 * )"R N D");

}

void A_APPLICATION_VOID_GBX_CHANGE(void){

		if(GBX_IS_STILL_PRESSED == NO_Condition)
		{
			GBX_IS_STILL_PRESSED = YES_Condition ;

			/*  Go to next state for gearbox*/
			GBX_STATE++ ;

			if(GBX_STATE == E_GBX_RETURN_TO_N)
			{
				GBX_STATE = E_GBX_NEUTRAL ;

			}

			/*  call function to update gearbox state in Dashboard*/
			A_APPLICATION_VOID_GBX_DISPLAY(GBX_STATE);

		}




}
void A_APPLICATION_VOID_GBX_DISPLAY(uint8 state){
	/*  Array carry All Characters For GearBox as make display easier using index*/
//	    uint8 GearBox_chars [] = {'N','D','R'};
//	    /*  Go to index that display current GearBox state*/
//	    LCD_MoveCursor(3,3);
//	    /*  Edit its state with new state given to function*/
//	    LCD_DisplayCharacter(GearBox_chars[state]);

	switch (state) {
	case E_GBX_NEUTRAL:
		LCD_MoveCursor(2,13);
		LCD_DisplayString((const uint8*)"  _  ");
		break;
	case E_GBX_DRIVE:
		LCD_MoveCursor(2,13);
		LCD_DisplayString((const uint8*)"    _");
		break;
	case E_GBX_REVERSE:
		LCD_MoveCursor(2,13);
		LCD_DisplayString((const uint8*)"_    ");
		break;
	default:
		break;
	}

}











