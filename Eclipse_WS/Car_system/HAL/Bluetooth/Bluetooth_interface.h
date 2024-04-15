/******************************************************************************
 *
 * Module: Bluetooth
 *
 * File Name: Bluetooth_private.h
 *
 * Description: Header file contain necessary definition
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef BLUETOOTH_INTERFACE_H_
#define BLUETOOTH_INTERFACE_H_
/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"

#define     DEFAULT_BUFFER_SIZE             9

void Bluetooth_Init(void);


void Bluetooth_Send(const uint8 * string);

#endif