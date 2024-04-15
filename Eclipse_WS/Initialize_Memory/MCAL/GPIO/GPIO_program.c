 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: GPIO_program.c
 *
 * Description: implementation for function for  GPIO
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/

#include "GPIO_private.h"
#include "GPIO_interface.h"
#include "GPIO_config.h"
#include "../../SERVICE/COMMON_MACROS.h"


/**************************                   Extern Global variable                   **************************/

// Here write all configuration you want for pins
extern GPIO_PORT_PIN_config GPIO_configParam [Configuration_NUM]  ;  // exist in GPIO_config.h


/**************************                   Functions Definition                   **************************/


void GPIO_init(void)
{
#if (Param_Disable_All_PULLUP_resistor == Disable_PullUp_resistor)
	SET_BIT(SFIOR,PUD);
#endif
	for(uint8 it = 0 ; it < Configuration_NUM ; it++)
	{
		if(GPIO_configParam[it].PIN_SELECT == PINS_ALL) // configure all port
		{
			GPIO_SetPortDirection(GPIO_configParam[it].PORT_Selected , GPIO_configParam[it].INPUT_OUTPUT);
		}
		else  // configure pin from port
		{
			GPIO_SetPinDirection(GPIO_configParam[it].PORT_Selected , GPIO_configParam[it].PIN_SELECT , GPIO_configParam[it].INPUT_OUTPUT);
		}
	}

}




void GPIO_SetPinDirection(uint8 PORTX , uint8 PIN ,GPIO_PinDirectionTypes PinDirction )
{

#if (Param_Disable_All_PULLUP_resistor == Disable_PullUp_resistor)
	SET_BIT(SFIOR,PUD);
#endif
	if(PORTX >= NUM_PORT  || PIN >= NUM_FOR_PINS_PER_PORT)
	{
		/* Do nothing */
	}
	else
	{
		switch(PORTX)
		{
			case PORTA_ID :
				if(PinDirction == INPUT_PIN)
				{
					CLEAR_BIT( DDRA , PIN );
					CLEAR_BIT( PORTA ,PIN );
				}
				else if(PinDirction == INPUT_PIN_PULLUP)
				{
					CLEAR_BIT( DDRA , PIN );
					SET_BIT( PORTA , PIN );
				}
				else if(PinDirction == OUTPUT_PIN)
				{
					SET_BIT( DDRA , PIN );
				}
				break;

			case PORTB_ID :
				if(PinDirction == INPUT_PIN)
				{
					CLEAR_BIT( DDRB , PIN );
					CLEAR_BIT( PORTB ,PIN );
				}
				else if(PinDirction == INPUT_PIN_PULLUP)
				{
					CLEAR_BIT( DDRB , PIN );
					SET_BIT( PORTB , PIN );
				}
				else if(PinDirction == OUTPUT_PIN)
				{
					SET_BIT( DDRB , PIN );
				}
				break;

			case PORTC_ID :
				if(PinDirction == INPUT_PIN)
				{
					CLEAR_BIT( DDRC , PIN );
					CLEAR_BIT( PORTC ,PIN );
				}
				else if(PinDirction == INPUT_PIN_PULLUP)
				{
					CLEAR_BIT( DDRC , PIN );
					SET_BIT( PORTC , PIN );
				}
				else if(PinDirction == OUTPUT_PIN)
				{
					SET_BIT( DDRC , PIN );
				}
				break;

			case PORTD_ID :
				if(PinDirction == INPUT_PIN)
				{
					CLEAR_BIT( DDRD , PIN );
					CLEAR_BIT( PORTD ,PIN );
				}
				else if(PinDirction == INPUT_PIN_PULLUP)
				{
					CLEAR_BIT( DDRD , PIN );
					SET_BIT( PORTD , PIN );
				}
				else if(PinDirction == OUTPUT_PIN)
				{
					SET_BIT( DDRD , PIN );
				}
				break;
		}
	}
}


uint8 GPIO_ReadPin(uint8 PORTX , uint8 PIN )
{
    uint8 returned_value = LOGIC_LOW ;

    if(PORTX >= NUM_PORT  || PIN >= NUM_FOR_PINS_PER_PORT)
    {
        /* Do Nothing*/
    }
    else 
    {
        switch (PORTX)
        {
            case PORTA_ID :
                if( BIT_IS_SET(PINA,PIN) )
                    returned_value = LOGIC_HIGH;
                else
                    returned_value = LOGIC_LOW ;
                break ;

            case PORTB_ID :
                if( BIT_IS_SET(PINB,PIN) )
                    returned_value = LOGIC_HIGH;
                else
                    returned_value = LOGIC_LOW ;

                break ;

            case PORTC_ID :
                if( BIT_IS_SET(PINC,PIN) )
                    returned_value = LOGIC_HIGH;
                else
                    returned_value = LOGIC_LOW ;

                break ;

            case PORTD_ID :
                if( BIT_IS_SET(PIND,PIN) )
                    returned_value = LOGIC_HIGH;
                else
                    returned_value = LOGIC_LOW ;

                break ;

        }
    }

    return returned_value ;
}



