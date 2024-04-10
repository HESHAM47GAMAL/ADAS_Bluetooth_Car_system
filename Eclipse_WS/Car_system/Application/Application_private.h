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




/**************************                   Definition                   **************************/
#define Keypad_GearBox_pressed_value            2
#define Keypad_Page_R_pressed_value             3
#define Keypad_Page_L_pressed_value             1
#define Keypad_CCS_pressed_value                0
#define Keypad_SpeedLimit_Dec_pressed_value     7
#define Keypad_SpeedLimit_ON_OFF_pressed_value  8
#define Keypad_SpeedLimit_Inc_pressed_value     9
#define Keypad_BrakingAssist_pressed_value      '*'
#define Keypad_DrivingMonetoring_pressed_value  '#'


#define MAX_CAR_SPEED                           200 

#define Max_Speed_Limit_value                   120
#define Min_speed_Limit_value                   20


#define Value_Loading_Timer1                    ((uint16)57723)


#define Timer0_OVF_1_sec_RTClock                    100
#define Timer0_OVF_5_sec_DrivingMonetoring          85
#define Timer0_OVF_Buzzer_Notify_sound              3

/**************************                   Function Prototype                   **************************/

/***************************Gear BOX Functions*****************************/

/*
*   @brief : this function used to handle All action may happen In N GearBox mode
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void Hanndle_GrearBox_N_State(void);


/*
*   @brief : this function used to handle All action may happen In R GearBox mode
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void Hanndle_GrearBox_R_State(void);


/*
*   @brief : this function used to handle Adaptive Cruise control sysytem will all condition available in statemachine 
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void Hanndle_GrearBox_D_State(void);



/***************************Bashboard*****************************/
/*
*   @brief : this function used to initialize what will be displayed in DashBoard(LCD) 
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
 static void DashBoard_Init(void);

/*
*   @brief : this function used to to Update only state of GearBox in DashBoard
*   @arg1  GearBox_state : state of GearBox that will be updated in Dashboard
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
 static void DashBoard_Update_GearBox_state(uint8 GearBox_state);


/*
*   @brief : this function used to to Update only state of Adaptive Cruise Control System in DashBoard
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
 static void DashBoard_Update_CCS_State(uint8 ACCS_state);


 
 static void DashBoard_Update_SpeedLimiter_State(uint8 SL_state);


 static void DashBoard_updateSpeedLimitValue(void);

 /*  tell me status for Speed Limit if it D , 🔔 or 🔇*/
 static void DashBoard_SpeedLimit_status_update(void);
 
 static void DashBoard_Update_BrakingAssist_State(uint8 BA_state);




 static void APP_DashBoardPage_update(void);


static void APP_DashBoard_SwitchPages(void);

static void App_GetDiffCarSpeed_and_limit(void);



static void DahBoard_Update_DrivingMonetoring_State(uint8 DM_state);


static void DashBoard_DrivingMonetoring_Status_update(void);

static void DashBoard_DrivingMonetoring_continous_Status_update(void);



static void DashBoard_updateTime(void);






/*
*   @brief : this function is program that will be called (ISR) when Braking Button pressed 
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void Braking_Button_Handling(void);

/*  This only function used with brake ISR that to make push to it in stack and when same ISR happen make context switch and return to function */
/*  Try to Ask Eng Mohamed Helmy    */

void tessst (void);


void Braking_LongPressHandle(void);



/*
*   @brief : this function is used to set buzzer high and initialize timeout period 
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void Buzzer_NotifySound(void);

/*
*   @brief : this function is program that will be called (ISR) when Timeout happen as turn buzzer off
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Buzzer_timeOutOff(void);




/*
*   @brief : this function used to get last value from Potentiometer and Display it
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void ACCS_CatchDistance(void);


static void ACCS_DicisionTake(void);



static void ACCS_PID(uint8 braking_value);


static void APP_KeypadUpdate(void);



static void App_CarSpeedUpdate(void);



// static void App_TimeOut_handle_DM_Time(void);


/* 
*   @brief : this function used to to handle Real Time clock and make constant time for switch between high and low for buzzer and Relay 
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Asynchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void TImer0_OVF_Handling_Fun(void);


/**************************************  For Small LCD ***********************/
    // static void DashBoard_Init_small(void);
    // static void DashBoard_Update_GearBox_state_small(uint8 GearBox_state);
    // static void DashBoard_DistanceShow_small(void);
    // static void DashBoard_DistanceHide_small(void);
    // static void DashBoard_UpdateSpeed(void);
    // static void APP_DashBoardPage_update_small(void);

// /*
// *   @brief : this function used to Show only "Distance : " in LCD
// *   @args  void
// *   @return: no return
// *   @synchronous / Asynchronous : Synchronous
// *   @ Reentrant / Non Reentrant : Reentrant
// */
//  static void DashBoard_DistanceShow(void); 


// /*
// *   @brief : this function used to hide all data in last row by display white space "                  "
// *   @args  void
// *   @return: no return
// *   @synchronous / Asynchronous : Synchronous
// *   @ Reentrant / Non Reentrant : Reentrant
// */
//  static void DashBoard_DistanceHide(void);




// /*
// *   @brief : this function used to get update of Buttons 
// *   @args  void
// *   @return: no return
// *   @synchronous / Asynchronous : Synchronous
// *   @ Reentrant / Non Reentrant : Reentrant
// */
// static void Buttons_Update(void);