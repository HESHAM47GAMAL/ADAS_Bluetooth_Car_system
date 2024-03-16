 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC_interface.h
 *
 * Description: Header contain function prototype to be used 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

//gard file

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "../GPIO/GPIO_interface.h"
#include "ADC_config.h"


/**************************                   Definition                   **************************/

#define ADC_Channel_0       PIN0_ID
#define ADC_Channel_1       PIN1_ID
#define ADC_Channel_2       PIN2_ID
#define ADC_Channel_3       PIN3_ID
#define ADC_Channel_4       PIN4_ID
#define ADC_Channel_5       PIN5_ID
#define ADC_Channel_6       PIN6_ID
#define ADC_Channel_7       PIN7_ID



#define ADC_MAX_VALUE   1023

#define ADC_Interrupt_State_interface           ADC_Interrupt_State
#define REFRENCE_Volt_AVCC_OR_AREF_OR_internal_interface        REFRENCE_Volt_AVCC_OR_AREF_OR_internal
#define ADC_Interrupt_Enable_interface          1
#define ADC_Interrupt_Disable_interface         0



#if(ADC_Interrupt_State_interface == ADC_Interrupt_Enable_interface)
/**************************                   Extern Global Variables                   **************************/
extern volatile uint16 g_adcResult ; 
#endif

/**************************                   Function Prototype                   **************************/

/*
*   @brief : this function used to initailize ADC  with wanted configuration 
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void ADC_Init(void);

/*
*   @brief : this function used to Read convertion  after start it using Polling technique used in Single conversion mode
*   @arg1  Channel_NUM : ADC channel that make conversion
*   @return: successive apporoximation register value 0:1023
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
uint16 ADC_ReadChannelSingleConvertion(uint8 Channel_NUM);

/*
*   @brief : this function used to make free running mode as when conversion finish start new one and so on 
*   @arg1  Channel_NUM : ADC channel that make conversion
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void ADC_FreeRunningStart (uint8 Channel_NUM);

/*
*   @brief : this function used to read ADC register
*   @args  : void
*   @return: successive apporoximation register value 0:1023
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
uint16 ADC_ReadConversionRegister(void);


/*
*   @brief : this function used to Start function for General only
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void ADC_OnlyStartConversionGeneral(uint8 Channel_NUM);


#endif