void GPIO_WritePin(uint8 PORTX , uint8 PIN ,uint8 value)
{
    if(PORTX >= NUM_PORT  || PIN >= NUM_FOR_PINS_PER_PORT)
    {
        /* Do Nothing*/
    }
    else
    {
        switch(PORTX)
        {
            case PORTA_ID :
                if(value == LOGIC_HIGH)
                    SET_BIT(PORTA,PIN);
                else if(value == LOGIC_LOW)
                    CLEAR_BIT(PORTA,PIN);
                break;


            case PORTB_ID :
                if(value == LOGIC_HIGH)
                    SET_BIT(PORTB,PIN);
                else if(value == LOGIC_LOW)
                    CLEAR_BIT(PORTB,PIN);
                break;  

            case PORTC_ID :
                if(value == LOGIC_HIGH)
                    SET_BIT(PORTC,PIN);
                else if(value == LOGIC_LOW)
                    CLEAR_BIT(PORTC,PIN);
                break;

            case PORTD_ID :
                if(value == LOGIC_HIGH)
                    SET_BIT(PORTD,PIN);
                else if(value == LOGIC_LOW)
                    CLEAR_BIT(PORTD,PIN);
                break;

        }
    }
}


void GPIO_TogglePin(uint8 PORTX , uint8 PIN )
{
if(PORTX >= NUM_PORT  || PIN >= NUM_FOR_PINS_PER_PORT)
    {
        /* Do Nothing*/
    }
    else
    {
        switch(PORTX)
        {
            case PORTA_ID :
                TOGGLE_BIT(PORTA,PIN);
                break;


            case PORTB_ID :
                TOGGLE_BIT(PORTB,PIN);
                break;  

            case PORTC_ID :
                TOGGLE_BIT(PORTC,PIN);
                break;

            case PORTD_ID :
                TOGGLE_BIT(PORTD,PIN);
                break;

        }
    }

}

void GPIO_SetPortDirection(uint8 PORTX , GPIO_PortDirectionTypes PortDirection)
{
#if (Param_Disable_All_PULLUP_resistor == Disable_PullUp_resistor)
	SET_BIT(SFIOR,PUD);
#endif

	if(PORTX >= NUM_PORT)
	{
		/** Do Nothing **/
	}
	else
	{
		switch(PORTX)
		{
			case PORTA_ID :
					if(PortDirection == INPUT_PORT)
					{
						DDRA = ZEROS_WORD ; // set port input
						PORTA = ZEROS_WORD ; //disable pullup resistor

					}
					else if(PortDirection == INPUT_PORT_PULLUP)
					{
						DDRA = ZEROS_WORD ;// set port input
						PORTA = ONES_WORD ; //enable pullup resistor

					}
					else if(PortDirection == OUTPUT_PORT )
					{
						DDRA = ONES_WORD ;
					}
					break;

			case PORTB_ID :
					if(PortDirection == INPUT_PORT)
					{
						DDRB = ZEROS_WORD ; // set port input
						PORTB = ZEROS_WORD ; //disable pullup resistor

					}
					else if(PortDirection == INPUT_PORT_PULLUP)
					{
						DDRB = ZEROS_WORD ;// set port input
						PORTB = ONES_WORD ; //enable pullup resistor

					}
					else if(PortDirection == OUTPUT_PORT )
					{
						DDRB = ONES_WORD ;
					}
					break;

			case PORTC_ID :
					if(PortDirection == INPUT_PORT)
					{
						DDRC = ZEROS_WORD ; // set port input
						PORTC = ZEROS_WORD ; //disable pullup resistor

					}
					else if(PortDirection == INPUT_PORT_PULLUP)
					{
						DDRC = ZEROS_WORD ;// set port input
						PORTC = ONES_WORD ; //enable pullup resistor

					}
					else if(PortDirection == OUTPUT_PORT )
					{
						DDRC = ONES_WORD ;
					}
					break;

			case PORTD_ID :
					if(PortDirection == INPUT_PORT)
					{
						DDRD = ZEROS_WORD ; // set port input
						PORTD = ZEROS_WORD ; //disable pullup resistor

					}
					else if(PortDirection == INPUT_PORT_PULLUP)
					{
						DDRD = ZEROS_WORD ;// set port input
						PORTD = ONES_WORD ; //enable pullup resistor

					}
					else if(PortDirection == OUTPUT_PORT )
					{
						DDRD = ONES_WORD ;
					}
					break;
		}
	}
}


uint8 GPIO_ReadPort(uint8 PORTX)
{
    uint8 returned_value = 0 ;
    if(PORTX >= NUM_PORT )
    {
        /* Do Nothing  */
    }
    else
    {
        switch(PORTX)
        {
            case PORTA_ID :
                returned_value = PINA ;
                break ;
            
            case PORTB_ID :
                returned_value = PINB ;
                break ; 


            case PORTC_ID :
                returned_value = PINC ;
                break ;


            case PORTD_ID :
                returned_value = PIND ;
                break ;

        }
    }


    return returned_value ;
}



void GPIO_WritePort(uint8 PORTX  ,uint8 value)
{
    if(PORTX >= NUM_PORT )
    {
        /* Do Nothing  */
    }
    else
    {
        switch(PORTX)
        {
            case PORTA_ID :
                PORTA = value ;
                break ;

            case PORTB_ID :
                PORTB = value ;
                break ;


            case PORTC_ID :
                PORTC = value ;
                break ;

            case PORTD_ID :
                PORTD = value ;
                break ;
        }
    }
}


void GPIO_TogglePort(uint8 PORTX)
{
    if(PORTX >= NUM_PORT )
    {
        /* Do Nothing  */
    }
    else
    {
        switch(PORTX)
        {
            case PORTA_ID :
                PORTA ^= 0xFF ;
                break ;

            case PORTB_ID :
                PORTB ^= 0xFF ;
                break ;


            case PORTC_ID :
                PORTC ^= 0xFF ;
                break ;

            case PORTD_ID :
                PORTD ^= 0xFF ;
                break ;
        }
    }	
}


