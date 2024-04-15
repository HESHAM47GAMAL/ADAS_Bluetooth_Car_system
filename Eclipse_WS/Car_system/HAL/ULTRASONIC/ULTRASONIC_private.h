/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ULTRASONIC_private.h
 *
 * Description: Header file as have function Prototype and Macros as can't called by user
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef ULTRASONIC_PRIVATE_H_
#define ULTRASONIC_PRIVATE_H_

/*
*   @brief : this function used to logic high for ultrasonic for specific time 
*   @args  : void
*   @return: void
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Ultrasonic_Trigger(void);

/*
*   @brief : this function used to to handle interrupt of ICU and proccess it to get distance 
*   @args  : void
*   @return: void
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void ULtrasonic_SignalProcessing(void);

#endif