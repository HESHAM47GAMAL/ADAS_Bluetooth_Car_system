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

#include "Application_private.h"


/**************************                   Definitions                   **************************/

#define BZR_PORT             PORTC_ID
#define BZR_PIN              PIN6_ID


#define ACL_BTN_PORT         PORTD_ID
#define ACL_BTN_PIN          PIN7_ID

#define BRK_BTN_PORT            PORTD_ID
#define BRK_BTN_PIN             PIN3_ID

#define CCS_BTN_PORT               PORTD_ID
#define CCS_BTN_PIN                PIN5_ID

#define GBX_BTN_PORT            PORTD_ID
#define GBX_BTN_PIN             PIN6_ID

#define BLU_LED_PORT               PORTA_ID
#define BLU_LED_PIN                PIN5_ID

#define RED_LED_PORT                PORTB_ID
#define RED_LED_PIN                 PIN7_ID

#define GRN_LED_PORT              PORTA_ID
#define GRN_LED_PIN               PIN4_ID

#define YLW_LED_PORT             PORTA_ID
#define YLW_LED_PIN              PIN6_ID


#define BTN_Pressed_State           LOGIC_LOW
#define BTN_Released_State          LOGIC_HIGH

#define YES_Condition               LOGIC_HIGH
#define NO_Condition                LOGIC_LOW

#define ON               LOGIC_HIGH
#define OFF                LOGIC_LOW

#endif /* APPLICATION_APPLICATION_H_ */
