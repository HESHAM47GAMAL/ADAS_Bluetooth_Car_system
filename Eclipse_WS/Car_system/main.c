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
	App_Init();
	
	while(1)
	{
		StateMachineUpdate();

	}



}
