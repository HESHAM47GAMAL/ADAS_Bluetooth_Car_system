/******************************************************************************
 *
 * Module: Potentiometer
 *
 * File Name: POT_program.c
 *
 * Description: source file for implementation
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/

#include "POT_interface.h"


void POT_Init(uint8 ADC_Channel_value )
{
    /*  Set pin As Input PIN */
    GPIO_SetPinDirection(PORTA_ID,ADC_Channel_value,INPUT_PIN);

}


uint16 POT_GetValue(uint8 ADC_Channel_value )
{
    
}