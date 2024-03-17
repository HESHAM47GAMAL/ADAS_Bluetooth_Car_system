 /******************************************************************************
 *
 * Module: Application
 *
 * File Name: Application_private.h
 *
 * Description: contain function Prototype for static functions
 * 
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "../SERVICE/STD_TYPES.h"

/**************************                   Function Prototype                   **************************/


/*
*   @ Brief : this function used to initialize everything in out rogram
*   @ Arguments :   void
*   @ Returns : no return
*   @ Synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/

void A_APPLICATION_VOID_INIT(void);








/*
*   @ Brief : this function used to run everything withn state machine
*   @ Arguments :   void
*   @ Returns : no return
*   @ Synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/

void StateMachineUpdate(void);







/*
*   @ Brief : this function is responsible fo which LCD screen we are on
*   @ Arguments :   void
*   @ Returns : no return
*   @ Synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/


void A_APPLICATION_VOID_MAIN_LCD_SCREEN_SELECT(void);







/*
*   @ Brief : this function is responsible for checking which button in keypad is pressed
*   @ Arguments :   void
*   @ Returns : no return
*   @ Synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void A_APPLICATION_VOID_KEYPAD_BUTTON_READ(void);







/*
*   @ Brief : this function is for Loading infro on lcd on first run of program
*   @ Arguments :   void
*   @ Returns : no return
*   @ Synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void A_APPLICATION_VOID_MAIN_LCD_LOAD(void);






/*
*   @ Brief : this function is For printing whatever wont change on all three screens
*   @ Arguments :   void
*   @ Returns : no return
*   @ Synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/


void A_APPLICATION_VOID_MAIN_LCD_STATICS(void);








/*
*   @ Brief : this function is For Displaying which gear on lcd
*   @ Arguments :   which gearbox state we are in
*   @ Returns : no return
*   @ Synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/

void A_APPLICATION_VOID_GBX_DISPLAY(uint8 state);




/*
*   @ Brief : this function is For changing the gearbox state
*   @ Arguments :   void
*   @ Returns : no return
*   @ Synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/

void A_APPLICATION_VOID_GBX_CHANGE(void);





//void Test_B(void)
//{
//    uint8 ACCS_State_bTN = BUTTON_GetValue(ACCS_BTN_PORT,ACCS_BTN_PIN);
//    static uint8 ACCS_BTN_IsPressed = LOGIC_LOW ;
//    if(ACCS_State_bTN == LOGIC_LOW)
//    {
//        if(ACCS_BTN_IsPressed == LOGIC_LOW)
//        {
//            LED_Toggle(Green_LED_PORT,Green_LED_PIN);
//            ACCS_BTN_IsPressed = LOGIC_HIGH ;
//        }
//    }
//    else
//    {
//        ACCS_BTN_IsPressed = LOGIC_LOW ;
//    }
//
//}
