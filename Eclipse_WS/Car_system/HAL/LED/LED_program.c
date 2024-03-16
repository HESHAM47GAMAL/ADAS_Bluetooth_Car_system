/******************************************************************************
 *
 * Module: LED
 *
 * File Name: LED_program.c
 *
 * Description: source file for implementation
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


/**************************                   INCLUDES                   **************************/

#include "LED_interface.h"


void LED_Init(uint8 PORTX , uint8 PIN  )
{
    GPIO_SetPinDirection(PORTX , PIN , OUTPUT_PIN);
}

void LED_OnOffPositiveLogic(uint8 PORTX , uint8 PIN ,LEDState_config State_value)
{
    if(State_value == LED_OFF)
    {
        GPIO_WritePin(PORTX,PIN,LOGIC_LOW);
    }
    else if(State_value == LED_ON)
    {
        GPIO_WritePin(PORTX,PIN,LOGIC_HIGH);
    }


}


void LED_OnOffNegativeLogic(uint8 PORTX , uint8 PIN ,LEDState_config State_value)
{
    if(State_value == LED_OFF)
    {
        GPIO_WritePin(PORTX,PIN,LOGIC_HIGH);
    }
    else if(State_value == LED_ON)
    {
        GPIO_WritePin(PORTX,PIN,LOGIC_LOW);
    }


}


void LED_Toggle(uint8 PORTX , uint8 PIN)
{
	GPIO_TogglePin(PORTX,PIN);
}


