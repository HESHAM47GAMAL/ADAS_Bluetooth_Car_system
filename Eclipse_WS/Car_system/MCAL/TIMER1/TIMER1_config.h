 /******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: TIMER1_config.h
 *
 * Description: Header to configure Timer1
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/*

                                                                                        Modes Control
                                                                                            |
                                                                                            |
               ----------------------------------------------------------------------------------------------------------------------------------------------------------------
              |                                                     |                                                                                                       |
              \/                                                    \/                                                                                                      \/
            OverFlow (normal)                                       CTC                                                                                                  Fast PWM & phase correct PWM & phase and frequency correct
                |  -----------------------                           |                                                                                                        |       
                |                           |               -------------------------------------
                \/                        ICU               |                                    |                                                                      No need to interrupt
            used in time Delay                              \/                                   \/
                |                                         Time Delay                        Wave generation (50% duty cycle)
                |can be using                               |can be using                                    |
                |                                           | (T0_NORMAL_PORT_OPERATION)                     |
        -------  ------                                ----------------                             No need to interrupt
        |               |                              |               |                                      |
    Polling         Interrupt                        Polling         Interrupt                      can be using(T0_TOGGLE_CO0)

*/

#ifndef TIMER1_CONFIG_H_
#define TIMER1_CONFIG_H_

#define T1_NORMAL_MODE                         0   //  Option 1 -----------|
#define T1_CTC_MODE                            1   //  Option 2 -----------|
#define T1_FAST_PWM_MODE                       2   //  Option 3 -----------|
#define T1_PHASE_CORRECT_PWM_MODE              3   //  Option 4 -----------|
#define T1_PHASE_FREQUENCY_CORRECT_PWM_MODE    4   //  Option 5 -----------|
//                                                                         | Here
#define TIMER1_CURRENT_MODE         T1_NORMAL_MODE        //<-----------------|


#define Enable_Interrupt_T1                1   //  Option 1 -----------|
#define Disable_Interrupt_T1               0   //  Option 2 -----------|
//                                                                     |
#define INTERUPT_STATE_T1          Enable_Interrupt_T1    //<------------|





/**************************                   Declare custom types                   **************************/


typedef enum 
{
    STOP_TIMER1  ,
    F_CPU_CLK_T1 ,
    F_CPU_8_T1 ,
    F_CPU_64_T1 ,
    F_CPU_256_T1 ,
    F_CPU_1024_T1 ,
    EXTERNAL_CLK_FALLING_EDGE_T1 ,   // @ T0 (PB0)
    EXTERNAL_CLK_RISING_EDGE_T1      // @ T0 (PB0)
}TIMER1_CLK ;

#if(TIMER1_CURRENT_MODE == T1_NORMAL_MODE)


    typedef struct 
    {
        TIMER1_CLK  TIMER1_CLK_value;
    }TIMER1_ConfigType;



#define    T1_TIME_DELAY            0 //  Option 1 -----------|
#define    T1_ICU                   1 //  Option 2 -----------|
//                                                            | Here   
#define NORMAL_use_T1_state         T1_ICU   //<-------|

#if (NORMAL_use_T1_state  == T1_ICU)
    typedef enum{
        Timer1_ICU_capture_Falling_edge ,
        Timer1_ICU_capture_Rising_edge
    }Timer1_ICU_Edge;

#endif 

#elif(TIMER1_CURRENT_MODE == T1_CTC_MODE )
    typedef enum 
    {
        T1_TOP_equal_OCR1A ,
        T1_Top_equal_ICR1
    }T1_CTC_Top;

    typedef enum 
    {
        T1_NORMAL_PORT_OPERATION ,
        T1_TOGGLE_CO1 ,
        T1_CLEAR_CO1 ,
        T1_SET_CO1
    }CO_nonPWM_T1;

    typedef struct 
    {
        TIMER1_CLK  TIMER1_CLK_value;
        T1_CTC_Top T1_CTC_Top_value;
        CO_nonPWM_T1   CO_nonPWM_T1_value ;
    }TIMER1_ConfigType;

#elif((TIMER1_CURRENT_MODE == T1_FAST_PWM_MODE) || (TIMER1_CURRENT_MODE == T1_PHASE_CORRECT_PWM_MODE))
    typedef enum 
    {
        T1_TOP_equal_FF , //8bit
        T1_TOP_equal_1FF , //9bit
        T1_TOP_equal_3FF , //10bit
        T1_TOP_equal_ICR1 ,  //  used when need to generate pwm with very low frequency 
        T1_TOP_equal_OCR1A
    }T1_FAST_phase_C_PWM_Top;

    typedef enum 
    {
        T1_NORMAL_PORT_OPERATION ,
        T1_NON_INVERTING = 2 ,
        T1_INVERTING
    }CO_PWM_T1;

    typedef enum 
    {
        OC1A_pin , 
        OC1B_pin ,
        OC1A_B_pin
    }CO_used_pin ;

    typedef struct 
    {
        TIMER1_CLK    TIMER1_CLK_value;
        T1_FAST_phase_C_PWM_Top   T1_FAST_phase_C_PWM_Top_value;
        CO_PWM_T1   CO_PWM_T1_value ;
        CO_used_pin CO_used_pin_value ;
    }TIMER1_ConfigType;

#elif (TIMER1_CURRENT_MODE == T1_PHASE_FREQUENCY_CORRECT_PWM_MODE)

    typedef enum 
    {
        T1_TOP_equal_ICR1 ,
        T1_TOP_equal_OCR1A
    }T1_PHASE_Freq_C_PWM_Top;

    typedef enum 
    {
        T1_NORMAL_PORT_OPERATION ,
        T1_NON_INVERTING = 2 ,
        T1_INVERTING
    }CO_PWM_T1;

    typedef struct 
    {
        TIMER1_CLK  TIMER1_CLK_value;
        T1_PHASE_Freq_C_PWM_Top   T1_PHASE_Freq_C_PWM_Top_value;
        CO_PWM_T1   CO_PWM_T1_value ;
    }TIMER1_ConfigType;


#endif






#endif



