/*
 * main.c
 *
 *  Created on: Mar 7, 2024
 *      Author: moham
 */


#include "Application/Application_interface.h"
uint8 Adc_value_pure = 0;
int main()
{
	/*	Make Initialize for Every thing*/
	A_APPLICATION_VOID_INIT();
	A_APPLICATION_VOID_MAIN_LCD_LOAD();
	A_APPLICATION_VOID_GBX_DISPLAY(0);


	while(1)
	{
		A_APPLICATION_VOID_KEYPAD_BUTTON_READ();
		A_APPLICATION_VOID_MAIN_LCD_SCREEN_SELECT();


	}



}
