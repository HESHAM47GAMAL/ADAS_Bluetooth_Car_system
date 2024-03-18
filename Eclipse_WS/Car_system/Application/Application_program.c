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
enum E_LCD_PAGE
{
	E_LCD_PAGE_MAIN,
	E_LCD_PAGE_CCSBA,
	E_LCD_PAGE_SL,
	E_LCD_PAGE_INFO
};

enum E_LCD_PAGE_L2R
{
	E_L2R_LCD_PAGE_MAIN,
	E_L2R_LCD_PAGE_RIGHT,
	E_L2R_LCD_PAGE_INFO,
	E_L2R_LCD_PAGE_LEFT
};

enum E_LCD_PAGE_R2L
{
	E_R2L_LCD_PAGE_MAIN,
	E_R2L_LCD_PAGE_LEFT,
	E_R2L_LCD_PAGE_INFO,
	E_R2L_LCD_PAGE_RIGHT
};

enum E_LCD_CUSTOM_CHARACTERS
{
	E_CHAR_GBX_SELECTED,
	E_CHAR_PAGE_SELECTED,
	E_CHAR_PAGE_NOT_SELECTED,
	E_CHAR_PAGE_INV_A,
	E_CHAR_PAGE_INV_L,
	E_CHAR_PAGE_INV_E,
	E_CHAR_PAGE_INV_R,
	E_CHAR_PAGE_INV_T,
};

enum BA_STATE
{
	E_BA_ON,
	E_BA_OFF,
	E_BA_RETURN_TO_ON

};

enum SL_STATE
{
	E_SL_ON,
	E_SL_OFF,
	E_SL_RETURN_TO_ON

};

enum CCS_STATE
{
	E_CCS_ON,
	E_CCS_OFF,
	E_CCS_RETURN_TO_ON

};

enum E_GBX
{
	E_GBX_NEUTRAL,
	E_GBX_DRIVE,
	E_GBX_REVERSE,
	E_GBX_RETURN_TO_N
};

