/******************************************************************************
 *
 * Module: Potentiometer
 *
 * File Name: POT_interface.h
 *
 * Description: Header File contain function Prototype  
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef POTENTIOMETER_INTERFACE_H_
#define POTENTIOMETER_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "POT_config.h"
#include "../../MCAL/GPIO/GPIO_interface.h"

void POT_Init(uint8 ADC_Channel_value );


uint16 POT_GetValue(uint8 ADC_Channel_value );


#endif