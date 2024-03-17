 /******************************************************************************
 *
 * Module: Keypad
 *
 * File Name: Keypad_interface.h
 *
 * Description: Header that contain function prototype
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"

/**************************                   Function Declaration                   **************************/

/*
*   @brief : this function used to initialize port that will be connected to keypad
*   @args  : void
*   @return: void
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Keypad_init(void);



/*
*   @brief : this function used to return value if pressed key (⛔Note that will stay at this function until key pressed)
*   @args  : void
*   @return: key pressed value
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
sint8 Keypad_GetPressedKey(void);

#endif