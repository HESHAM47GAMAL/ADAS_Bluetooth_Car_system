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
	
	while(1)
	{
		 A_APPLICATION_sint8_LCD_PAGE_UPDATE();
		 A_APPLICATION_sint8_LCD_PAGE_UPDATE2();

	}



}
