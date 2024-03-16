/******************************************************************************
 *
 * Module: BUTTON
 *
 * File Name: BUTTON_interface.h
 *
 * Description: Header File contain function Prototype  
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef BUTTON_INTERFACE_H_
#define BUTTON_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "BUTTON_config.h"
#include "../../MCAL/GPIO/GPIO_interface.h"


void BUTTON_Init(uint8 PORTX ,uint8 PIN ,GPIO_PinDirectionTypes typeOfInput );

uint8 BUTTON_GetValue(uint8 PORTX ,uint8 PIN );



#endif