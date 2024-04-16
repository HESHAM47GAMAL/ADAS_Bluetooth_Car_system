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


#define Timer0_OVF_1_sec_RTClock                    8
#define Timer0_OVF_5_sec_DrivingMonetoring          85
#define Timer0_OVF_Buzzer_Notify_sound              4

#define EEPROM_LOCATION    0x10


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


/*
*   @brief : this function used to to Update only state of Speed limit System in DashBoard
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/ 
 static void DashBoard_Update_SpeedLimiter_State(uint8 SL_state);


/*
*   @brief : this function used to to Update status of Speed limit (D , 🔔 or 🔇) System in DashBoard
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/ 
 static void DashBoard_SpeedLimit_status_update(void);

/*
*   @brief : this function used to to Update speed limit value for car
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/ 
 static void DashBoard_updateSpeedLimitValue(void);


/*
*   @brief : this function used to to Update only state of Brake assist System in DashBoard
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/ 
 static void DashBoard_Update_BrakingAssist_State(uint8 BA_state);


/*
*   @brief : this function used to to Update status of brake assist (D , 🔔 or 🔇) System in DashBoard
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/ 
static void DashBoard_BrakingAssist_Status_update(void);


/*
*   @brief : this function used to to Update last row in dashboard that represent number of page
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/ 
 static void DashBoardPageFooter_update(void);

/*
*   @brief : this function used to Update some information in dashboard when switch from page to another
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/ 
static void DashBoard_SwitchPages(void);

/*
*   @brief : this function used to to Update only state of Driving Monitoring System in DashBoard
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void DahBoard_Update_DrivingMonetoring_State(uint8 DM_state);

/*
*   @brief : this function used to to Update status of Driving Monitoring (D , 🔔 or 🔇) System in DashBoard
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/ 
static void DashBoard_DrivingMonetoring_Status_update(void);

/*
*   @brief : this function used to to Update status of Driving Monitoring (D , 🔔 or 🔇) System in DashBoard as periodicly call above function
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void DashBoard_DrivingMonetoring_continous_Status_update(void);

/*
*   @brief : this function used to update time when user in page of time and date
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void DashBoard_updateTime(void);



/*
*   @brief : this function is program that will be called (ISR) when Braking Button pressed 
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void Braking_Button_Handling(void);

/*
*   @brief : this function used to start program and load some inforamation from EXT EEPROM and store information when turn engine off
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void Engine_Control_Handling(void);

/*  This only function used with brake ISR that to make push to it in stack and when same ISR happen make context switch and return to function */
/*  Try to Ask Eng Mohamed Helmy    */

void tessst (void);


/*
*   @brief : this function used to handle some cases that need to know that brake button still pressed like Driving monitoring
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Braking_LongPressHandle(void);




/*
*   @brief : this function used to get last value from ultrasonic sensor 
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void Radar_CatchDistance(void);

/*
*   @brief : this function used to decide action will taken when brake assist opened to avoid crushing
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void BrakeAssist_DicisionTake(void);


/*
*   @brief : this function used to catch pressed buttons 
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void APP_KeypadUpdate(void);


/*
*   @brief : this function used to update speed car depend on potentiometer value and if brake button pressed or brake assist perform any action of any senario
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void App_CarSpeedUpdate(void);

/*
*   @brief : this function used to comapre between car speed and speed limit and take action 
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void GetDiffCarSpeed_and_limit(void);



/* 
*   @brief : this function used to to handle Real Time clock and make constant time for switch between high and low for buzzer and Relay 
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Asynchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void TImer0_OVF_Handling_Fun(void);

/* 
*   @brief : this function used to update kilo meters moved by car if dashboard currently in page 2
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Asynchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static void APP_CarMovedKiloMeters(void);

/* 
*   @brief : this function used to catch message from mobile application and update some states depend on message content
*   @args  void
*   @return: no return
*   @synchronous / Asynchronous : Asynchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Bluetooth_Buffer_Decision(void);