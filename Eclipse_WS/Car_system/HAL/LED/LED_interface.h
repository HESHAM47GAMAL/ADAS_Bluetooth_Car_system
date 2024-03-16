/******************************************************************************
 *
 * Module: LED
 *
 * File Name: LED_interface.h
 *
 * Description: Header File contain function Prototype  
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/**************************                   INCLUDES                   **************************/

#include "../../SERVICE/STD_TYPES.h"
#include "LED_config.h"
#include "../../MCAL/GPIO/GPIO_interface.h"

typedef enum
{
    LED_OFF ,
    LED_ON
}LEDState_config;


/*
*   @brief : this function used to set pin that will connected to leds
*   @arg1  PORTX: port of this pin will connect to LED
*   @arg2  PIN: Pin of port  will connect to LED
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LED_Init(uint8 PORTX , uint8 PIN );

/*
*   @brief : this function used to set led state if on or off for positive logic led connection 
*   @arg1  PORTX: port of this pin will connect to LED
*   @arg2  PIN: Pin of port  will connect to LED
*   @arg3  State_value: state of led 
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LED_OnOffPositiveLogic(uint8 PORTX , uint8 PIN ,LEDState_config State_value);

/*
*   @brief : this function used to set led state if on or off for negative logic led connection 
*   @arg1  PORTX: port of this pin will connect to LED
*   @arg2  PIN: Pin of port  will connect to LED
*   @arg3  State_value: state of led 
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LED_OnOffNegativeLogic(uint8 PORTX , uint8 PIN ,LEDState_config State_value);

/*
*   @brief : this function used to initailize Servo as at same time initialize Timer 1 
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LED_Toggle(uint8 PORTX , uint8 PIN);

#endif

