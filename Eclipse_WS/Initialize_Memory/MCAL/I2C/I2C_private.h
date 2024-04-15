 /******************************************************************************
 *
 * Module: I2C
 *
 * File Name: I2C_private.h
 *
 * Description: Header file for AVR contain all register memmory mapped adderess for I2C
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

// Gard file
#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_


/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


#define TWBR          ( *(volatile uint8 * ) (0x20) )
#define TWCR          ( *(volatile uint8 * ) (0x56) )
#define TWSR          ( *(volatile uint8 * ) (0x21) )
#define TWDR          ( *(volatile uint8 * ) (0x23) )
#define TWAR          ( *(volatile uint8 * ) (0x22) )



#define  TWPS0             0


#define TWA0               1
#define TWGCE              0

#define TWINT              7
#define TWEA               6
#define TWSTA              5
#define TWSTO              4
#define TWEN               2

#endif