/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: Buzzer_interface.h
 *
 * Description: Header File contain function Prototype  
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "Buzzer_config.h"
#include "../../MCAL/GPIO/GPIO_interface.h"

typedef enum
{
    Buzzer_OFF ,
    Buzzer_ON
}BuzzerState_config;


/*
*   @brief : this function used to set pin that will connected to Buzzer
*   @arg1  PORTX: port of this pin will connect to Buzzer
*   @arg2  PIN: Pin of port  will connect to Buzzer
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Buzzer_Init(uint8 PORTX , uint8 PIN );

/*
*   @brief : this function used to set Buzzer state if on or off for positive logic Buzzer connection 
*   @arg1  PORTX: port of this pin will connect to Buzzer
*   @arg2  PIN: Pin of port  will connect to Buzzer
*   @arg3  State_value: state of Buzzer 
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Buzzer_OnOffPositiveLogic(uint8 PORTX , uint8 PIN ,BuzzerState_config State_value);

/*
*   @brief : this function used to set Buzzer state if on or off for negative logic Buzzer connection 
*   @arg1  PORTX: port of this pin will connect to Buzzer
*   @arg2  PIN: Pin of port  will connect to Buzzer
*   @arg3  State_value: state of Buzzer 
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Buzzer_OnOffNegativeLogic(uint8 PORTX , uint8 PIN ,BuzzerState_config State_value);

/*
*   @brief : this function used to toggle state of buzzer
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Buzzer_Toggle(uint8 PORTX , uint8 PIN);


#endif

