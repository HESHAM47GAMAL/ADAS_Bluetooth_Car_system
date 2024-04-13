 /******************************************************************************
 *
 * Module: Keypad
 *
 * File Name: Keypad_config.h
 *
 * Description: Header to configure connection of keypad and size of it
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

/**************************                   INCLUDES                   **************************/
#include "../../MCAL/GPIO/GPIO_interface.h"


//                                          |----> some time not exist
//                                          |
//                 -           c0  c1  c2  c3
//                |      r0   |--------------|
// input pin      |      r1      output pin
//                |      r2
//                |      r3
//                 - 




/**************************                   Definitions macro                   **************************/

#define KEYPAD_ROW_NUM              4
#define KEYPAD_COL_NUM              3 

#define KEYPAD_SequencePin              0
#define KEYPAD_NOTSequencePin           1
#define Option_PIN_KEYPAD               KEYPAD_NOTSequencePin


/***  Choose port that will connected to keypad***/

#if(Option_PIN_KEYPAD == KEYPAD_SequencePin)

    #define PORT_FOR_KEYPAD         PORTA_ID

    /***  choose first pin from cols lines of keypad will connect to MCU***/
    #define KEYPAD_FIRST_PIN_ROW_ID         PIN0_ID

    #define KEYPAD_FIRST_PIN_COL_ID         PIN4_ID    

#elif(Option_PIN_KEYPAD == KEYPAD_NOTSequencePin)

    #define KEYPAD_COL_PORT         PORTD_ID

    #define     KEYPAD_COL0         PIN7_ID
    #define     KEYPAD_COL1         PIN5_ID
    #define     KEYPAD_COL2         PIN4_ID
    #define     KEYPAD_COL3         PIN3_ID


    #define  KEYPAD_ROW_PORT        PORTC_ID

    #define KEYPAD_ROW_0            PIN5_ID
    #define KEYPAD_ROW_1            PIN4_ID
    #define KEYPAD_ROW_2            PIN3_ID
    #define KEYPAD_ROW_3            PIN2_ID

#endif

/*** state that I will read in pin when press button from keypad ***/
#define KEYPAD_PRESSED_STATE            LOGIC_LOW   //(LOGIC_HIGH , LOGIC_LOW)   
//                             |
//                             |
//           ------------------ -------------------
//          |                                      |
//          |(Logic low)                           |(logic high)   
//          |                                      |
//          \/                                     \/
// activate pullup resistor                        need extenal pull down resistor (👀 don't miss)


/*** here can control if i want to wait until pressed button release before return value ***/
#define WAIT_BEFORE_RETURN_PRESSED_KEY          0  	//-----(OPTION 1)
//															|
#define RETURN_NUM_ONLY_ONCE_UNTIL_RELEASE      1	//-----(OPTION 2)  as here return only number pressed once release btn and press it again to return it or press another btn not same previous
//															|
#define DO_NOTHING_KEYPAD 						2	//-----(OPTION 3)
//															|
#define WHAT_DO_WITH_PRESS			DO_NOTHING_KEYPAD


/**************************                   Macros like function   & Function Declare                **************************/
#if(KEYPAD_COL_NUM == 3)

/*
*   @brief : this function used map pressed button to value of button for keypad matrex size    4*3
*   @args  : key number that pressed
*   @return: value of key pressed after mapping
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static uint8 Keypad_4X3_AdjustKeyNumber(uint8 Button_Number); // static that no another module will use it 

#elif(KEYPAD_COL_NUM == 4)

/*
*   @brief : this function used map pressed button to value of button for keypad matrex size    4*4
*   @args  : key number that pressed
*   @return: value of key pressed after mapping
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static uint8 Keypad_4X4_AdjustKeyNumber(uint8 Button_Number); // static that no another module will use it 

#endif


/**************************                   Functions Definition                   **************************/

/*  Note ⛔🙆‍♂️  Don't miss to edit what is character in ROW column in your Keypad    */


#if(KEYPAD_COL_NUM == 3)

static uint8 Keypad_4X3_AdjustKeyNumber(uint8 Button_Number)
{
    uint8 pressed_key = 0;
    switch (Button_Number)
    {
        case 10 :
            pressed_key = '*';
            break;

        case 11 : 
            pressed_key = 0;
            break;

        case 12 : 
            pressed_key = '#';
            break;

        default :
            pressed_key = Button_Number;   // if Button_Number =1  --> so will return 1 (as no mapping need like case 10 , 11 , 12)
            break;
    }
    return pressed_key;
}

#elif(KEYPAD_COL_NUM == 4)

static uint8 Keypad_4X4_AdjustKeyNumber(uint8 Button_Number)
{
    uint8 pressed_key = 0;
    switch(Button_Number)
    {
        case 1 : pressed_key = 1;
            break;
        
        case 2 : pressed_key = 2;
            break;

        case 3 : pressed_key = 3 ;
            break;

        case 4 : pressed_key = 'A';
            break;

        case 5 : pressed_key = 4 ;
            break ;

        case 6 : pressed_key = 5 ;
            break ;

        case 7 : pressed_key = 6 ;
            break;

        case 8 : pressed_key = 'B';
            break ;

        case 9 : pressed_key = 7;
            break ;

        case 10 : pressed_key = 8 ;
            break ;

        case 11 : pressed_key = 9 ; 
            break ;

        case 12 : pressed_key = 'C';
            break ;

        case 13 : pressed_key = '*';
            break; 

        case 14 : pressed_key = 0 ;
            break ;

        case 15 : pressed_key = '#';
            break ;

        case 16 : pressed_key = 'D';
            break;


        default : /* Do Nothing */
            break  ;

    }
    return pressed_key;
}

#endif


#endif 
