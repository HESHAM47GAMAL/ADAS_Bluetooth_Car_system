/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ULTRASONIC_interface.h
 *
 * Description: Header file contain necessary definition
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_
/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


/**************************                   Prototypes                   **************************/

/*
*   @brief : this function use to make make Initialization Ultrasonic by initialize Timer1 (⚠️You need to go to Timer1_config.h and .c to set prebuild config for ICU) 
    and Initilaize Trigger pin that You need to configure it in Ultrasonic_config.h
    and set call back function that will be called to get distance
*   @args  : void
*   @return: void
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Ultrasonic_Init(void);


/*
*   @brief : this function used to current distance ultasonic read it and it use Polling technique
*   @args  : void
*   @return: distance catched 
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
float64 Ultrasonic_Distance(void);



#endif

