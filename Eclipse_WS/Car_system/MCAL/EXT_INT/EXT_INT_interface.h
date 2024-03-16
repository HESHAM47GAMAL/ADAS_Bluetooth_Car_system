 /******************************************************************************
 *
 * Module: External Interrupt
 *
 * File Name: EXT_INT_interface.h
 *
 * Description: Header contain function prototype to be used 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef EXT_INT_INTERFCAE_H_
#define EXT_INT_INTERFCAE_H_

/**************************                   INCLUDES                   **************************/

#include "../../SERVICE/STD_TYPES.h"
#include "../GPIO/GPIO_interface.h"


/**************************                   Types Declaration                   **************************/
 typedef enum
 {
	 LOW_LEVEL_TRIGGER,
	 ANY_LOGIC_CHANGE_TRIGGER,
	 FALLING_EDGE_TRIGGER,
	 RISING_EDGE_TRIGGER
 }EXT_triggerType;


/*
*   @brief : this function used to store address of function that will be stored in  pointer to function as when Interrupt happen call this function 
*   @arg1  a_ptr : pointer to function that will be called when Inteerupt happen 
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
    void INT0_SetCallBack(void(*a_ptr)(void));

    void INT1_SetCallBack(void(*a_ptr)(void));

    void INT2_SetCallBack(void(*a_ptr)(void));


/*
*   @brief : this function used to intialize interrupt 0 with edge trigger type
* ⛔Note : can be any type of  EXT_triggerType
*   @arg1  triggerType : type of trigger
*   @arg2  input_type : type of input pin (input pin or input pull up pin)
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void INT0_init( EXT_triggerType triggerType, GPIO_PinDirectionTypes input_type);

/*
*   @brief : this function used to intialize interrupt 1 with edge trigger type
* ⛔Note : can be any type of  EXT_triggerType
*   @arg1  triggerType : type of trigger
*   @arg2  input_type : type of input pin (input pin or input pull up pin)
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void INT1_init( EXT_triggerType triggerType, GPIO_PinDirectionTypes input_type);

/*
*   @brief : this function used to intialize interrupt 0 with edge trigger type
* ⛔Note : trigger can be only RISING_EDGE_TRIGGER or FALLING_EDGE_TRIGGER  whereas any another thing will ignored
*   @arg1  triggerType : type of trigger
*   @arg2  input_type : type of input pin (input pin or input pull up pin)
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void INT2_init( EXT_triggerType triggerType, GPIO_PinDirectionTypes input_type);

/*
*   @brief : this function used to disable interrupt 0
*   @args   : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void INT0_DeInit(void);

/*
*   @brief : this function used to disable interrupt 1
*   @args   : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void INT1_DeInit(void);

/*
*   @brief : this function used to disable interrupt 2
*   @args   : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void INT2_DeInit(void);


#endif