enum E_KEYPAD
{
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

/**************************                   Global variables                   **************************/
volatile uint8 LCD_PAGE_STATE = E_LCD_PAGE_MAIN;
uint8 volatile KEYPAD_PRESSED = -1;
uint8 BA_STATE = OFF;
uint8 CCS_STATE = OFF;
uint8 SL_STATE = OFF;

uint8 GBX_STATE = E_GBX_NEUTRAL;
uint8 GBX_IS_STILL_PRESSED = NO_Condition;
uint8 SCREEN_RIGHT_SCROLL_IS_STILL_PRESSED = NO_Condition;
uint8 SCREEN_LEFT_SCROLL_IS_STILL_PRESSED = NO_Condition;
uint8 BA_IS_STILL_PRESSED = NO_Condition;
uint8 CCS_IS_STILL_PRESSED = NO_Condition;
uint8 SL_IS_STILL_PRESSED = NO_Condition;

/**************************                   SPECIAL LCD variables                   **************************/
uint8 GBX_SELECTED[] = {0x04, 0x0E, 0x15, 0x04, 0x04, 0x00, 0x00, 0x00};
uint8 PAGE_SELECTED[] = {0x00, 0x00, 0x0E, 0x1F, 0x1F, 0x1F, 0x0E, 0x00};
uint8 PAGE_NOT_SELECTED[] = {0x00, 0x00, 0x0E, 0x11, 0x15, 0x11, 0x0E, 0x00};
uint8 INVERTED_A[] = {0x1F, 0x1B, 0x15, 0x11, 0x15, 0x15, 0x1F, 0x1F};
uint8 INVERTED_L[] = {0x1F, 0x17, 0x17, 0x17, 0x17, 0x11, 0x1F, 0x1F};
uint8 INVERTED_E[] = {0x1F, 0x11, 0x17, 0x11, 0x17, 0x11, 0x1F, 0x1F};
uint8 INVERTED_R[] = {0x1F, 0x11, 0x15, 0x13, 0x15, 0x15, 0x1F, 0x1F};
uint8 INVERTED_T[] = {0x1F, 0x11, 0x1B, 0x1B, 0x1B, 0x1B, 0x1F, 0x1F};

/**************************                   Function bodies                   **************************/

// Body of initialize function
void A_APPLICATION_VOID_INIT(void)
{
	// initialize LEDs needed
	LED_Init(YLW_LED_PORT, YLW_LED_PIN);
	LED_Init(RED_LED_PORT, RED_LED_PIN);

	// initialize Buzzer
	Buzzer_Init(BZR_PORT, BZR_PIN);

	// initialize LCD
	LCD_init();

	// initialize ADC
	ADC_Init();

	// initialize External interrupt
	INT0_init(RISING_EDGE_TRIGGER, INPUT_PIN);

	// initialize keypad
	Keypad_init();

	// initialize of special characters
	LCD_GenerateCharacterCGRAM(GBX_SELECTED, E_CHAR_GBX_SELECTED);
	LCD_GenerateCharacterCGRAM(PAGE_SELECTED, E_CHAR_PAGE_SELECTED);
	LCD_GenerateCharacterCGRAM(PAGE_NOT_SELECTED, E_CHAR_PAGE_NOT_SELECTED);
	LCD_GenerateCharacterCGRAM(INVERTED_A, E_CHAR_PAGE_INV_A);
	LCD_GenerateCharacterCGRAM(INVERTED_L, E_CHAR_PAGE_INV_L);
	LCD_GenerateCharacterCGRAM(INVERTED_E, E_CHAR_PAGE_INV_E);
	LCD_GenerateCharacterCGRAM(INVERTED_R, E_CHAR_PAGE_INV_R);
	LCD_GenerateCharacterCGRAM(INVERTED_T, E_CHAR_PAGE_INV_T);
}

/************************** LCD screen select function **************************/
void A_APPLICATION_VOID_MAIN_LCD_SCREEN_SELECT()
{
	uint8 static  LOCAL_PLACEHOLDER1 = NO_Condition;
	uint8 static  LOCAL_PLACEHOLDER2 = NO_Condition;
	uint8 static  LOCAL_PLACEHOLDER3 = NO_Condition;
	uint8 static  LOCAL_PLACEHOLDER4 = NO_Condition;

	if (LCD_PAGE_STATE == E_LCD_PAGE_CCSBA)
	{
		if (LCD_PAGE_STATE == E_LCD_PAGE_CCSBA)
		{
			if (LOCAL_PLACEHOLDER1 == 0)
			{
				A_APPLICATION_VOID_CCSBA_PAGE_DISPLAY();
				LOCAL_PLACEHOLDER1 = 1;

			}


			else
			{
				LOCAL_PLACEHOLDER1 = 0;
				A_APPLICATION_VOID_LCD_VARIABLE_CLEAR();
			}
		}

	}

	if (LCD_PAGE_STATE == E_LCD_PAGE_INFO)
	{
		if (LCD_PAGE_STATE == E_LCD_PAGE_INFO)
		{
			if (LOCAL_PLACEHOLDER2 == 0)
			{

				LOCAL_PLACEHOLDER2 = 1;

			}

		}
		else
		{
			LOCAL_PLACEHOLDER2 = 0;
			A_APPLICATION_VOID_LCD_VARIABLE_CLEAR();
		}
	}



	if (LCD_PAGE_STATE == E_LCD_PAGE_MAIN)
	{
		if (LCD_PAGE_STATE == E_LCD_PAGE_MAIN)
		{
			if (LOCAL_PLACEHOLDER3 == 0)
			{

				LOCAL_PLACEHOLDER3 = 1;

			}

		}
		else
		{
			LOCAL_PLACEHOLDER3 = 0;
			A_APPLICATION_VOID_LCD_VARIABLE_CLEAR();
		}
	}


	if (LCD_PAGE_STATE == E_LCD_PAGE_SL)
	{
		if (LCD_PAGE_STATE == E_LCD_PAGE_SL)
		{
			if (LOCAL_PLACEHOLDER4 == 0)
			{
				A_APPLICATION_VOID_SL_PAGE_DISPLAY();
				LOCAL_PLACEHOLDER4 = 1;

			}


		}
		else
		{
			LOCAL_PLACEHOLDER4 = 0;
			A_APPLICATION_VOID_LCD_VARIABLE_CLEAR();
		}
	}







}

/************************** Keypad button read check function **************************/
void A_APPLICATION_VOID_KEYPAD_BUTTON_READ(void)
{
	KEYPAD_PRESSED = Keypad_GetPressedKey();

	if ((KEYPAD_PRESSED == E_KEYPAD_GEARBOX))
	{
		A_APPLICATION_VOID_GBX_CHANGE();
	}
	else
	{
		GBX_IS_STILL_PRESSED = NO_Condition;
	}

	if (KEYPAD_PRESSED == E_KEYPAD_CCS_TOG)
	{
		A_APPLICATION_VOID_CCS_CHANGE();

	}
	else
	{
		CCS_IS_STILL_PRESSED = NO_Condition;

	}

	if (KEYPAD_PRESSED == E_KEYPAD_LEFT_PAGE)
	{
		A_APPLICATION_VOID_SCREEN_SCROLL_LEFT();
	}
	else
	{

		SCREEN_LEFT_SCROLL_IS_STILL_PRESSED = NO_Condition;
	}


	if (KEYPAD_PRESSED == E_KEYPAD_RIGHT_PAGE)
	{
		A_APPLICATION_VOID_SCREEN_SCROLL_RIGHT();
	}
	else
	{
		SCREEN_RIGHT_SCROLL_IS_STILL_PRESSED = NO_Condition;
	}

	if (KEYPAD_PRESSED == E_KEYPAD_SPEED_LIMITER_DEC)
	{
	}
	else
	{
	}

	if (KEYPAD_PRESSED == E_KEYPAD_SPEED_LIMITER_TOG)
	{
		A_APPLICATION_VOID_SL_CHANGE();

	}
	else
	{
		SL_IS_STILL_PRESSED = NO_Condition;

	}

	if (KEYPAD_PRESSED == E_KEYPAD_SPEED_LIMITER_INC)
	{
		LCD_MoveCursor(2, 2);
		LCD_DisplayCharacter((KEYPAD_PRESSED + '0'));
	}
	else
	{
	}

	if (KEYPAD_PRESSED == '*')// Brake assist one
	{
		A_APPLICATION_VOID_BA_CHANGE();

	}
	else
	{
		BA_IS_STILL_PRESSED = NO_Condition;
	}
}

void A_APPLICATION_VOID_MAIN_LCD_LOAD(void)
{
	LCD_ClearScreen();

	LCD_MoveCursor(0, 6);
	LCD_DisplayString((const uint8 *)"WELCOME");
	LCD_MoveCursor(1, 6);
	LCD_DisplayString((const uint8 *)"  TO");
	LCD_MoveCursor(2, 6);
	LCD_DisplayString((const uint8 *)" YOUR");
	LCD_MoveCursor(3, 6);
	LCD_DisplayString((const uint8 *)"MERCEDES");
	
	_delay_ms(1000);

	LCD_ClearScreen();
	LCD_MoveCursor(3, 0);
	LCD_DisplayString((const uint8 *)"CCS");

	LCD_MoveCursor(3, 4);
	LCD_DisplayString((const uint8 *)"BA");

	LCD_MoveCursor(3, 8);
	LCD_DisplayString((const uint8 *)"SL");

	LCD_MoveCursor(0, 9);
	LCD_DisplayString((const uint8 *)"S: 999 Km/h");

	LCD_MoveCursor(1, 9);
	LCD_DisplayString((const uint8 *)"GBX : R N D");

	A_APPLICATION_VOID_ALERT_INVERTED();

	LCD_MoveCursor(2, 15);
	LCD_DisplayCustomCharacter(E_CHAR_GBX_SELECTED);

	LCD_MoveCursor(2, 17);
	LCD_DisplayCustomCharacter(E_CHAR_GBX_SELECTED);

	LCD_MoveCursor(2, 19);
	LCD_DisplayCustomCharacter(E_CHAR_GBX_SELECTED);

	LCD_MoveCursor(3, 16);
	LCD_DisplayCustomCharacter(E_CHAR_PAGE_SELECTED);

	LCD_MoveCursor(3, 17);
	LCD_DisplayCustomCharacter(E_CHAR_PAGE_SELECTED);

	LCD_MoveCursor(3, 18);
	LCD_DisplayCustomCharacter(E_CHAR_PAGE_SELECTED);

	LCD_MoveCursor(3, 19);
	LCD_DisplayCustomCharacter(E_CHAR_PAGE_SELECTED);

	_delay_ms(2000);
	LCD_ClearScreen();
	A_APPLICATION_VOID_MAIN_LCD_STATICS();
}

void A_APPLICATION_VOID_MAIN_LCD_STATICS(void)
{
	LCD_MoveCursor(0, 9);
	LCD_DisplayString((const uint8 *)"S:     KM/h");

	LCD_MoveCursor(1, 9);
	LCD_DisplayString((const uint8 *)"GBX : R N D");

	LCD_MoveCursor(3, 11);
	LCD_DisplayString((const uint8 *)"ALERT");
	A_APPLICATION_VOID_LCD_PAGE_DISPLAY_R2L(LCD_PAGE_STATE);
}

void A_APPLICATION_VOID_GBX_CHANGE(void)
{

	if (GBX_IS_STILL_PRESSED == NO_Condition)
	{
		GBX_IS_STILL_PRESSED = YES_Condition;

		GBX_STATE++;

		if (GBX_STATE == E_GBX_RETURN_TO_N)
		{
			GBX_STATE = E_GBX_NEUTRAL;
		}

		A_APPLICATION_VOID_GBX_DISPLAY(GBX_STATE);
	}
}
void A_APPLICATION_VOID_GBX_DISPLAY(uint8 state)
{

	switch (state)
	{
	case E_GBX_NEUTRAL:
		LCD_MoveCursor(2, 15);
		LCD_DisplayString((const uint8 *)"     ");
		LCD_MoveCursor(2, 17);
		LCD_DisplayCustomCharacter(E_CHAR_GBX_SELECTED);

		break;
	case E_GBX_DRIVE:
		LCD_MoveCursor(2, 15);
		LCD_DisplayString((const uint8 *)"     ");
		LCD_MoveCursor(2, 19);
		LCD_DisplayCustomCharacter(E_CHAR_GBX_SELECTED);

		break;
	case E_GBX_REVERSE:
		LCD_MoveCursor(2, 15);
		LCD_DisplayString((const uint8 *)"     ");
		LCD_MoveCursor(2, 15);
		LCD_DisplayCustomCharacter(E_CHAR_GBX_SELECTED);

		break;
	}
}

void A_APPLICATION_VOID_ALERT_INVERTED(void)
{

	LCD_MoveCursor(3, 11);
	LCD_DisplayCustomCharacter(E_CHAR_PAGE_INV_A);

	LCD_MoveCursor(3, 12);
	LCD_DisplayCustomCharacter(E_CHAR_PAGE_INV_L);

	LCD_MoveCursor(3, 13);
	LCD_DisplayCustomCharacter(E_CHAR_PAGE_INV_E);

	LCD_MoveCursor(3, 14);
	LCD_DisplayCustomCharacter(E_CHAR_PAGE_INV_R);

	LCD_MoveCursor(3, 15);
	LCD_DisplayCustomCharacter(E_CHAR_PAGE_INV_T);
}

void A_APPLICATION_VOID_SCREEN_SCROLL_RIGHT(void)
{
	if (SCREEN_RIGHT_SCROLL_IS_STILL_PRESSED == NO_Condition)
	{
		SCREEN_RIGHT_SCROLL_IS_STILL_PRESSED = YES_Condition;

		LCD_PAGE_STATE++;
		if (LCD_PAGE_STATE == 4)
		{
			LCD_PAGE_STATE = E_R2L_LCD_PAGE_MAIN;
		}

		A_APPLICATION_VOID_LCD_PAGE_DISPLAY_R2L(LCD_PAGE_STATE);
	}
}

void A_APPLICATION_VOID_SCREEN_SCROLL_LEFT(void)
{
	if (SCREEN_LEFT_SCROLL_IS_STILL_PRESSED == NO_Condition)
	{
		SCREEN_LEFT_SCROLL_IS_STILL_PRESSED = YES_Condition;

		LCD_PAGE_STATE++;

		if (LCD_PAGE_STATE == 4)
		{
			LCD_PAGE_STATE = E_L2R_LCD_PAGE_MAIN;
		}

		A_APPLICATION_VOID_LCD_PAGE_DISPLAY_L2R(LCD_PAGE_STATE);
	}
}

void A_APPLICATION_VOID_LCD_PAGE_DISPLAY_R2L(uint8 state)
{

	switch (state)
	{
	case E_R2L_LCD_PAGE_MAIN:
		LCD_MoveCursor(3, 16);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 17);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_SELECTED);

