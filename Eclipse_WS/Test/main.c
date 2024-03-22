/*
 * main.c
 *
 *  Created on: Mar 18, 2024
 *      Author: moham
 */

#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/Timer0/TIMER0_interface.h"
#include "SERVICE/IVT.h"

volatile uint8 OverFlow_Count = 0 ;

void TurnOn(void)
{
	OverFlow_Count++;
	if(OverFlow_Count == 122)
	{
		GPIO_TogglePin(PORTC_ID,PIN0_ID);
		OverFlow_Count = 0;
	}
}


int main()
{
	sei();
	Timer0_Init();
	GPIO_init();
	GPIO_WritePin(PORTC_ID,PIN0_ID, LOGIC_LOW);
	GPIO_WritePin(PORTA_ID,PIN0_ID, LOGIC_LOW);
	GPIO_WritePin(PORTA_ID,PIN1_ID, LOGIC_HIGH);

	Timer0_SetCallBack(TurnOn);
	Timer0_Enable_OVR_Flow_Interrupt();
	Timer0_FastPWMSetOCR(30);
	while(1)
	{

	}
}
