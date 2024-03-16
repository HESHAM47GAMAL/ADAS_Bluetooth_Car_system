/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: Buzzer_program.c
 *
 * Description: source file for implementation
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/

#include "Buzzer_interface.h"


void Buzzer_Init(uint8 PORTX , uint8 PIN )
{
    GPIO_SetPinDirection(PORTX , PIN , OUTPUT_PIN);
}


void Buzzer_OnOffPositiveLogic(uint8 PORTX , uint8 PIN ,BuzzerState_config State_value)
{
    if(State_value == Buzzer_OFF)
    {
        GPIO_WritePin(PORTX,PIN,LOGIC_LOW);
    }
    else if(State_value == Buzzer_ON)
    {
        GPIO_WritePin(PORTX,PIN,LOGIC_HIGH);
    }
}


void Buzzer_OnOffNegativeLogic(uint8 PORTX , uint8 PIN ,BuzzerState_config State_value)
{
    if(State_value == Buzzer_OFF)
    {
        GPIO_WritePin(PORTX,PIN,LOGIC_HIGH);
    }
    else if(State_value == Buzzer_ON)
    {
        GPIO_WritePin(PORTX,PIN,LOGIC_LOW);
    }
}



void Buzzer_Toggle(uint8 PORTX , uint8 PIN)
{
    GPIO_TogglePin(PORTX,PIN);
}



