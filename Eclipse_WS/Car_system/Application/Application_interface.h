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

#include "../MCAL/EXT_INT/EXT_INT_interface.h"
#include "../MCAL/TIMER0/TIMER0_interface.h"
#include "../MCAL/ADC/ADC_interface.h"


/**************************                   Definitions                   **************************/

#define Buzzer_PORT             PORTC_ID
#define Buzzer_PIN              PIN6_ID


#define Accelerate_BTN_PORT         PORTD_ID
#define Accelerate_BTN_PIN          PIN7_ID

#define Braking_BTN_PORT            PORTD_ID
#define Braking_BTN_PIN             PIN3_ID

#define ACCS_BTN_PORT               PORTD_ID
#define ACCS_BTN_PIN                PIN5_ID

#define GearBox_BTN_PORT            PORTD_ID
#define GearBox_BTN_PIN             PIN6_ID

#define Blue_LED_PORT               PORTA_ID
#define BLUE_LED_PIN                PIN5_ID

#define Red_LED_PORT                PORTB_ID
#define Red_LED_PIN                 PIN7_ID

#define Green_LED_PORT              PORTA_ID
#define Green_LED_PIN               PIN4_ID

#define Yellow_LED_PORT             PORTA_ID
#define Yellow_LED_PIN              PIN6_ID


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
void StateMachineUpdate(void);




#endif /* APPLICATION_APPLICATION_H_ */
