/******************************************************************************
 *
 * Module: Application
 *
 * File Name: Application_interface.h
 *
 * Description: Header File contain function Prototype  
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef APPLICATION_APPLICATION_H_
#define APPLICATION_APPLICATION_H_


/**************************                   INCLUDES                   **************************/

#include "../HAL/BUTTON/BUTTON_interface.h"
#include "../HAL/LED/LED_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../Hal/Buzzer/Buzzer_interface.h"
#include "../HAL/Potentiometer/POT_interface.h"
#include "../HAL/KEYPAD/Keypad_interface.h"

#include "../MCAL/EXT_INT/EXT_INT_interface.h"
#include "../MCAL/TIMER0/TIMER0_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/TIMER1/TIMER1_interface.h"


/**************************                   Definitions                   **************************/

#define Buzzer_PORT             PORTC_ID
#define Buzzer_PIN              PIN6_ID



#define Braking_BTN_PORT            PORTD_ID
#define Braking_BTN_PIN             PIN3_ID



#define Red_LED_PORT                PORTB_ID
#define Red_LED_PIN                 PIN7_ID


#define Yellow_LED_PORT             PORTA_ID
#define Yellow_LED_PIN              PIN6_ID


#define Relay_PORT                  PORTC_ID
#define Relay_PIN                   PIN7_ID

#define DC_RIR_1_PORT               PORTB_ID
#define DC_RIR_1_PIN                PIN5_ID


#define DC_RIR_2_PORT               PORTB_ID
#define DC_RIR_2_PIN                PIN6_ID


#define BTN_Pressed_State           LOGIC_LOW
#define BTN_Released_State          LOGIC_HIGH

#define YES_Condition               LOGIC_HIGH
#define NO_Condition                LOGIC_LOW




/*
*   @brief : this function used to initailize what will displayed in LCD and configure Buttons and Leds 
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void App_Init(void);


/*
*   @brief : this function used responsible for all system and handle changes in Modes 
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void App_StateMachineUpdate(void);




#endif /* APPLICATION_APPLICATION_H_ */
