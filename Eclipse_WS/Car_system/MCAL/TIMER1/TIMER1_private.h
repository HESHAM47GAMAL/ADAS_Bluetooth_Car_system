 /******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: Timer1_private.h
 *
 * Description: Header file for AVR contain all register memmory mapped adderess for Timer1
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

// Gard file
#ifndef  TIMER1_PRIVATE_H
#define TIMER1_PRIVATE_H

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"

#define TCCR1A                  (* (volatile uint8 *) (0x4F) )
#define TCCR1B                  (* (volatile uint8 *) (0x4E) )

#define TCNT1                   (* (volatile uint16 *) (0x4C) )
#define TCNT1L                  (* (volatile uint8 *) (0x4C) )
#define TCNT1H                  (* (volatile uint8 *) (0x4D) )

#define OCR1A                   (* (volatile uint16 *) (0x4A) )
#define OCR1AL                  (* (volatile uint8 *) (0x4A) )
#define OCR1AH                  (* (volatile uint8 *) (0x4B) )

#define OCR1B                   (* (volatile uint16 *) (0x48) )
#define OCR1BL                  (* (volatile uint8 *) (0x48) )
#define OCR1BH                  (* (volatile uint8 *) (0x49) )

#define ICR1                   (* (volatile uint16 *) (0x46) )
#define ICR1L                  (* (volatile uint8 *) (0x46) )
#define ICR1H                  (* (volatile uint8 *) (0x47) )

#define TIMSK                  (* (volatile uint8 *) (0x59) )
#define TIFR                   (* (volatile uint8 *) (0x58) )

#define SREG                   (* (volatile uint8 *) (0x5F) )


#define FOC1A     3
#define FOC1B     2
#define WGM10     0
#define WGM11     1
#define COM1B0    4
#define COM1A0    6



#define WGM12     3
#define WGM13     4
#define ICES1     6


#define TOIE1     2
#define TICIE1    5
#define OCIE1A    4
#define OCIE1B    3


#define TOV1      2
#define OCF1B     3
#define OCF1A     4

#endif