		LCD_MoveCursor(3, 18);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 19);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		break;
	case E_R2L_LCD_PAGE_RIGHT:
		LCD_MoveCursor(3, 16);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_SELECTED);

		LCD_MoveCursor(3, 17);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 18);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 19);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		break;
	case E_R2L_LCD_PAGE_LEFT:
		LCD_MoveCursor(3, 16);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 17);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 18);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_SELECTED);

		LCD_MoveCursor(3, 19);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);
		break;

	case E_R2L_LCD_PAGE_INFO:
		LCD_MoveCursor(3, 16);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 17);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 18);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 19);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_SELECTED);

		break;
	}
}

void A_APPLICATION_VOID_LCD_PAGE_DISPLAY_L2R(uint8 state)
{

	switch (state)
	{
	case E_L2R_LCD_PAGE_MAIN:
		LCD_MoveCursor(3, 16);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 17);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_SELECTED);

		LCD_MoveCursor(3, 18);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 19);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		break;
	case E_L2R_LCD_PAGE_RIGHT:
		LCD_MoveCursor(3, 16);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_SELECTED);

		LCD_MoveCursor(3, 17);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 18);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 19);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		break;
	case E_L2R_LCD_PAGE_LEFT:
		LCD_MoveCursor(3, 16);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 17);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 18);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_SELECTED);

		LCD_MoveCursor(3, 19);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		break;

	case E_L2R_LCD_PAGE_INFO:
		LCD_MoveCursor(3, 16);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 17);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 18);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_NOT_SELECTED);

		LCD_MoveCursor(3, 19);
		LCD_DisplayCustomCharacter(E_CHAR_PAGE_SELECTED);

		break;
	}
}

