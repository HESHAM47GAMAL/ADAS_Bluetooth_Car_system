 /******************************************************************************
 *
 * Module: TIMER0
 *
 * File Name: TIMER0_config.c
 *
 * Description: include configuration that will applied
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "TIMER0_config.h"


/*  fill this data from available option in     TIMER0_config.h     */


#if(TIMER0_CURRENT_MODE == T0_NORMAL_MODE)

    TIMER0_ConfigType TIMER0_ConfigTypeParam = {
        F_CPU_8_T0        /*    Choose Prescaler   */
    };
    
#elif(TIMER0_CURRENT_MODE == T0_CTC_MODE )

    TIMER0_ConfigType TIMER0_ConfigTypeParam = {
        F_CPU_8_T0   ,     /*    Choose Prescaler   */ 
        T0_TOGGLE_CO0      /*    Choose what happen on compare match   */ 
    };


#elif( (TIMER0_CURRENT_MODE == T0_FAST_PWM_MODE) || (TIMER0_CURRENT_MODE == T0_PHASE_CORRECT_PWM_MODE))
 
    TIMER0_ConfigType TIMER0_ConfigTypeParam = {
        F_CPU_256_T0   ,     /*    Choose Prescaler   */ 
        T0_NON_INVERTING      /*    Choose what happen on compare match   */ 
    };

#endif