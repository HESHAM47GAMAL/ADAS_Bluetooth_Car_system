 /******************************************************************************
 *
 * Module: External Interrupt
 *
 * File Name: EXT_INT_program.c
 *
 * Description: contain Implementation of External Interrupt Driver 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


/**************************                   INCLUDES                   **************************/
#include "EXT_INT_private.h"
#include "EXT_INT_interface.h"

#include "../GPIO/GPIO_interface.h"
#include "../../SERVICE/COMMON_MACROS.h"
#include "../../SERVICE/IVT.h"


/**************************                   Static varaible and ISR                   **************************/
static volatile void (*g_CallBackPtr_INT0)(void) = NULL_PTR;
static volatile void (*g_CallBackPtr_INT1)(void) = NULL_PTR;
static volatile void (*g_CallBackPtr_INT2)(void) = NULL_PTR;

ISR(INT0)
{
    if(g_CallBackPtr_INT0 != NULL_PTR)
    {
        g_CallBackPtr_INT0();
    }
}

ISR(INT1)
{
    if(g_CallBackPtr_INT1 != NULL_PTR)
    {
        g_CallBackPtr_INT1();
    }
}

ISR(INT2)
{
    if(g_CallBackPtr_INT2 != NULL_PTR)
    {
        g_CallBackPtr_INT2();
    }
}

/**************************                  Function Implement                   **************************/

void INT0_SetCallBack(void(*a_ptr)(void))
{
    g_CallBackPtr_INT0 = a_ptr ;
}

void INT1_SetCallBack(void(*a_ptr)(void))
{
    g_CallBackPtr_INT1 = a_ptr ;
}

void INT2_SetCallBack(void(*a_ptr)(void))
{
    g_CallBackPtr_INT2 = a_ptr ;
}


void INT0_init( EXT_triggerType triggerType, GPIO_PinDirectionTypes input_type)
{
    /*  Set pin as input Pin*/
    GPIO_SetPinDirection(PORTD_ID,PIN2_ID,input_type);
    /*  Set trigger type*/
    MCUCR = ( MCUCR & (0xFC) ) | (triggerType << ISC00) ;
    /*  Enable EXT Interrupt 0*/
    SET_BIT(GICR , INT0_bit);
}

void INT1_init( EXT_triggerType triggerType, GPIO_PinDirectionTypes input_type)
{
    /*  Set pin as input Pin*/
    GPIO_SetPinDirection(PORTD_ID,PIN3_ID,input_type);
    /*  Set trigger type*/
    MCUCR = ( MCUCR & (0xF3) ) | (triggerType << ISC10) ;
    /*  Enable EXT Interrupt 0*/
    SET_BIT(GICR , INT1_bit);
}


void INT2_init( EXT_triggerType triggerType, GPIO_PinDirectionTypes input_type)
{
    /*  Set pin as input Pin*/
    GPIO_SetPinDirection(PORTB_ID,PIN2_ID,input_type);
    /*  Set trigger type*/
    if(triggerType == FALLING_EDGE_TRIGGER)
        CLEAR_BIT(MCUCSR,ISC2);
    else if (triggerType == RISING_EDGE_TRIGGER)
        SET_BIT(MCUCSR,ISC2);
    /*  Enable EXT Interrupt 0*/
    SET_BIT(GICR , INT2_bit);
}


void INT0_DeInit(void)
{
    CLEAR_BIT(GICR ,INT0_bit);
}


void INT1_DeInit(void)
{
    CLEAR_BIT(GICR ,INT1_bit);
}

void INT2_DeInit(void)
{
    CLEAR_BIT(GICR ,INT2_bit);
}