void A_APPLICATION_VOID_LCD_VARIABLE_CLEAR(void)
{
	LCD_MoveCursor(0, 0);
	LCD_DisplayString((const uint8 *)"        ");
	LCD_MoveCursor(1, 0);
	LCD_DisplayString((const uint8 *)"        ");
}

void A_APPLICATION_VOID_BA_CHANGE(void)
{
if (BA_IS_STILL_PRESSED == NO_Condition)
	{
		BA_IS_STILL_PRESSED = YES_Condition;

		BA_STATE++;

		if (BA_STATE == E_BA_RETURN_TO_ON)
		{
			BA_STATE = E_BA_ON;
		}

		A_APPLICATION_VOID_BA_DISPLAY(BA_STATE);
	}


}

void A_APPLICATION_VOID_BA_DISPLAY(uint8 state)
{

	switch (state)
	{
	case E_BA_ON:

		LCD_MoveCursor(3,5);
		LCD_DisplayString((const uint8 *)"  ");

		break;
	case E_BA_OFF:

		LCD_MoveCursor(3,5);
 		LCD_DisplayString((const uint8 *)"BA");

		break;
	}
}



void A_APPLICATION_VOID_CCS_CHANGE(void)
{

if (CCS_IS_STILL_PRESSED == NO_Condition)
	{
		CCS_IS_STILL_PRESSED = YES_Condition;

		CCS_STATE++;

		if (CCS_STATE == E_CCS_RETURN_TO_ON)
		{
			CCS_STATE = E_CCS_ON;
		}

		A_APPLICATION_VOID_CCS_DISPLAY(CCS_STATE);
	}


}

