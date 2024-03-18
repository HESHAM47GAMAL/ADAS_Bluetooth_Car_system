 /******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: TIMER1_program.c
 *
 * Description: contain Implementation of TIMER0 Driver 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "TIMER1_private.h"
#include "TIMER1_interface.h"
#include "TIMER1_config.h"
#include "../GPIO/GPIO_interface.h"
#include "../../SERVICE/COMMON_MACROS.h"
#include "../../SERVICE/IVT.h"

#if(INTERUPT_STATE_T1 == Enable_Interrupt_T1)

/**************************                   Static varaible and ISR                   **************************/
static volatile void (*g_CallBackPtr_T1)(void) = NULL_PTR;

    void Timer1_SetCallBack(void(*a_ptr)(void))
    {
        /* Save the address of the Call back function in a global variable */
        g_CallBackPtr_T1 = a_ptr;
    }

    #if((TIMER1_CURRENT_MODE == T1_NORMAL_MODE) && (NORMAL_use_T1_state == T1_TIME_DELAY))
        ISR(TIMER_1_OVF)
        {
            if(g_CallBackPtr_T1 != NULL_PTR)
            {
                g_CallBackPtr_T1();
            }
        }
    #elif((TIMER1_CURRENT_MODE == T1_NORMAL_MODE) && (NORMAL_use_T1_state == T1_ICU))
        ISR(TIMER_1_CAPT)
        {
            if(g_CallBackPtr_T1 != NULL_PTR)
            {
                g_CallBackPtr_T1();
            }   
        }
    #elif(TIMER1_CURRENT_MODE == T1_CTC_MODE)
        ISR(TIMER_1_COMPA)
        {
            if(g_CallBackPtr_T1 != NULL_PTR)
            {
                g_CallBackPtr_T1();
            } 
        }

    #endif

#endif

/**************************                   Extern Global variable                   **************************/
extern TIMER1_ConfigType  TIMER1_ConfigTypeParam ;




