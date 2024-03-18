 /******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: TIMER1_interface.h
 *
 * Description: Header contain function prototype to be used 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

//gard file

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "TIMER1_config.h"

/*
*   @brief : this function used to initailize Timer1 in which mode will work 
* ⛔Note : keep in mind that in OVF(time delay or ICP) and CTC mode clock not provided but it provided first step in function for this  two mode
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Timer1_Init(void);

/*
*   @brief : this function used to update timer1 register TCNT1
*   @arg1  Register_value : value will store in this register
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Timer1_UpdateValue(uint16 Register_value);

/*
*   @brief : this function used to stop clock for Timer1 Peripheral as TCNT1 won't count
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Timer1_StopClock(void);

/*
*   @brief : this function used to provide Clock again that is setted in Config.c to make peripheral work 
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Timer1_ProvideClock(void);

#if(INTERUPT_STATE_T1 == Enable_Interrupt_T1)
/*
*   @brief : this function used to store address of function that will be stored in  pointer to function as when Interrupt happen call this function 
*   @arg1  a_ptr : pointer to function that will be called when Inteerupt happen 
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
    void Timer1_SetCallBack(void(*a_ptr)(void));

#endif

#if(TIMER1_CURRENT_MODE == T1_NORMAL_MODE)

    #if (NORMAL_use_T1_state  == T1_ICU)
/*
*   @brief : this function used to set type of edge that when catched ICR take copy from TCNT1
*   @arg1  edge_type : type of edge as (Rising , Falling)
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer1_ICU_capture_edge (Timer1_ICU_Edge edge_type);
/*
*   @brief : this function used to return value of ICR
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        uint16 Icu_getInputCaptureValue(void);

    #endif

    #if(INTERUPT_STATE_T1 == Disable_Interrupt_T1)
/*
*   @brief : this function used to make time delay using polling Technique
*   ⛔note if you want to edit value of TCNT1 can use function that do that before this function
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer1_DelayOVFPolling(void);

    #elif(INTERUPT_STATE_T1 == Enable_Interrupt_T1)

/*
*   @brief : this function used to make time delay using Interrut Technique
*   ⛔note if you want to edit value of TCNT1 can use function that do that before this function
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer1_DelayOVFInterrupt(void);

/*
*   @brief : this function used to Disable Interrupt of OVF mode
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer1_OVFDisableInterrupt(void);

/*
*   @brief : this function used to Enable Interrupt of OVF mode
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer1_OVFEnableInterrupt(void);

    #endif

#elif(TIMER1_CURRENT_MODE == T1_CTC_MODE)

/*
*   @brief : this function used to update OutputCompare register OCR1A 
*   @arg1  Compare_value : value will store in this register
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Timer1_OutputCompareRegisterAUpdate(uint16 Compare_value);

/*
*   @brief : this function used to Generate wave form with 50% deuty cycle but it's frequency change depend on value of OCR1A 
*   @arg1  Compare_value : value will store in this register
*   @return: no return                                                              F_cpu
*   @synchronous / Asynchronous : Synchronous                       F_OC1 = -----------------------
*   @ Reentrant / Non Reentrant : Reentrant                                   2*preScaler*(1+OCR1A)
*/
void Timer1_CTCWaveGeneration(uint16 Ticks);

    #if(INTERUPT_STATE_T1 == Disable_Interrupt_T1)

/*
*   @brief : this function used to make time delay using polling Technique
*   ⛔note if you want to edit value of OCR0 can use function that do that before this function
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer1_DelayCTCPolling(void);

    #elif(INTERUPT_STATE_T1 == Enable_Interrupt_T1)

/*
*   @brief : this function used to make time delay using Interrut Technique
*   ⛔note if you want to edit value of OCR0 can use function that do that before this function
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer1_DelayCTCInterrupt(void);

/*
*   @brief : this function used to Disable Interrupt of CTC mode
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer1_CTCDisableInterrupt(void);

/*
*   @brief : this function used to Enable Interrupt of CTC mode
*   @args  :void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
        void Timer1_CTCEnableInterrupt(void);

    #endif
    
    
#elif(TIMER1_CURRENT_MODE == T1_FAST_PWM_MODE)

/*
*   @brief : this function used to Generate Fast PWM  (Analog signal) @ pin OC1A
*   @arg1  OCR_Register_value : value will store in OCR1A that control analog value  
*   @return: no return                                                              F_cpu
*   @synchronous / Asynchronous : Synchronous                       F_OC1(A:B) = -----------------------
*   @ Reentrant / Non Reentrant : Reentrant                                         preScaler* Top_value
*/
    void Timer1_FastPWMSetOCR1A(uint16 OCR_Register_value);