void A_APPLICATION_VOID_CCS_DISPLAY(uint8 state)
{

	switch (state)
	{
	case E_CCS_ON:

		LCD_MoveCursor(3,0);
		LCD_DisplayString((const uint8 *)"   ");

		break;
	case E_CCS_OFF:

		LCD_MoveCursor(3,0);
 		LCD_DisplayString((const uint8 *)"CCS");

		break;
	}
}


void A_APPLICATION_VOID_SL_CHANGE(void)
{

	if (SL_IS_STILL_PRESSED == NO_Condition)
	{
		SL_IS_STILL_PRESSED = YES_Condition;

		BA_STATE++;

		if (BA_STATE == E_SL_RETURN_TO_ON)
		{
			BA_STATE = E_SL_ON;
		}

		A_APPLICATION_VOID_SL_DISPLAY(BA_STATE);
	}
}
void A_APPLICATION_VOID_SL_DISPLAY(uint8 state)
{

	switch (state)
	{
	case E_BA_ON:

		LCD_MoveCursor(3,7);
		LCD_DisplayString((const uint8 *)"   ");

		break;
	case E_BA_OFF:

		LCD_MoveCursor(3,8);
 		LCD_DisplayString((const uint8 *)"SL");

		break;
	}
}

void A_APPLICATION_VOID_CCSBA_PAGE_DISPLAY(void)
{
		LCD_MoveCursor(0,0);
 		LCD_DisplayString((const uint8 *)"CCS :");
		LCD_MoveCursor(1,0);
 		LCD_DisplayString((const uint8 *)"BA :");



}
void A_APPLICATION_VOID_CCSBA_PAGE_UPDATE(uint8 state)
{

	
}

void A_APPLICATION_VOID_SL_PAGE_DISPLAY(void)
{
		LCD_MoveCursor(0,0);
 		LCD_DisplayString((const uint8 *)"SL :");
		LCD_MoveCursor(1,0);
 		LCD_DisplayString((const uint8 *)"DST    m:");



}
void A_APPLICATION_VOID_SL_PAGE_UPDATE(uint8 state)
{

	
}