void Timer1_Init(void)
{
    /*  Set Mode For Timer0    */
#if(TIMER1_CURRENT_MODE == T1_NORMAL_MODE)
    /*  Set this bit high when mode is non PWM  */
    SET_BIT(TCCR1A,FOC1A);
    SET_BIT(TCCR1A,FOC1B);

    CLEAR_BIT(TCCR1A,WGM10);
    CLEAR_BIT(TCCR1A,WGM11);
    CLEAR_BIT(TCCR1B,WGM12);
    CLEAR_BIT(TCCR1B,WGM13);

    #if(NORMAL_use_T1_state == T1_ICU)
    
        /*  Set this pin as input to take signal  ICP1  */
        GPIO_SetPinDirection(PORTD_ID,PIN6_ID,INPUT_PIN);
        /*  Enable Global Interrupt  */
        SET_BIT(SREG , 7);
        /*  Enable Input capture Interrupt  */
        SET_BIT(TIMSK,TICIE1);
    
    #elif(NORMAL_use_T1_state == T1_TIME_DELAY) 
    
        #if(INTERUPT_STATE_T0 == Enable_Interrupt_T0)
            /*  Enable Global Interrupt  */
            SET_BIT(SREG , 7);
            /*  Enable overflow Interrupt  */
            SET_BIT(TIMSK,TOIE1);
        #else
            /*  Disable overflow Interrupt  */
            CLEAR_BIT(TIMSK,TOIE1);
        #endif
    #endif

#elif(TIMER1_CURRENT_MODE == T1_CTC_MODE )
    /*  Set this bit high when mode is non PWM  */
    SET_BIT(TCCR1A,FOC1A);
    SET_BIT(TCCR1A,FOC1B);
    /*  Choose which type of CTC use  */
    if(TIMER1_ConfigTypeParam.T1_CTC_Top_value == T1_TOP_equal_OCR1A)
    {
        CLEAR_BIT(TCCR1A,WGM10);
        CLEAR_BIT(TCCR1A,WGM11);
        SET_BIT(TCCR1B,WGM12);
        CLEAR_BIT(TCCR1B,WGM13);
    }
    else if (TIMER1_ConfigTypeParam.T1_CTC_Top_value == T1_Top_equal_ICR1)
    {
        CLEAR_BIT(TCCR1A,WGM10);
        CLEAR_BIT(TCCR1A,WGM11);
        SET_BIT(TCCR1B,WGM12);
        SET_BIT(TCCR1B,WGM13);
    }
    
    /*  Set Output Compare pin (OC1B) behavior   */
    TCCR1A = (TCCR1A & 0xCF) | (TIMER1_ConfigTypeParam.CO_nonPWM_T1_value << COM1B0) ;
    /*  Set Output Compare pin (OC1A) behavior   */
    TCCR1A = (TCCR1A & 0x3F) | (TIMER1_ConfigTypeParam.CO_nonPWM_T1_value << COM1A0) ;
    if(TIMER1_ConfigTypeParam.CO_nonPWM_T1_value != T1_NORMAL_PORT_OPERATION )
        /*  Need to set this pin to output  OC1B & OC1A  */
        GPIO_SetPinDirection(PORTD_ID,PIN4_ID,OUTPUT_PIN);
        GPIO_SetPinDirection(PORTD_ID,PIN5_ID,OUTPUT_PIN);
    #if(INTERUPT_STATE_T0 == Enable_Interrupt_T0)
        /*  Enable Global Interrupt  */
        SET_BIT(SREG , 7);
        /*  Enable CTC Interrupt  */
        SET_BIT(TIMSK,OCIE1A);

    #else
        /*  Disable CTC Interrupt  */
        CLEAR_BIT(TIMSK,OCIE1A);

    #endif


#elif(TIMER1_CURRENT_MODE == T1_FAST_PWM_MODE) 
    /*  Choose which type of FAST PWM  use  */
    if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_FF)
    {
        SET_BIT(TCCR1A,WGM10);
        CLEAR_BIT(TCCR1A,WGM11);
        SET_BIT(TCCR1B,WGM12);
        CLEAR_BIT(TCCR1B,WGM13);        
    }
    else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_1FF)
    {
        CLEAR_BIT(TCCR1A,WGM10);
        SET_BIT(TCCR1A,WGM11);
        SET_BIT(TCCR1B,WGM12);
        CLEAR_BIT(TCCR1B,WGM13);  
    }
    else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_3FF)
    {
        SET_BIT(TCCR1A,WGM10);
        SET_BIT(TCCR1A,WGM11);
        SET_BIT(TCCR1B,WGM12);
        CLEAR_BIT(TCCR1B,WGM13);
    }
    else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_ICR1)
    {
        CLEAR_BIT(TCCR1A,WGM10);
        SET_BIT(TCCR1A,WGM11);
        SET_BIT(TCCR1B,WGM12);
        SET_BIT(TCCR1B,WGM13);
    }
    else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_OCR1A)
    {
        SET_BIT(TCCR1A,WGM10);
        SET_BIT(TCCR1A,WGM11);
        SET_BIT(TCCR1B,WGM12);
        SET_BIT(TCCR1B,WGM13);
    }

    if(TIMER1_ConfigTypeParam.CO_used_pin_value == OC1B_pin)
        /*  Set Output Compare pin (OC1B) behavior   */
        TCCR1A = (TCCR1A & 0xCF) | (TIMER1_ConfigTypeParam.CO_PWM_T1_value << COM1B0) ;
    else if(TIMER1_ConfigTypeParam.CO_used_pin_value == OC1A_pin)
        /*  Set Output Compare pin (OC1A) behavior   */
        TCCR1A = (TCCR1A & 0x3F) | (TIMER1_ConfigTypeParam.CO_PWM_T1_value << COM1A0) ;
    else if(TIMER1_ConfigTypeParam.CO_used_pin_value == OC1A_B_pin)
    {
        /*  Set Output Compare pin (OC1B) behavior   */
        TCCR1A = (TCCR1A & 0xCF) | (TIMER1_ConfigTypeParam.CO_PWM_T1_value << COM1B0) ;
         /*  Set Output Compare pin (OC1A) behavior   */
        TCCR1A = (TCCR1A & 0x3F) | (TIMER1_ConfigTypeParam.CO_PWM_T1_value << COM1A0) ;
    }

    if(TIMER1_ConfigTypeParam.CO_PWM_T1_value != T1_NORMAL_PORT_OPERATION)
    { /*  Need to set this pin to output  OC1B & OC1A  */
        if(TIMER1_ConfigTypeParam.CO_used_pin_value == OC1B_pin)
            GPIO_SetPinDirection(PORTD_ID,PIN4_ID,OUTPUT_PIN);
        else if(TIMER1_ConfigTypeParam.CO_used_pin_value == OC1A_pin)
            GPIO_SetPinDirection(PORTD_ID,PIN5_ID,OUTPUT_PIN);  
        else if(TIMER1_ConfigTypeParam.CO_used_pin_value == OC1A_B_pin)
        {
            GPIO_SetPinDirection(PORTD_ID,PIN4_ID,OUTPUT_PIN);
            GPIO_SetPinDirection(PORTD_ID,PIN5_ID,OUTPUT_PIN);  
        }
    }   
        
    /*  Set Clock for Timer    */
    TCCR1B = (TCCR1B & 0xF8) | (TIMER1_ConfigTypeParam.TIMER1_CLK_value);

