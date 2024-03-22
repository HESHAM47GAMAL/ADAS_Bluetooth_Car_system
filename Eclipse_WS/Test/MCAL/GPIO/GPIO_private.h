 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: GPIO_private.h
 *
 * Description: Header file for AVR contain all register memmory mapped adderess for GPIO
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

// Gard file
#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_ 

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


/**************************                   Register memmory mapped GPIO                  **************************/

/*************  Disable all internal pullup resistor 	*************/
#define     SFIOR               (*(volatile uint8 *)(0x50)) 

/*************  Control PortA  	*************/
#define     DDRA                (*(volatile uint8 *)(0x3A)) 
#define     PORTA               (*(volatile uint8 *)(0x3B)) 
#define     PINA                (*(volatile uint8 *)(0x39)) 


/*************  Control PortB  	*************/
#define     DDRB                (*(volatile uint8 *)(0x37)) 
#define     PORTB               (*(volatile uint8 *)(0x38)) 
#define     PINB                (*(volatile uint8 *)(0x36)) 

/*************  Control PortC  	*************/
#define     DDRC                (*(volatile uint8 *)(0x34)) 
#define     PORTC               (*(volatile uint8 *)(0x35)) 
#define     PINC                (*(volatile uint8 *)(0x33)) 


/*************  Control PortD  	*************/
#define     DDRD                (*(volatile uint8 *)(0x31)) 
#define     PORTD               (*(volatile uint8 *)(0x32)) 
#define     PIND                (*(volatile uint8 *)(0x30))  


#endif
