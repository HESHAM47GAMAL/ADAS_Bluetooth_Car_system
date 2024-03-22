 /******************************************************************************
 *
 * Module: TIMER0
 *
 * File Name: TIMER0_config.h
 *
 * Description: Header to configure Timer0
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
            OverFlow                                                CTC                                                                                                  Fast PWM & phase correct PWM
                |                                                   |                                                                                                        |       
                |                                           -------------------------------------
                \/                                          |                                    |                                                                      No need to interrupt
            used in time Delay                              \/                                   \/
                |                                         Time Delay                        Wave generation (50% duty cycle)
                |can be using                               |can be using                                    |
                |                                           | (T0_NORMAL_PORT_OPERATION)                     |
        -------  ------                                ----------------                             No need to interrupt
        |               |                              |               |                                      |
    Polling         Interrupt                        Polling         Interrupt                      can be using(T0_TOGGLE_CO0)

*/

#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

#define T0_NORMAL_MODE                         0   //  Option 1 -----------|
#define T0_CTC_MODE                            2   //  Option 2 -----------|
#define T0_FAST_PWM_MODE                       3   //  Option 3 -----------|
#define T0_PHASE_CORRECT_PWM_MODE              1   //  Option 4 -----------|
//                                                                         | Here
#define TIMER0_CURRENT_MODE         T0_FAST_PWM_MODE   //<-----------------|


#define Enable_Interrupt_T0                1   //  Option 1 -----------|
#define Disable_Interrupt_T0               0   //  Option 2 -----------|
//                                                                     |
#define INTERUPT_STATE_T0          Enable_Interrupt_T0    //<------------|


/**************************                   Declare custom types                   **************************/


typedef enum 
{
    STOP_TIMER0  ,
    F_CPU_CLK_T0 ,
    F_CPU_8_T0 ,
    F_CPU_64_T0 ,
    F_CPU_256_T0 ,
    F_CPU_1024_T0 ,
    EXTERNAL_CLK_FALLING_EDGE_T0 ,   // @ T0 (PB0)
    EXTERNAL_CLK_RISING_EDGE_T0      // @ T0 (PB0)
}TIMER0_CLK ;

#if(TIMER0_CURRENT_MODE == T0_NORMAL_MODE)

    typedef struct 
    {
        TIMER0_CLK  TIMER0_CLK_value;
    }TIMER0_ConfigType;

#elif(TIMER0_CURRENT_MODE == T0_CTC_MODE )
    typedef enum 
    {
        T0_NORMAL_PORT_OPERATION ,
        T0_TOGGLE_CO0 ,
        T0_CLEAR_CO0 ,
        T0_SET_CO0
    }CO_nonPWM_T0;

    typedef struct 
    {
        TIMER0_CLK  TIMER0_CLK_value;
        CO_nonPWM_T0   CO_nonPWM_T0_value ;
    }TIMER0_ConfigType;

#elif( (TIMER0_CURRENT_MODE == T0_FAST_PWM_MODE) || (TIMER0_CURRENT_MODE == T0_PHASE_CORRECT_PWM_MODE))
    typedef enum 
    {
        T0_NORMAL_PORT_OPERATION ,
        T0_NON_INVERTING = 2 ,
        T0_INVERTING
    }CO_PWM_T0;

    typedef struct 
    {
        TIMER0_CLK  TIMER0_CLK_value;
        CO_PWM_T0   CO_PWM_T0_value ;
    }TIMER0_ConfigType;

#endif






#endif