#elif(TIMER1_CURRENT_MODE == T1_PHASE_CORRECT_PWM_MODE) 
    /*  Choose which type of phase correct PWM  use  */
    if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_FF)
    {
        SET_BIT(TCCR1A,WGM10);
        CLEAR_BIT(TCCR1A,WGM11);
        CLEAR_BIT(TCCR1B,WGM12);
        CLEAR_BIT(TCCR1B,WGM13);        
    }
    else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_1FF)
    {
        CLEAR_BIT(TCCR1A,WGM10);
        SET_BIT(TCCR1A,WGM11);
        CLEAR_BIT(TCCR1B,WGM12);
        CLEAR_BIT(TCCR1B,WGM13);  
    }
    else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_3FF)
    {
        SET_BIT(TCCR1A,WGM10);
        SET_BIT(TCCR1A,WGM11);
        CLEAR_BIT(TCCR1B,WGM12);
        CLEAR_BIT(TCCR1B,WGM13);
    }
    else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_ICR1)
    {
        CLEAR_BIT(TCCR1A,WGM10);
        SET_BIT(TCCR1A,WGM11);
        CLEAR_BIT(TCCR1B,WGM12);
        SET_BIT(TCCR1B,WGM13);
    }
    else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_OCR1A)
    {
        SET_BIT(TCCR1A,WGM10);
        SET_BIT(TCCR1A,WGM11);
        CLEAR_BIT(TCCR1B,WGM12);
        SET_BIT(TCCR1B,WGM13);
    }
    
    if(TIMER1_ConfigTypeParam.CO_used_pin_value == OC1B_pin)
        /*  Set Output Compare pin (OC1B) behavior   */
        TCCR1A = (TCCR1A & 0xCF) | (TIMER1_ConfigTypeParam.CO_PWM_T1_value << COM1B0) ;
    else if(TIMER1_ConfigTypeParam.CO_used_pin_value == OC1A_pin)
        /*  Set Output Compare pin (OC1A) behavior   */
        TCCR1A = (TCCR1A & 0x3F) | (TIMER1_ConfigTypeParam.CO_PWM_T1_value << COM1A0) ;
    else if(TIMER1_ConfigTypeParam.CO_used_pin_value == OC1A_B_pin)
    {
        /*  Set Output Compare pin (OC1B) behavior   */
        TCCR1A = (TCCR1A & 0xCF) | (TIMER1_ConfigTypeParam.CO_PWM_T1_value << COM1B0) ;
         /*  Set Output Compare pin (OC1A) behavior   */
        TCCR1A = (TCCR1A & 0x3F) | (TIMER1_ConfigTypeParam.CO_PWM_T1_value << COM1A0) ;
    }

    if(TIMER1_ConfigTypeParam.CO_PWM_T1_value != T1_NORMAL_PORT_OPERATION)
    { /*  Need to set this pin to output  OC1B & OC1A  */
        if(TIMER1_ConfigTypeParam.CO_used_pin_value == OC1B_pin)
            GPIO_SetPinDirection(PORTD_ID,PIN4_ID,OUTPUT_PIN);
        else if(TIMER1_ConfigTypeParam.CO_used_pin_value == OC1A_pin)
            GPIO_SetPinDirection(PORTD_ID,PIN5_ID,OUTPUT_PIN);  
        else if(TIMER1_ConfigTypeParam.CO_used_pin_value == OC1A_B_pin)
        {
            GPIO_SetPinDirection(PORTD_ID,PIN4_ID,OUTPUT_PIN);
            GPIO_SetPinDirection(PORTD_ID,PIN5_ID,OUTPUT_PIN);  
        }
    }   
    /*  Set Clock for Timer    */
    TCCR1B = (TCCR1B & 0xF8) | (TIMER1_ConfigTypeParam.TIMER1_CLK_value);

