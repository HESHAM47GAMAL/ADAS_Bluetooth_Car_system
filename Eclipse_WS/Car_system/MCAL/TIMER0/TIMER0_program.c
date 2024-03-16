 /******************************************************************************
 *
 * Module: TIMER0
 *
 * File Name: TIMER0_program.h
 *
 * Description: contain Implementation of TIMER0 Driver 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "TIMER0_private.h"
#include "TIMER0_interface.h"
#include "TIMER0_config.h"
#include "../GPIO/GPIO_interface.h"
#include "../../SERVICE/COMMON_MACROS.h"
#include "../../SERVICE/IVT.h"

#if(INTERUPT_STATE_T0 == Enable_Interrupt_T0)

/**************************                   Static varaible and ISR                   **************************/
static volatile void (*g_CallBackPtr_T0)(void) = NULL_PTR;

    void Timer0_SetCallBack(void(*a_ptr)(void))
    {
        /* Save the address of the Call back function in a global variable */
        g_CallBackPtr_T0 = a_ptr;
    }

    #if(TIMER0_CURRENT_MODE == T0_NORMAL_MODE)
        ISR(TIMER_0_OVF)
        {
            if(g_CallBackPtr_T0 != NULL_PTR)
            {
                g_CallBackPtr_T0();
            }
        }
    #elif(TIMER0_CURRENT_MODE == T0_CTC_MODE)
        ISR(TIMER_0_COMP)
        {
            if(g_CallBackPtr_T0 != NULL_PTR)
            {
                g_CallBackPtr_T0();
            } 
        }

    #endif

#endif

/**************************                   Extern Global variable                   **************************/
extern TIMER0_ConfigType  TIMER0_ConfigTypeParam ;




void Timer0_Init(void)
{
    /*  Set Mode For Timer0    */
#if(TIMER0_CURRENT_MODE == T0_NORMAL_MODE)
    /*  Set this bit high when mode is non PWM  */
    SET_BIT(TCCR0,FOC0);

    CLEAR_BIT(TCCR0,WGM00);
    CLEAR_BIT(TCCR0,WGM01);
    #if(INTERUPT_STATE_T0 == Enable_Interrupt_T0)
        /*  Enable Global Interrupt  */
        SET_BIT(SREG , 7);
        /*  Enable overflow Interrupt  */
        SET_BIT(TIMSK,TOIE0);
    #else
        /*  Disable overflow Interrupt  */
        CLEAR_BIT(TIMSK,TOIE0);
    #endif

#elif(TIMER0_CURRENT_MODE == T0_CTC_MODE )
    /*  Set this bit high when mode is non PWM  */
    SET_BIT(TCCR0,FOC0);

    CLEAR_BIT(TCCR0,WGM00);
    SET_BIT(TCCR0,WGM01);
    /*  Set Output Compare pin (OC0) behavior   */
    TCCR0 = (TCCR0 & 0xCF) | (TIMER0_ConfigTypeParam.CO_nonPWM_T0_value << COM00) ;
    if(TIMER0_ConfigTypeParam.CO_nonPWM_T0_value != T0_NORMAL_PORT_OPERATION )
        /*  Need to set this pin to output*/
        GPIO_SetPinDirection(PORTB_ID,PIN3_ID,OUTPUT_PIN);
    #if(INTERUPT_STATE_T0 == Enable_Interrupt_T0)
        /*  Enable Global Interrupt  */
        SET_BIT(SREG , 7);
        /*  Enable overflow Interrupt  */
        SET_BIT(TIMSK,OCIE0);
    #else
        /*  Disable overflow Interrupt  */
        CLEAR_BIT(TIMSK,OCIE0);
    #endif


#elif(TIMER0_CURRENT_MODE == T0_FAST_PWM_MODE) 
    SET_BIT(TCCR0,WGM00);
    SET_BIT(TCCR0,WGM01);
    /*  Set Output Compare pin (OC0) behavior   */
    TCCR0 = (TCCR0 & 0xCF) | (TIMER0_ConfigTypeParam.CO_PWM_T0_value << COM00) ;
    if(TIMER0_ConfigTypeParam.CO_PWM_T0_value != T0_NORMAL_PORT_OPERATION)
        /*  Need to set this pin to output*/
        GPIO_SetPinDirection(PORTB_ID,PIN3_ID,OUTPUT_PIN);  
    /*  Set Clock for Timer    */
    TCCR0 = (TCCR0 & 0xF8) | (TIMER0_ConfigTypeParam.TIMER0_CLK_value);

#elif(TIMER0_CURRENT_MODE == T0_PHASE_CORRECT_PWM_MODE) 
    SET_BIT(TCCR0,WGM00);
    CLEAR_BIT(TCCR0,WGM01);
    /*  Set Output Compare pin (OC0) behavior   */
    TCCR0 = (TCCR0 & 0xCF) | (TIMER0_ConfigTypeParam.CO_PWM_T0_value << COM00) ;
    if(TIMER0_ConfigTypeParam.CO_PWM_T0_value != T0_NORMAL_PORT_OPERATION)
        /*  Need to set this pin to output*/
        GPIO_SetPinDirection(PORTB_ID,PIN3_ID,OUTPUT_PIN);  
    /*  Set Clock for Timer    */
    TCCR0 = (TCCR0 & 0xF8) | (TIMER0_ConfigTypeParam.TIMER0_CLK_value);

#endif


    /*  Set TCNT0 value to Zero*/
    Timer0_UpdateValue(0) ;
}



