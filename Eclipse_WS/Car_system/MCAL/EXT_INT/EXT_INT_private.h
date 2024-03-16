 /******************************************************************************
 *
 * Module: External Interrupt
 *
 * File Name: EXT_INT_private.h
 *
 * Description: Header file for AVR contain all register memmory mapped adderess for External Interrupt
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

// Gard file
#ifndef  EXT_INT_PRIVATE_H
#define EXT_INT_PRIVATE_H

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


/**************************                   Definitions                   **************************/



#define MCUCR              (* (volatile uint8 *) (0x55))
#define MCUCSR             (* (volatile uint8 *) (0x54))
#define GICR               (* (volatile uint8 *) (0x5B))
#define GIFR               (* (volatile uint8 *) (0x5A))

#define ISC00                   0
#define ISC10                   2

#define ISC2                    6


#define INT0_bit                    6
#define INT1_bit                    7
#define INT2_bit                    5



#endif