#elif(TIMER1_CURRENT_MODE == T1_PHASE_FREQUENCY_CORRECT_PWM_MODE) 

    /*  Choose which type of phase and frequency correct PWM   use  */
    if(TIMER1_ConfigTypeParam.T1_PHASE_Freq_C_PWM_Top_value == T1_TOP_equal_ICR1)
    {
        CLEAR_BIT(TCCR1A,WGM10);
        CLEAR_BIT(TCCR1A,WGM11);
        CLEAR_BIT(TCCR1B,WGM12);
        SET_BIT(TCCR1B,WGM13);        
    }
    else if(TIMER1_ConfigTypeParam.T1_PHASE_Freq_C_PWM_Top_value == T1_TOP_equal_OCR1A)
    {
        SET_BIT(TCCR1A,WGM10);
        CLEAR_BIT(TCCR1A,WGM11);
        CLEAR_BIT(TCCR1B,WGM12);
        SET_BIT(TCCR1B,WGM13);  
    }
    /*  Set Output Compare pin (OC1B) behavior   */
    TCCR1A = (TCCR1A & 0xCF) | (TIMER1_ConfigTypeParam.CO_PWM_T1_value << COM1B0) ;
    /*  Set Output Compare pin (OC1A) behavior   */
    TCCR1A = (TCCR1A & 0x3F) | (TIMER1_ConfigTypeParam.CO_PWM_T1_value << COM1A0) ;

    if(TIMER1_ConfigTypeParam.CO_PWM_T1_value != T1_NORMAL_PORT_OPERATION)
        /*  Need to set this pin to output  OC1B & OC1A  */
        GPIO_SetPinDirection(PORTD_ID,PIN4_ID,OUTPUT_PIN);
        GPIO_SetPinDirection(PORTD_ID,PIN5_ID,OUTPUT_PIN); 
    /*  Set Clock for Timer    */
    TCCR1B = (TCCR1B & 0xF8) | (TIMER1_ConfigTypeParam.TIMER1_CLK_value);
#endif


    /*  Set TCNT0 value to Zero*/
    Timer1_UpdateValue(0) ;
}



void Timer1_UpdateValue(uint16 Register_value)
{
    TCNT1 = Register_value;
}


void Timer1_StopClock(void)
{
    TCCR1B = TCCR1B & (0xF8);
}


void Timer1_ProvideClock(void)
{
    TCCR1B = (TCCR1B & 0xF8) | (TIMER1_ConfigTypeParam.TIMER1_CLK_value);
}


#if(TIMER1_CURRENT_MODE == T1_NORMAL_MODE)

    #if (NORMAL_use_T1_state  == T1_ICU)
        void Timer1_ICU_capture_edge (Timer1_ICU_Edge edge_type)
        {
            TCCR1B = ( TCCR1B & (~(1 << ICES1)) ) | (edge_type << ICES1) ;
        }

        uint16 Icu_getInputCaptureValue(void)
        {
            return ICR1;
        }
    #endif


    #if(INTERUPT_STATE_T1 == Disable_Interrupt_T1)

        void Timer1_DelayOVFPolling(void)
        {
            Timer1_ProvideClock();
            /*  Loop in flag of overflow    */
            while(BIT_IS_CLEAR(TIFR,TOV1));

            /*  Clear flag by write one  */
            SET_BIT(TIFR,TOV1);
            Timer1_StopClock();
        }

    #elif(INTERUPT_STATE_T1 == Enable_Interrupt_T1)

        void Timer1_DelayOVFInterrupt(void)
        {
            Timer1_ProvideClock();
        }


        void Timer1_OVFDisableInterrupt(void)
        {
            /*  Disable overflow Interrupt  */
                CLEAR_BIT(TIMSK,TOIE1);   
        }

        void Timer1_OVFEnableInterrupt(void)
        {
            SET_BIT(TIMSK,TOIE1);   
        }

    #endif

#elif(TIMER1_CURRENT_MODE == T1_CTC_MODE)

void Timer1_OutputCompareRegisterAUpdate(uint16 Compare_value)
{
    OCR1A = Compare_value;
}

