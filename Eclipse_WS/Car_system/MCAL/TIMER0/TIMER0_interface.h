 /******************************************************************************
 *
 * Module: TIMER0
 *
 * File Name: TIMER0_interface.h
 *
 * Description: Header contain function prototype to be used 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

//gard file

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "TIMER0_config.h"

/*
*   @brief : this function used to initailize Timer0 in which mode will work 
* ⛔Note : keep in mind that in OVF and CTC mode clock not provided but it provided first step in function for this  two mode
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Timer0_Init(void);

/*
*   @brief : this function used to update timer0 register TCNT0 
*   @arg1  Register_value : value will store in this register
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Timer0_UpdateValue(uint8 Register_value);

/*
*   @brief : this function used to stop clock for Timer0 Peripheral as TCNT0 won't count
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Timer0_StopClock(void);

/*
*   @brief : this function used to provide Clock again that is setted in Config.c to make peripheral work 
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Timer0_ProvideClock(void);

#if(INTERUPT_STATE_T0 == Enable_Interrupt_T0)
/*
*   @brief : this function used to store address of function that will be stored in  pointer to function as when Interrupt happen call this function 
*   @arg1  a_ptr : pointer to function that will be called when Inteerupt happen 
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
    void Timer0_SetCallBack(void(*a_ptr)(void));

#endif

#if(TIMER0_CURRENT_MODE == T0_NORMAL_MODE)

    #if(INTERUPT_STATE_T0 == Disable_Interrupt_T0)
/*
*   @brief : this function used to make time delay using polling Technique
*   ⛔note if you want to edit value of TCNT0 can use function that do that before this function
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer0_DelayOVFPolling(void);

    #elif(INTERUPT_STATE_T0 == Enable_Interrupt_T0)

/*
*   @brief : this function used to make time delay using Interrut Technique
*   ⛔note if you want to edit value of TCNT0 can use function that do that before this function
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer0_DelayOVFInterrupt(void);

/*
*   @brief : this function used to Disable Interrupt of OVF mode
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer0_OVFDisableInterrupt(void);

/*
*   @brief : this function used to Enable Interrupt of OVF mode
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer0_OVFEnableInterrupt(void);

    #endif

#elif(TIMER0_CURRENT_MODE == T0_CTC_MODE)

/*
*   @brief : this function used to update OutputCompare register OCR0 
*   @arg1  Compare_value : value will store in this register
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Timer0_OutputCompareRegisterUpdate(uint8 Compare_value);

/*
*   @brief : this function used to Generate wave form with 50% deuty cycle but it's frequency change depend on value of OCR0 
*   @arg1  Compare_value : value will store in this register
*   @return: no return                                                              F_cpu
*   @synchronous / Asynchronous : Synchronous                       F_OC0 = -----------------------
*   @ Reentrant / Non Reentrant : Reentrant                                   2*preScaler*(1+OCR0)
*/
void Timer0_CTCWaveGeneration(uint8 Ticks);

    #if(INTERUPT_STATE_T0 == Disable_Interrupt_T0)

/*
*   @brief : this function used to make time delay using polling Technique
*   ⛔note if you want to edit value of OCR0 can use function that do that before this function
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer0_DelayCTCPolling(void);

    #elif(INTERUPT_STATE_T0 == Enable_Interrupt_T0)

/*
*   @brief : this function used to make time delay using Interrut Technique
*   ⛔note if you want to edit value of OCR0 can use function that do that before this function
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer0_DelayCTCInterrupt(void);

/*
*   @brief : this function used to Disable Interrupt of CTC mode
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer0_CTCDisableInterrupt(void);

/*
*   @brief : this function used to Enable Interrupt of CTC mode
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer0_CTCEnableInterrupt(void);

    #endif
    
    
#elif(TIMER0_CURRENT_MODE == T0_FAST_PWM_MODE)

/*
*   @brief : this function used to Generate Fast PWM  (Analog signal)
*   @arg1  OCR_Register_value : value will store in OCR0 that control analog value  Range = (0:255)
*   @return: no return                                                              F_cpu
*   @synchronous / Asynchronous : Synchronous                       F_OC0 = -----------------------
*   @ Reentrant / Non Reentrant : Reentrant                                   preScaler*256
*/
    void Timer0_FastPWMSetOCR(uint8 OCR_Register_value);

/*
*   @brief : this function used to Generate Fast PWM  (Analog signal)
*   @arg1  DutyCycle_value : value that will control analog value  Range = (0:100) as give duty cycle
*   @return: no return                                                              F_cpu
*   @synchronous / Asynchronous : Synchronous                       F_OC0 = -----------------------
*   @ Reentrant / Non Reentrant : Reentrant                                   preScaler*256
*/
    void Timer0_FastPWMSetDutyCycle(uint8 DutyCycle_value);

#elif(TIMER0_CURRENT_MODE == T0_PHASE_CORRECT_PWM_MODE)

/*
*   @brief : this function used to Generate Phase correct PWM  (Analog signal)
*   @arg1  OCR_Register_value : value will store in OCR0 that control analog value  Range = (0:255)
*   @return: no return                                                              F_cpu
*   @synchronous / Asynchronous : Synchronous                       F_OC0 = -----------------------
*   @ Reentrant / Non Reentrant : Reentrant                                   preScaler*510
*/
    void Timer0_PhaseCorrectPWMSetOCR(uint8 OCR_Register_value);

/*
*   @brief : this function used to Generate Phase correct PWM  (Analog signal)
*   @arg1  DutyCycle_value : value that will control analog value  Range = (0:100) as give duty cycle
*   @return: no return                                                              F_cpu
*   @synchronous / Asynchronous : Synchronous                       F_OC0 = -----------------------
*   @ Reentrant / Non Reentrant : Reentrant                                   preScaler*510
*/
    void Timer0_PhaseCorrectPWMSetDutyCycle(uint8 DutyCycle_value);

#endif





#endif