void Timer0_UpdateValue(uint8 Register_value)
{
    TCNT0 = Register_value;
}


void Timer0_StopClock(void)
{
    TCCR0 = TCCR0 & (0xF8);
}


void Timer0_ProvideClock(void)
{
    TCCR0 = (TCCR0 & 0xF8) | (TIMER0_ConfigTypeParam.TIMER0_CLK_value);
}


#if(TIMER0_CURRENT_MODE == T0_NORMAL_MODE)

    #if(INTERUPT_STATE_T0 == Disable_Interrupt_T0)

        void Timer0_DelayOVFPolling(void)
        {
            Timer0_ProvideClock();
            /*  Loop in flag of overflow    */
            while(BIT_IS_CLEAR(TIFR,TOV0));

            /*  Clear flag by write one  */
            SET_BIT(TIFR,TOV0);
            Timer0_StopClock();
        }

    #elif(INTERUPT_STATE_T0 == Enable_Interrupt_T0)

        void Timer0_DelayOVFInterrupt(void)
        {
            Timer0_ProvideClock();
        }


        void Timer0_OVFDisableInterrupt(void)
        {
            /*  Disable overflow Interrupt  */
                CLEAR_BIT(TIMSK,TOIE0);   
        }

        void Timer0_OVFEnableInterrupt(void)
        {
            SET_BIT(TIMSK,TOIE0);   
        }

    #endif

#elif(TIMER0_CURRENT_MODE == T0_CTC_MODE)

void Timer0_OutputCompareRegisterUpdate(uint8 Compare_value)
{
    OCR0 = Compare_value;
}

void Timer0_CTCWaveGeneration(uint8 Ticks)
{
    Timer0_ProvideClock();
    OCR0 = Ticks ;
}

    #if(INTERUPT_STATE_T0 == Disable_Interrupt_T0)

        void Timer0_DelayCTCPolling(void)
        {
            Timer0_ProvideClock();
            /*  Loop in flag of compare match    */
            while(BIT_IS_CLEAR(TIFR,OCF0));
            /*  Clear flag by write one  */
            SET_BIT(TIFR,OCF0);
            Timer0_StopClock();
        }

    #elif(INTERUPT_STATE_T0 == Enable_Interrupt_T0)

        void Timer0_DelayCTCInterrupt(void)
        {
            Timer0_ProvideClock();
        }

        void Timer0_CTCDisableInterrupt(void)
        {
            /*  Disable overflow Interrupt  */
            CLEAR_BIT(TIMSK,OCIE0); 
        }

        void Timer0_CTCEnableInterrupt(void)
        {
            SET_BIT(TIMSK,OCIE0); 
        }


    #endif

#elif(TIMER0_CURRENT_MODE == T0_FAST_PWM_MODE)

    void Timer0_FastPWMSetOCR(uint8 OCR_Register_value)
    {
        OCR0 = OCR_Register_value;
    }

    void Timer0_FastPWMSetDutyCycle(uint8 DutyCycle_value)
    {
        OCR0 = ( ((uint16)(255)) * DutyCycle_value ) / 100 ;
    }

#elif(TIMER0_CURRENT_MODE == T0_PHASE_CORRECT_PWM_MODE)

    void Timer0_PhaseCorrectPWMSetOCR(uint8 OCR_Register_value)
    {
        OCR0 = OCR_Register_value;
    }

    void Timer0_PhaseCorrectPWMSetDutyCycle(uint8 DutyCycle_value)
    {
        OCR0 = ( ((uint16)(255)) * DutyCycle_value ) / 100 ;
    }
#endif