void Timer1_CTCWaveGeneration(uint16 Ticks)
{
    Timer1_ProvideClock();
    OCR1A = Ticks ;
}

    #if(INTERUPT_STATE_T1 == Disable_Interrupt_T1)

        void Timer1_DelayCTCPolling(void)
        {
            Timer1_ProvideClock();
            /*  Loop in flag of compare match    */
            while(BIT_IS_CLEAR(TIFR,OCF1A));
            /*  Clear flag by write one  */
            SET_BIT(TIFR,OCF1A);
            Timer1_StopClock();
        }

    #elif(INTERUPT_STATE_T1 == Enable_Interrupt_T1)

        void Timer1_DelayCTCInterrupt(void)
        {
            Timer1_ProvideClock();
        }

        void Timer1_CTCDisableInterrupt(void)
        {
            /*  Disable overflow Interrupt  */
            CLEAR_BIT(TIMSK,OCIE1A); 
        }

        void Timer1_CTCEnableInterrupt(void)
        {
            SET_BIT(TIMSK,OCIE1A); 
        }


    #endif

#elif(TIMER1_CURRENT_MODE == T1_FAST_PWM_MODE)

    void Timer1_FastPWMSetOCR1A(uint16 OCR_Register_value)
    {
        OCR1A = OCR_Register_value;
    }

    void Timer1_FastPWMSetOCR1B(uint16 OCR_Register_value)
    {
        OCR1B = OCR_Register_value;
    }

    void Timer1_FastPWMSetDutyCycleA(uint8 DutyCycle_value)
    {
        if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_FF)
            OCR1A = ( ((uint16)(255)) * DutyCycle_value ) / 100 ;
        else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_1FF)
            OCR1A = ( ((uint16)(511)) * DutyCycle_value ) / 100 ;
        else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_3FF)
            OCR1A = ( ((uint32)(1023)) * DutyCycle_value ) / 100 ;
        else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_ICR1)
            OCR1A = ( ((uint32)(ICR1)) * DutyCycle_value ) / 100 ;
    }

    void Timer1_FastPWMSetDutyCycleB(uint8 DutyCycle_value)
    {
        if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_FF)
            OCR1B = ( ((uint16)(255)) * DutyCycle_value ) / 100 ;
        else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_1FF)
            OCR1B = ( ((uint16)(511)) * DutyCycle_value ) / 100 ;
        else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_3FF)
            OCR1B = ( ((uint32)(1023)) * DutyCycle_value ) / 100 ;
        else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_ICR1)
            OCR1B = ( ((uint32)(ICR1)) * DutyCycle_value ) / 100 ;
    }

    void Timer1_FastPWMSetICR_Register(uint16 ICR_value)
    {
        ICR1 = ICR_value ;
    }

#elif(TIMER1_CURRENT_MODE == T1_PHASE_CORRECT_PWM_MODE)

    void Timer1_PhaseCorrectPWMSetOCR1A(uint16 OCR_Register_value)
    {
        OCR1A = OCR_Register_value;
    }

    void Timer1_PhaseCorrectPWMSetOCR1B(uint16 OCR_Register_value)
    {
        OCR1B = OCR_Register_value;
    }

    void Timer1_PhaseCorrectPWMSetDutyCycleA(uint8 DutyCycle_value)
    {
        if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_FF)
            OCR1A = ( ((uint16)(255)) * DutyCycle_value ) / 100 ;
        else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_1FF)
            OCR1A = ( ((uint16)(511)) * DutyCycle_value ) / 100 ;
        else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_3FF)
            OCR1A = ( ((uint32)(1023)) * DutyCycle_value ) / 100 ;
        else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_ICR1)
            OCR1A = ( ((uint32)(ICR1)) * DutyCycle_value ) / 100 ;
    }

    void Timer1_PhaseCorrectPWMSetDutyCycleB(uint8 DutyCycle_value)
    {
        if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_FF)
            OCR1B = ( ((uint16)(255)) * DutyCycle_value ) / 100 ;
        else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_1FF)
            OCR1B = ( ((uint16)(511)) * DutyCycle_value ) / 100 ;
        else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_3FF)
            OCR1B = ( ((uint32)(1023)) * DutyCycle_value ) / 100 ;
        else if(TIMER1_ConfigTypeParam.T1_FAST_phase_C_PWM_Top_value == T1_TOP_equal_ICR1)
            OCR1B = ( ((uint32)(ICR1)) * DutyCycle_value ) / 100 ;
    }

    void Timer1_PhaseCorrectPWMSetICR_Register(uint16 ICR_value)
    {
        ICR1 = ICR_value ;
    }



#endif
