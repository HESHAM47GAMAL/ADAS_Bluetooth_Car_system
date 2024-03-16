/******************************************************************************
 *
 * Module: BUTTON
 *
 * File Name: BUTTON_program.c
 *
 * Description: source file for implementation
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#include "BUTTON_interface.h"

void BUTTON_Init(uint8 PORTX ,uint8 PIN ,GPIO_PinDirectionTypes typeOfInput )
{
    GPIO_SetPinDirection(PORTX,PIN,typeOfInput);
}

uint8 BUTTON_GetValue(uint8 PORTX ,uint8 PIN )
{
    return GPIO_ReadPin(PORTX,PIN);
}