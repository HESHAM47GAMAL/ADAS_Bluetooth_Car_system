 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC_private.h
 *
 * Description: Header file for AVR contain all register memmory mapped adderess for ADC
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

// gard file 

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


/**************************                   Register memmory mapped GPIO                  **************************/

/*************  Control PortA  	*************/
#define ADMUX            (* (volatile uint8 *) (0x27) )

#define ADCSRA           (* (volatile uint8 *) (0x26) )

#define ADCL             (* (volatile uint8 *) (0x24) )

#define ADCH             (* (volatile uint8 *) (0x25) )

#define SFIOR            (* (volatile uint8 *) (0x50) )

#define ADC_REG          (* (volatile uint16 *) (0x24))

#define SREG             (* (volatile uint8 *) (0x5F) )

#define ADLAR   5
#define ADEN    7
#define ADATE   5
#define ADTS0   5
#define ADTS1   6
#define ADTS2   7
#define ADPS0   0
#define ADPS1   1
#define ADPS2   2
#define ADSC    6
#define ADIF    4
#define ADIE    3

#endif