/*
*   @brief : this function used to Generate Fast PWM  (Analog signal) @ pin OC1B
*   @arg1  OCR_Register_value : value will store in OCR1B that control analog value  
*   @return: no return                                                              F_cpu
*   @synchronous / Asynchronous : Synchronous                       F_OC1(A:B) = -----------------------
*   @ Reentrant / Non Reentrant : Reentrant                                        preScaler*Top_value
*/
    void Timer1_FastPWMSetOCR1B(uint16 OCR_Register_value);

/*
*   @brief : this function used to Generate Fast PWM  (Analog signal)  @ pin OC1A
*   @arg1  DutyCycle_value : value that will control analog value   as give duty cycle
*   @return: no return                                                              F_cpu
*   @synchronous / Asynchronous : Synchronous                       F_OC1(A:B) = -----------------------
*   @ Reentrant / Non Reentrant : Reentrant                                         preScaler*Top_value
*/
    void Timer1_FastPWMSetDutyCycleA(uint8 DutyCycle_value);

/*
*   @brief : this function used to Generate Fast PWM  (Analog signal)  @ pin OC1B
*   @arg1  DutyCycle_value : value that will control analog value   as give duty cycle
*   @return: no return                                                              F_cpu
*   @synchronous / Asynchronous : Synchronous                       F_OC1(A:B) = -----------------------
*   @ Reentrant / Non Reentrant : Reentrant                                         preScaler*Top_value
*/
    void Timer1_FastPWMSetDutyCycleB(uint8 DutyCycle_value);
/*
*   @brief : this function used to SET value of ICR1 register when use Generate Fast PWM  (Analog signal)
*   @arg1  ICR_value : value that will seted in ICR1
*   @return: no return                                                    
*   @synchronous / Asynchronous : Synchronous                     
*   @ Reentrant / Non Reentrant : Reentrant                                 
*/
    void Timer1_FastPWMSetICR_Register(uint16 ICR_value);

#elif(TIMER1_CURRENT_MODE == T1_PHASE_CORRECT_PWM_MODE)


/*
*   @brief : this function used to Generate Fast PWM  (Analog signal) @ pin OC1A
*   @arg1  OCR_Register_value : value will store in OCR1A that control analog value  
*   @return: no return                                                              F_cpu
*   @synchronous / Asynchronous : Synchronous                       F_OC1(A:B) = -----------------------
*   @ Reentrant / Non Reentrant : Reentrant                                         preScaler* Top_value
*/
    void Timer1_PhaseCorrectPWMSetOCR1A(uint16 OCR_Register_value);

/*
*   @brief : this function used to Generate Fast PWM  (Analog signal) @ pin OC1B
*   @arg1  OCR_Register_value : value will store in OCR1B that control analog value  
*   @return: no return                                                              F_cpu
*   @synchronous / Asynchronous : Synchronous                       F_OC1(A:B) = -----------------------
*   @ Reentrant / Non Reentrant : Reentrant                                        preScaler*Top_value
*/
    void Timer1_PhaseCorrectPWMSetOCR1B(uint16 OCR_Register_value);

/*
*   @brief : this function used to Generate Fast PWM  (Analog signal)  @ pin OC1A
*   @arg1  DutyCycle_value : value that will control analog value   as give duty cycle
*   @return: no return                                                              F_cpu
*   @synchronous / Asynchronous : Synchronous                       F_OC1(A:B) = -----------------------
*   @ Reentrant / Non Reentrant : Reentrant                                         preScaler*Top_value
*/
    void Timer1_PhaseCorrectPWMSetDutyCycleA(uint8 DutyCycle_value);

/*
*   @brief : this function used to Generate Fast PWM  (Analog signal)  @ pin OC1B
*   @arg1  DutyCycle_value : value that will control analog value   as give duty cycle
*   @return: no return                                                              F_cpu
*   @synchronous / Asynchronous : Synchronous                       F_OC1(A:B) = -----------------------
*   @ Reentrant / Non Reentrant : Reentrant                                         preScaler*Top_value
*/
    void Timer1_PhaseCorrectPWMSetDutyCycleB(uint8 DutyCycle_value);
/*
*   @brief : this function used to SET value of ICR1 register when use Generate Fast PWM  (Analog signal)
*   @arg1  ICR_value : value that will seted in ICR1
*   @return: no return                                                    
*   @synchronous / Asynchronous : Synchronous                     
*   @ Reentrant / Non Reentrant : Reentrant                                 
*/
    void Timer1_PhaseCorrectPWMSetICR_Register(uint16 ICR_value);

#endif





#endif