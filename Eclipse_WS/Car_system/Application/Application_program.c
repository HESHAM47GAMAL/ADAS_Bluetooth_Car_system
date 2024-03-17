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





/**************************                   Enums                    **************************/
enum	E_LCD_PAGE{
	E_LCD_PAGE_MAIN,
	E_LCD_PAGE_RIGHT,
	E_LCD_PAGE_LEFT
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
uint8 volatile KEYPAD_PRESSED;


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
void A_APPLICATION_MAIN_LCD_SCREEN_SELECT(){

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

	switch (KEYPAD_PRESSED) {

	case E_KEYPAD_CCS_TOG:

		break;
	case E_KEYPAD_LEFT_PAGE:

		break;
	case E_KEYPAD_GEARBOX:

		break;
	case E_KEYPAD_RIGHT_PAGE:

		break;
	case E_KEYPAD_SPEED_LIMITER_DEC:

		break;
	case E_KEYPAD_SPEED_LIMITER_TOG:

		break;
	case E_KEYPAD_SPEED_LIMITER_INC:

		break;

	default:	//do nothing
		break;
	}

}


sint8 A_APPLICATION_sint8_LCD_PAGE_UPDATE(void) {

	KEYPAD_PRESSED = Keypad_GetPressedKey();
	if (KEYPAD_PRESSED == E_KEYPAD_RIGHT_PAGE) {
	static uint8 BTN_STATE;
	BTN_STATE  = LOGIC_LOW;
	static uint8 BTN_STILL_PRESSED = LOGIC_LOW ;
//		if (condition) {

			if(BTN_STATE == LOGIC_LOW)
			{
				if(BTN_STILL_PRESSED == LOGIC_LOW)
				{
					uint8 GearBox_Characyer [] = {'N','D','R'};
					LCD_MoveCursor(0,17);
					LCD_DisplayCharacter(GearBox_Characyer[0]);
					BTN_STILL_PRESSED = LOGIC_HIGH ;
				}
			}
			else
			{

				BTN_STILL_PRESSED = LOGIC_HIGH ;
			}
		//}


	}
}
	sint8 A_APPLICATION_sint8_LCD_PAGE_UPDATE2(void) {

		KEYPAD_PRESSED = Keypad_GetPressedKey();
		if (KEYPAD_PRESSED == E_KEYPAD_LEFT_PAGE) {
		static uint8 BTN_STATE;
		BTN_STATE  = LOGIC_LOW;
		static uint8 BTN_STILL_PRESSED = LOGIC_LOW ;
	//		if (condition) {

				if(BTN_STATE == LOGIC_LOW)
				{
					if(BTN_STILL_PRESSED == LOGIC_LOW)
					{
						uint8 GearBox_Characyer [] = {'N','D','R'};
						LCD_MoveCursor(0,17);
						LCD_DisplayCharacter(GearBox_Characyer[1]);
						BTN_STILL_PRESSED = LOGIC_HIGH ;
					}
				}
				else
				{

					BTN_STILL_PRESSED = LOGIC_HIGH ;
				}
			//}
		}
	}












