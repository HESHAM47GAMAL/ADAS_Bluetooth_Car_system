 /******************************************************************************
 *
 * Module: TIMER0
 *
 * File Name: Timer0_private.h
 *
 * Description: Header file for AVR contain all register memmory mapped adderess for Timer0
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

// Gard file
#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


#define TCCR0                  (* (volatile uint8 *) (0x53) )
#define TCNT0                  (* (volatile uint8 *) (0x52) )
#define OCR0                   (* (volatile uint8 *) (0x5C) )
#define TIMSK                  (* (volatile uint8 *) (0x59) )
#define TIFR                   (* (volatile uint8 *) (0x58) )
#define SREG                   (* (volatile uint8 *) (0x5F) )

#define WGM01       3
#define WGM00       6
#define FOC0        7
#define COM00       4

#define TOIE0       0
#define OCIE0       1

#define TOV0        0
#define OCF0        1

#endif