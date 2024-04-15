 /******************************************************************************
 *
 * Module: USART
 *
 * File Name: USART_private.h
 *
 * Description: Header file for AVR contain all register memmory mapped adderess for USART
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

// Gard file
#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


#define UDR                     (*(volatile uint8 *) (0x2C))
#define UCSRA                   (*(volatile uint8 *) (0x2B))
#define UCSRB                   (*(volatile uint8 *) (0x2A))
#define UCSRC                   (*(volatile uint8 *) (0x40))

#define UBRRL                   (*(volatile uint8 *) (0x29))
#define UBRRH                   (*(volatile uint8 *) (0x40))


#define RXC                7
#define UDRE               5
#define U2X                1

#define RXCIE              7


#define RXEN               4
#define TXEN               3
#define UCSZ2              2
#define RXB8               1
#define TXB8               0


#define URSEL              7
#define UMSEL              6
#define UPM0               4
#define USBS               3
#define UCSZ0              1
#define UCPOL              0


#endif