/******************************************************************************
 *
 * Module: Application
 *
 * File Name: Application_program.c
 *
 * Description: source file for implementation for all functionality for Application Specefic
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/



/**************************                   INCLUDES                   **************************/

#include "Application_interface.h"
#include "Application_private.h"
#include "../SERVICE/IVT.h"




/**************************                   Extern variables                   **************************/

/*  Array that carry values for New Custom Character  */
extern uint8 LCD_Page_Not_Selected [] ;
extern uint8 LCD_Page_Selected [] ;
extern uint8 LCD_Right_ICON [] ;
extern uint8 LCD_False_ICON [] ;
extern uint8 LCD_Mute_ICON [] ;
extern uint8 LCD_Skull_ICON [] ;
extern uint8 LCD_Alarm_ICON [] ;

/*  Locations that this custom characters Stored  */
#define POS_LCD_Page_Not_Selected               LCD_CGRAM_LOCATION_1
#define POS_LCD_Page_Selected                   LCD_CGRAM_LOCATION_2
#define POS_LCD_Right_ICON                      LCD_CGRAM_LOCATION_3
#define POS_LCD_False_ICON                      LCD_CGRAM_LOCATION_4
#define POS_LCD_Mute_ICON                       LCD_CGRAM_LOCATION_5
#define POS_LCD_Skull_ICON                      LCD_CGRAM_LOCATION_6
#define POS_LCD_Alarm_ICON                      LCD_CGRAM_LOCATION_7



/**************************                   Type Declaration                    **************************/
enum GearBox_State {N_GearBox,D_GearBox,R_GearBox , GearBox_Return_to_N};

enum CCS_State {CCS_Disable,CCS_Enable};

enum SpeedLimit_State {SpeedLimit_Disable , SpeedLimit_Enable};

enum BrakingAssist_State {BrakingAssist_Disable , BrakingAssist_Enable} ;

enum DirivingMonetoring_State {DirivingMonetoring_Disable , DirivingMonetoring_Enable};

/*  🙆‍♂️Note I start with page 2  that has main parameter     */
enum Page_State{Page_1_LCD , Page_2_LCD , Page_3_LCD  , Page_4_LCD};
//                  BA          main        SL              date & time



volatile uint8 Temp_Speed ;
sint16 Diff_between_ADCS ;
/**************************                   Global variable                   **************************/

uint8 GearBox_Current_State = N_GearBox; /* Carry current state of GearBox*/

uint8 CCS_Currnet_state = CCS_Disable; /* Carry Current dtate of ACCS and Note that it will take in consideration when GearBox_State == D*/

sint8 Page_Current_State = Page_2_LCD; /*   -128 :127*/

uint8 SpeedLimit_Current__State = SpeedLimit_Disable ;

uint8 BrakingAssist_Current_State = BrakingAssist_Disable;

uint8 DrivingMonetoring_Current_State = DirivingMonetoring_Disable ;


/*  Should be signed as If press brake in N mode will decrease -2 and if data type uint8 so when decrease will happen underflow and if value equal Zero at first so will be 254 so program will have bug*/
static volatile sint16 Car_Speed = 0; /*  Global variable carry Speed of Car  */

/*  carry state of Braking Button that updated by Interrupt and this variable take copy of last state of Braking Button  */
static volatile uint8 Global_Braking_BTN_State = BTN_Released_State ;

/*  This variable store intail value for speed Limiter*/
static volatile uint8 Global_Speed_Limiter_value = 40 ; /*  Set intail value 40 as no limit speed under 40 KM/h*/



volatile float32 distance_ACCS = 0 ;    /*  Global Variable carry distance between my car and car in front  of me and will take in consideration when GearBox_State == D && ACCS_state == ON   */

/*  object declare for DC motor  */
DC_Pin_Type DC_pins_Motor = {DC_RIR_1_PORT,DC_RIR_1_PIN,DC_RIR_2_PORT,DC_RIR_2_PIN };



/* status Available for this Speed Limiter system  */
enum Speed_Limit_Status{Speed_Limit_Failed , Speed_Limit_Meet} ;

/* status Available for this Braking Assist system  */
enum Distance_BA_status {Distance_BA_Failed , Distance_BA_Meet} ;

/* status Available for this Driving Monitoring system  */
enum DrivingMonetoring_Status {DM_Failed    ,   DM_Meet};
//                            make alarm       don't make alarm     


uint8 Speed_limit_Current_Status = Speed_Limit_Meet;


uint8 Distance_BA_Current_status = Distance_BA_Meet;


uint8  DrivingMonetoring_Current_Status = DM_Meet ;


/* Carry number of interrupt happen for TImer 0 */
uint8 TimeOut_Counter = 0 ; // old varaible it used for real time and Driving monetering with Timer 1

/* Varaibles used to update Real Time Clock  */
uint8 Clock_sec = 12; 
uint8 Clock_min = 30 ;
uint8 Clock_hour = 2 ;

/*  Used to store how many of kilo meters car Moved  */
float64 Accumulative_Distance_KM = 0.0 ;


/*  Carry number of overflow for 1 second for Real time clock*/
uint8 Timer0_Overflow_Counter_RTClock = 0;

/*  Carry number of overflow for 5 second for Driving monetring*/
uint16 Timer0_Overflow_counter_DM = 0 ;

uint8 Buzzer_GiveSound =  NO_Condition  ;
uint8 Buzzer_Timer0_OVF_count = 0 ;

/*  👀👀 Function called inside While(1) Loop  */

void App_StateMachineUpdate(void)
{
    Hanndle_GrearBox_N_State();

    // Hanndle_GrearBox_D_State();

    Hanndle_GrearBox_R_State();


    APP_KeypadUpdate();

    Braking_LongPressHandle();

    App_CarSpeedUpdate ();

    GetDiffCarSpeed_and_limit();

    /*  make continous update for dashboard if I in page 2   */
    DashBoard_DrivingMonetoring_continous_Status_update();
    
    /*  used to update time if I in page 4*/
    DashBoard_updateTime();

    /*  Update Kilko meters for Kilo metrers moved in Dashboard */  
    APP_CarMovedKiloMeters();

}


static void Hanndle_GrearBox_D_State(void)
{
    if((CCS_Currnet_state == CCS_Enable) && (D_GearBox == GearBox_Current_State))
    {
       // ACCS_CatchDistance();
        /*  may be interrupt happen here so inside next function check if brake button pressed and make disable for ACCS    */
       // ACCS_DicisionTake();
        
    }
}



static void Hanndle_GrearBox_N_State(void)
{
    if(GearBox_Current_State == N_GearBox)
    {
        if(CCS_Currnet_state == CCS_Enable)
        {
            /*  Disable ACCS if Enabled  */
            CCS_Currnet_state = CCS_Disable;
            /*  Update LCD with new change*/
            DashBoard_Update_CCS_State(CCS_Currnet_state);
            
            //DashBoard_DistanceHide();
           // DashBoard_DistanceHide_small();

        }
    }
   
}


static void Hanndle_GrearBox_R_State(void)
{
    if(GearBox_Current_State == R_GearBox)
    {
        /*  Turn off led that work in Adaptive cruise control  as may make switch by gearBox so I need to handle this   */
        //LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_OFF);
        if(CCS_Currnet_state == CCS_Enable)
        {
            /*  Disable ACCS if Enabled  */
            CCS_Currnet_state = CCS_Disable;

            /*  Update LCD with new change*/
            DashBoard_Update_CCS_State(CCS_Currnet_state);
            
            //DashBoard_DistanceHide();
            //DashBoard_DistanceHide_small();
        }

        if(DrivingMonetoring_Current_State == DirivingMonetoring_Enable)
        {
            DrivingMonetoring_Current_State = DirivingMonetoring_Disable ;
            /*  Update in LCD */
            DahBoard_Update_DrivingMonetoring_State(DrivingMonetoring_Current_State);

        }

        /*  If it was Speed Limiter enabled should disabled and update in LCD*/
        if(SpeedLimit_Current__State == SpeedLimit_Enable)
        {
            /*  Disable BA Sysystem */
            SpeedLimit_Current__State = SpeedLimit_Disable ;
            
            /*  Update LCD with new change*/
            DashBoard_Update_SpeedLimiter_State(SpeedLimit_Current__State);
        }

    }
}




void App_Init(void)
{
    /*	Enable Global Interrupt  */
	sei();

    /*  Intialize LCD   */
    LCD_init();

    /*  Initalize New custom character */
    LCD_GenerateCharacterCGRAM(LCD_Page_Not_Selected,POS_LCD_Page_Not_Selected);
    LCD_GenerateCharacterCGRAM(LCD_Page_Selected,POS_LCD_Page_Selected);
    LCD_GenerateCharacterCGRAM(LCD_Right_ICON,POS_LCD_Right_ICON);
    LCD_GenerateCharacterCGRAM(LCD_False_ICON,POS_LCD_False_ICON);
    LCD_GenerateCharacterCGRAM(LCD_Mute_ICON,POS_LCD_Mute_ICON);
    LCD_GenerateCharacterCGRAM(LCD_Skull_ICON,POS_LCD_Skull_ICON);
    LCD_GenerateCharacterCGRAM(LCD_Alarm_ICON,POS_LCD_Alarm_ICON);

    /*  Initialize Buzzer */
    Buzzer_Init(Buzzer_PORT,Buzzer_PIN);


    /*  Initialize Braking Button with EXT_INT 1    */
    INT1_init(FALLING_EDGE_TRIGGER,INPUT_PIN);

    /*  Set call back function  */
    INT1_SetCallBack(Braking_Button_Handling);

    /*  Initialize LEDS(Red,Yellow) all os them connected positive logic */

    LED_Init(Red_LED_PORT,Red_LED_PIN);
    LED_Init(Yellow_LED_PORT,Yellow_LED_PIN);

    /*  Initailize Relay Pin  */
    GPIO_SetPinDirection(Relay_PORT,Relay_PIN,OUTPUT_PIN);

    /*  Initialize pins that control direction for DC motor  */
    GPIO_SetPinDirection(DC_RIR_1_PORT,DC_RIR_1_PIN,OUTPUT_PIN);
    GPIO_SetPinDirection(DC_RIR_2_PORT,DC_RIR_2_PIN,OUTPUT_PIN);
    /*  initialize PWM pin fo motor  */
    DC_Motor_Init(&DC_pins_Motor);
    /*  Turn Of all of this led  */
    LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN, LED_OFF);
    LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN, LED_OFF);

    /*  initialize Timer0   */
    Timer0_Init();
    

    /*  Set callback function that will called when Timeout happen to turn of buzzer and handle anything another    */
    Timer0_SetCallBack(TImer0_OVF_Handling_Fun);
    
    /*  Enable Overflow Interrupt  */
    Timer0_Enable_OVR_Flow_Interrupt();

    // /*  Initailize Timer 1*/
    // Timer1_Init();

    // /*  Set callback for finction that will hanle DM and Time */
    // Timer1_SetCallBack(App_TimeOut_handle_DM_Time);

    // Timer1_ProvideClock();

    /*  Initialize ADC to be used by Potentiometer to accelerate  */
    ADC_Init();

    /*  Intialize Potentiometer */
    POT_Init(ADC_Channel_0);

    /*  Initailize Keypad  */
    Keypad_init();

    /*  Intialize Bash Board for Car*/
    DashBoard_Init();
}


static void DashBoard_Init(void)
{
    cli();
    LCD_MoveCursor(0,0);
    LCD_DisplayString((const uint8 * )"DM Status:");
    /*  call function that will handle status for DM  */
    DashBoard_DrivingMonetoring_Status_update();

    /*  Display GearBox Current state  */
    LCD_MoveCursor(0,14);
    LCD_DisplayString((const uint8 * )"GB : N");

    /*  Display kilo meters counter value  */
    LCD_MoveCursor(1,0);
    LCD_DisplayString((const uint8 * )"KMC:"); 
    LCD_FloatToString(Accumulative_Distance_KM);

    /*  Display speed */
    LCD_MoveCursor(1,11);
    LCD_DisplayString((const uint8 * )"SP:"); 
    /*  Call function that catch current speed to dispaly  */
    App_CarSpeedUpdate();

    /*  Display state of Adaptive Cruise control  */
    LCD_MoveCursor(2,0);
    LCD_DisplayString((const uint8 * )"CC:");
    LCD_DisplayCharacter(POS_LCD_False_ICON);

    LCD_DisplayString((const uint8 * )" BA:");
    LCD_DisplayCharacter(POS_LCD_False_ICON);

    LCD_DisplayString((const uint8 * )" SL:");
    LCD_DisplayCharacter(POS_LCD_False_ICON);

    LCD_DisplayString((const uint8 * )" DM:");
    LCD_DisplayCharacter(POS_LCD_False_ICON);

    /*  call function that Display pages and @ first when start program I will be in Page 2 */
    DashBoardPageFooter_update();
    sei();
}



static void DashBoard_Update_GearBox_state(uint8 GearBox_state)
{
    cli();
    /*  Array carry All Characters For GearBox as make display easier using index*/
    uint8 GearBox_Characyer [] = {'N','D','R'};
    /*  Go to index that display current GearBox state*/
    LCD_MoveCursor(0,19);
    /*  Edit its state with new state given to function*/
    LCD_DisplayCharacter(GearBox_Characyer[GearBox_state]);
    sei();
}

static void DashBoard_Update_CCS_State(uint8 ACCS_state)
{
    cli();
        
        /*  Go to index that display current GearBox state*/
        LCD_MoveCursor(2,3);

        /*  Edit its state with new state given to function*/
        if(CCS_Currnet_state == CCS_Enable)
            LCD_DisplayCharacter(POS_LCD_Right_ICON);

        else
            LCD_DisplayCharacter(POS_LCD_False_ICON);

    sei();
}

static void DashBoard_Update_BrakingAssist_State(uint8 BA_state)
{
    cli();
    /*  Go to index that display current GearBox state*/
        LCD_MoveCursor(2,8);
            /*  Edit its state with new state given to function*/
        if(BA_state == BrakingAssist_Enable)
            LCD_DisplayCharacter(POS_LCD_Right_ICON);

        else
            LCD_DisplayCharacter(POS_LCD_False_ICON);
    sei();
}


static void DashBoard_Update_SpeedLimiter_State(uint8 SL_state)
{
    cli();
        /*  Go to index that display current GearBox state*/
        LCD_MoveCursor(2,13);

        /*  Edit its state with new state given to function*/
        if(SL_state == SpeedLimit_Enable)
            LCD_DisplayCharacter(POS_LCD_Right_ICON);

        else
            LCD_DisplayCharacter(POS_LCD_False_ICON);
    sei();
}


static void DashBoard_updateSpeedLimitValue(void)
{
    if(Page_Current_State == Page_3_LCD)
    {
        cli();
        //Global_Speed_Limiter_value
        LCD_MoveCursor(0,7);
        LCD_intToString(Global_Speed_Limiter_value);
        LCD_DisplayString("KMH ");
        sei();
    }
}


static void GetDiffCarSpeed_and_limit(void)
{
    if(Car_Speed > Global_Speed_Limiter_value)
    {
        /*  Update Status  */
        Speed_limit_Current_Status = Speed_Limit_Failed ;
    }
    else if(Car_Speed <= Global_Speed_Limiter_value)
    {
        Speed_limit_Current_Status = Speed_Limit_Meet ;
    }
    if(Page_Current_State == Page_3_LCD)
    {
        /*  Make update in LCD  and give sound notify */
        DashBoard_SpeedLimit_status_update();
    }
    else /* give sound notify  */
    {
        if((SpeedLimit_Current__State == SpeedLimit_Enable) && (Speed_limit_Current_Status == Speed_Limit_Meet))
        {
            GPIO_WritePin(Relay_PORT,Relay_PIN,LOGIC_LOW);
        }
        else if((SpeedLimit_Current__State == SpeedLimit_Enable) && (Speed_limit_Current_Status == Speed_Limit_Failed))
        {
            GPIO_TogglePin(Relay_PORT,Relay_PIN);
        }
    }
}

static void DashBoard_SpeedLimit_status_update(void)
{
    // if(Page_Current_State == Page_3_LCD)
    // {
        cli();
        LCD_MoveCursor(1,9);
        if(SpeedLimit_Current__State == SpeedLimit_Enable)
        {
            if(Speed_limit_Current_Status == Speed_Limit_Meet)
            {
                LCD_DisplayCharacter(POS_LCD_Mute_ICON);
                /*  stop sound of relay  */
                GPIO_WritePin(Relay_PORT,Relay_PIN,LOGIC_LOW);
            }
            else
            {
                LCD_DisplayCharacter(POS_LCD_Alarm_ICON);
                /*  Action Will taken notify user  as it sound of relay switch*/
                GPIO_TogglePin(Relay_PORT,Relay_PIN);
            }
        }
        else 
        {
            LCD_DisplayCharacter('D'); //system disabled
        }
        sei();
    // }
}

static void DahBoard_Update_DrivingMonetoring_State(uint8 DM_state)
{
    cli();
    /*  Go to index that display current Driving Monetoring state*/
    LCD_MoveCursor(2,18);

    if(DM_state == DirivingMonetoring_Enable)
    {
        LCD_DisplayCharacter(POS_LCD_Right_ICON);
    }
    else 
    {
        LCD_DisplayCharacter(POS_LCD_False_ICON);
    }

    sei();

}

static void DashBoard_DrivingMonetoring_Status_update(void)
{
    cli();
    LCD_MoveCursor(0,10);
    if(DrivingMonetoring_Current_State == DirivingMonetoring_Enable)
    {
        if(DrivingMonetoring_Current_Status == DM_Meet)
        {
            LCD_DisplayCharacter(POS_LCD_Mute_ICON);
        }
        else
        {
            LCD_DisplayCharacter(POS_LCD_Alarm_ICON);
        }
    }
    else
    {
        LCD_DisplayCharacter('D'); //system disabled
    }
    sei();
}

static void DashBoard_DrivingMonetoring_continous_Status_update(void)
{
    if(Page_Current_State == Page_2_LCD)
    {
        DashBoard_DrivingMonetoring_Status_update();
    }
}




static void DashBoardPageFooter_update(void)
{
    
    uint8 pages_option [4][4] = { {POS_LCD_Page_Selected , POS_LCD_Page_Not_Selected , POS_LCD_Page_Not_Selected , POS_LCD_Page_Not_Selected} , {POS_LCD_Page_Not_Selected , POS_LCD_Page_Selected , POS_LCD_Page_Not_Selected , POS_LCD_Page_Not_Selected} , {POS_LCD_Page_Not_Selected , POS_LCD_Page_Not_Selected , POS_LCD_Page_Selected , POS_LCD_Page_Not_Selected} , {POS_LCD_Page_Not_Selected , POS_LCD_Page_Not_Selected , POS_LCD_Page_Not_Selected , POS_LCD_Page_Selected} };
    cli();
    LCD_MoveCursor(3,8);
    /*  Display indicator for current page  */
    LCD_DisplayCharacter(pages_option[Page_Current_State][0]);
    LCD_DisplayCharacter(pages_option[Page_Current_State][1]);
    LCD_DisplayCharacter(pages_option[Page_Current_State][2]);
    LCD_DisplayCharacter(pages_option[Page_Current_State][3]);
    sei();
}




static void DashBoard_SwitchPages(void)
{
    cli();
    LCD_MoveCursor(0,0);
    LCD_DisplayString("              ");
    LCD_MoveCursor(1,0);
    LCD_DisplayString("           ");
    /*  Main window that I start with  */
    if(Page_Current_State == Page_2_LCD)
    {
        /*  display data for Driving monetoring */
        LCD_MoveCursor(0,0);
        LCD_DisplayString((const uint8 * )"DM Status:");
        /*  Call function that will handle status for DM */
        DashBoard_DrivingMonetoring_Status_update();

        /*  Display kilo meters counter value  */
        LCD_MoveCursor(1,0);
        LCD_DisplayString((const uint8 * )"KMC:"); 
        LCD_FloatToString(Accumulative_Distance_KM);
    }
    else if(Page_Current_State == Page_1_LCD)
    {
        if(BrakingAssist_Current_State == BrakingAssist_Enable)
        {
            LCD_MoveCursor(0,0);
            LCD_DisplayString("DIS : ");
            LCD_MoveCursor(1,0);
            LCD_DisplayString("Status : ");
        }
        else 
        {
            LCD_MoveCursor(0,0);
            LCD_DisplayString("Disabled");
        }

    }
    else if(Page_Current_State == Page_3_LCD)
    {
        LCD_MoveCursor(0,0);
        LCD_DisplayString("SLIM : ");
        LCD_intToString(Global_Speed_Limiter_value);
        LCD_DisplayString("KMH ");
        LCD_MoveCursor(1,0);
        LCD_DisplayString("Status : ");
        /* update Icons of speed limit status  */
        DashBoard_SpeedLimit_status_update();
    }
    else if(Page_Current_State == Page_4_LCD)
    {
        LCD_MoveCursor(0,0);
        LCD_DisplayString("D=18/3/2024");
        DashBoard_updateTime();

        

    }
    sei();
}


static void APP_KeypadUpdate(void)
{
    /*  This variable used to carry if button is still pressed after last pressed as any action taken once with first step and if still press nothing happen    */
    static uint8 GearBox_IsStillPressed = NO_Condition;

    /*  This variable used to carry if button is still pressed after last pressed as any action taken once with first step and if still press nothing happen    */
    static uint8 CCS_IsStillPressed = NO_Condition;

    static uint8 R_Page_IsStillPressed = NO_Condition;

    static uint8 L_Page_IsStillPressed = NO_Condition;

    static uint8 SL_ON_OFFIsStillPressed = NO_Condition ;

    static uint8 SL_IncIsStillPressed = NO_Condition ;

    static uint8 SL_DecIsStillPressed = NO_Condition ;

    static uint8 BrakingAssit_IsStillPressed = NO_Condition ;

    static uint8 DrivingMonetoring_IsStillPressed = NO_Condition ;

    volatile sint8 local_currentValue_keypad = Keypad_GetPressedKey();/* Take last keypad pressed button */
    /*  This if used to see only value of button pressed in Keypad  */
    // if(local_currentValue_keypad >= 0 )
    // {
            
    //     LCD_MoveCursor(3,0);
    //     /*✍️LCD_SMALL_LARGE*/
    //     //LCD_MoveCursor(1,0);
    //     if(local_currentValue_keypad < 10)
    //         LCD_DisplayCharacter((local_currentValue_keypad + '0'));
    //     else 
    //         LCD_DisplayCharacter(local_currentValue_keypad);
    // }
    // LCD_MoveCursor(3,2);
    // LCD_intToString(Global_Speed_Limiter_value);
    // LCD_DisplayCharacter(' ');


/* (Button 1️⃣) Handle GearBox Button   */

    /*  👀👀👀👀👀👀GearBox switch only happen when press on gearbox and brake button in same time  */
    if( (local_currentValue_keypad == Keypad_GearBox_pressed_value) && (Global_Braking_BTN_State == BTN_Pressed_State) )
    // if((local_currentValue_keypad == Keypad_GearBox_pressed_value))
    {
        /*  Make counter with zero to start count from zero for DM */
        // TimeOut_Counter = 0 ;//old one when I use timer1
        Timer0_Overflow_counter_DM = 0 ;

        /*  Change state to update in LCD*/
        DrivingMonetoring_Current_Status = DM_Meet ;

        /*  This condition placed here to take action for button press only when pressed and if still pressed Do nothing    */
        if(GearBox_IsStillPressed == NO_Condition)
        {
            GearBox_IsStillPressed = YES_Condition ;
            /* turn buzzer on and give timer 0 clock and set timeout    */
            Buzzer_GiveSound = YES_Condition; 

            /*  Go to next state for gearbox*/
            GearBox_Current_State ++ ;
            if(GearBox_Current_State == GearBox_Return_to_N  )
            {
                GearBox_Current_State = N_GearBox ;
                
            }

            /*  call function to update gearbox state in Dashboard*/
            DashBoard_Update_GearBox_state(GearBox_Current_State);

        }
        
    }
    else
    {
        /*  Enter this state when Button released*/
        GearBox_IsStillPressed = NO_Condition ;
    }

    /*  There buttons shouldn't take any action except on D mode like(Cruise Control , Braking Assist and Speed limiter)*/
    if(GearBox_Current_State == D_GearBox)
    {
/* (Button 2️⃣) Handle Cruise Control system   */
        if(local_currentValue_keypad == Keypad_CCS_pressed_value) 
        {
            /*  Make counter with zero to start count from zero for DM */
            // TimeOut_Counter = 0 ;//old one when I use timer1
            Timer0_Overflow_counter_DM = 0 ;

            /*  Change state to update in LCD*/
            DrivingMonetoring_Current_Status = DM_Meet ;

            /*  This condition placed here to take action for button press only when pressed and if still pressed Do nothing    */
            if(CCS_IsStillPressed == NO_Condition)
            {
                CCS_IsStillPressed = YES_Condition ;
                /* turn buzzer on and give timer 0 clock and set timeout    */
                Buzzer_GiveSound = YES_Condition; 

                if(CCS_Currnet_state == CCS_Disable ) 
                {
                    
                    /*  Update ACCS state with new value (Enabled)*/
                    CCS_Currnet_state = CCS_Enable;
                    DashBoard_Update_CCS_State(CCS_Currnet_state);
                    
                }
                else
                {
                    CCS_Currnet_state = CCS_Disable;

                    /*  Turn off led that work in Adaptive cruise control  as may be  in not safe area and  turn off Adaptive cruise control   */
                    //LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_OFF);
                    /*  🚩🚩🚩🚩🚩🚩🙆‍♂️🙆‍♂️🙆‍♂️ i think that I need to put diable and enable to interrupt as I may be ACCS enabled and when I disable and press braiking at same time */
                    //LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN,LED_OFF);

                    DashBoard_Update_CCS_State(CCS_Currnet_state);

                }
            }
            
        }
        else
        {
            /*  Enter this state when Button released*/
            CCS_IsStillPressed = NO_Condition ;
        }
/* (Button 3️⃣) Handle Speed Limiter system   */
        /*  Handle Speed Limiter System Button   */
        if(local_currentValue_keypad == Keypad_SpeedLimit_ON_OFF_pressed_value) 
        {
            /*  Make counter with zero to start count from zero for DM */
            // TimeOut_Counter = 0 ;//old one when I use timer1
            Timer0_Overflow_counter_DM = 0 ;

            /*  Change state to update in LCD*/
            DrivingMonetoring_Current_Status = DM_Meet ; 


            /*  This condition placed here to take action for button press only when pressed and if still pressed Do nothing    */
            if(SL_ON_OFFIsStillPressed == NO_Condition)
            {
                SL_ON_OFFIsStillPressed = YES_Condition ;
                /* turn buzzer on and give timer 0 clock and set timeout    */
                Buzzer_GiveSound = YES_Condition; 

                if(SpeedLimit_Current__State == SpeedLimit_Disable)
                {
                    /*  update State of Speed Limiter   */
                    SpeedLimit_Current__State = SpeedLimit_Enable ;
                    /*  Call updater for Speed limiter state */
                    DashBoard_Update_SpeedLimiter_State(SpeedLimit_Current__State);
                }
                else 
                {
                    /*  update State of Speed Limiter   */
                    SpeedLimit_Current__State = SpeedLimit_Disable ;
                    /*  Call updater for Speed limiter state */   
                    DashBoard_Update_SpeedLimiter_State(SpeedLimit_Current__State);
                    /*  stop sound of relay  as may be close this system and I also my speed higher than limit speed */
                    GPIO_WritePin(Relay_PORT,Relay_PIN,LOGIC_LOW);
                }
            }  
        }
        else
        {
            SL_ON_OFFIsStillPressed = NO_Condition ;
        } 

/* (Button 4️⃣) Handle Braking Assist system   */
        if(local_currentValue_keypad == Keypad_BrakingAssist_pressed_value)
        {
            /*  Make counter with zero to start count from zero for DM */
            // TimeOut_Counter = 0 ; //old one when I use timer1
            Timer0_Overflow_counter_DM = 0 ;
            
            /*  Change state to update in LCD*/
            DrivingMonetoring_Current_Status = DM_Meet ;

            if(BrakingAssit_IsStillPressed == NO_Condition)
            {
                BrakingAssit_IsStillPressed = YES_Condition ;
                /* turn buzzer on and give timer 0 clock and set timeout    */
                Buzzer_GiveSound = YES_Condition; 

                if(BrakingAssist_Current_State == BrakingAssist_Disable)
                {
                    BrakingAssist_Current_State = BrakingAssist_Enable ;
                    /*  call function update state of Brake assist*/
                    DashBoard_Update_BrakingAssist_State(BrakingAssist_Current_State);
                }
                else
                {
                    BrakingAssist_Current_State = BrakingAssist_Disable ;
                    /*  call function update state of Brake assist*/
                    DashBoard_Update_BrakingAssist_State(BrakingAssist_Current_State);
                }
                /*  As if I in page braking Assist and Enable or disable  need to update*/
                if(Page_Current_State == Page_1_LCD)
                {
                    DashBoard_SwitchPages();    
                }
            }
        }
        else 
        {
            BrakingAssit_IsStillPressed = NO_Condition ;
        }

        /* (Button 10) Handle Driving monetoring Button   */
        if(local_currentValue_keypad == Keypad_DrivingMonetoring_pressed_value)
        {
            if(DrivingMonetoring_IsStillPressed == NO_Condition)
            {
                DrivingMonetoring_IsStillPressed = YES_Condition ;

                /* turn buzzer on and give timer 0 clock and set timeout    */
                Buzzer_GiveSound = YES_Condition; 
                
                if(DrivingMonetoring_Current_State == DirivingMonetoring_Disable)
                {
                    DrivingMonetoring_Current_State = DirivingMonetoring_Enable ;
                    /*  Update in LCD   */
                    DahBoard_Update_DrivingMonetoring_State(DrivingMonetoring_Current_State);

                    /*  Make counter start from zero Again  */
                    // TimeOut_Counter = 0 ;//old one when I use timer1
                    Timer0_Overflow_counter_DM = 0 ;

                    /*  intialize that will meeting state at first  */
                    DrivingMonetoring_Current_Status = DM_Meet ;
                }  
                else
                {
                    DrivingMonetoring_Current_State = DirivingMonetoring_Disable ;
                    /*  Update in LCD */
                    DahBoard_Update_DrivingMonetoring_State(DrivingMonetoring_Current_State);
                    

                } 
                
            }
        }
        else
        {
            DrivingMonetoring_IsStillPressed = NO_Condition ;
        }

    }

/* (Button 5️⃣) Handle switch to right screen   */
    /*  ⚠️⚠️⚠️⚠️ I think that is critical section   */
    if(local_currentValue_keypad == Keypad_Page_R_pressed_value)
    {
        /*  Make counter with zero to start count from zero for DM */
        // TimeOut_Counter = 0 ;//old one when I use timer1
        Timer0_Overflow_counter_DM = 0 ;

        /*  Change state to update in LCD*/
        DrivingMonetoring_Current_Status = DM_Meet ;

        if(R_Page_IsStillPressed == NO_Condition)
        {
            R_Page_IsStillPressed = YES_Condition ;
            Page_Current_State++ ; /*   Move one right page*/
            if(Page_Current_State == 4) /*  Exceed page 3 so it need to handle and return to page one  */
            {
                Page_Current_State = Page_1_LCD ;
            }
            /*  Call function that handle change in first two */
            DashBoard_SwitchPages();
            /*  Call function that will handle display in LCD*/
            DashBoardPageFooter_update();

        }
    }
    else 
    {
        /*  Enter this state when Button released*/
        R_Page_IsStillPressed = NO_Condition ;
    }


/* (Button 6️⃣) Handle switch to left screen   */
    /*  ⚠️⚠️⚠️⚠️ I think that is critical section   */
    if(local_currentValue_keypad == Keypad_Page_L_pressed_value)
    {
        /*  Make counter with zero to start count from zero for DM */
        // TimeOut_Counter = 0 ; //old one when I use timer1
        Timer0_Overflow_counter_DM = 0 ;

        /*  Change state to update in LCD*/
        DrivingMonetoring_Current_Status = DM_Meet ;

        if(L_Page_IsStillPressed == NO_Condition)
        {
            L_Page_IsStillPressed = YES_Condition ;
            Page_Current_State-- ; /*   Move one right page*/
            if(Page_Current_State == -1) /*  Exceed page 3 so it need to handle and return to page one  */
            {
                Page_Current_State = Page_4_LCD ;
            }
            /*  Call function that handle change in first two */
            DashBoard_SwitchPages();
            /*  Call function that will handle display in LCD*/
            DashBoardPageFooter_update();

        }
    }
    else 
    {
        /*  Enter this state when Button released*/
        L_Page_IsStillPressed = NO_Condition ;
    }


/* (Button 7️⃣) Handle increase in speed limit   */
    /*  Handle Increasing part for speed limiter    */
    static uint8 SL_FirstTime_INC = YES_Condition ;
    static uint8 SL_INC_repeation = 0 ;
    if(local_currentValue_keypad == Keypad_SpeedLimit_Inc_pressed_value)
    {
        /*  Make counter with zero to start count from zero for DM */
        // TimeOut_Counter = 0 ; //old one when I use timer1
        Timer0_Overflow_counter_DM = 0 ;
        /*  Change state to update in LCD*/
        DrivingMonetoring_Current_Status = DM_Meet ;
        if(SL_FirstTime_INC == YES_Condition )
        {
            if(Global_Speed_Limiter_value < Max_Speed_Limit_value)
            {
                Global_Speed_Limiter_value += 5; 
            }
                SL_FirstTime_INC = NO_Condition ;
        }
        else /* Enter it when SL_FirstTime_INC = NO_Condition   */
        {
            SL_INC_repeation += 1;
            if(SL_INC_repeation == 3)
            {
                SL_INC_repeation = 0;
                /*   Increase Global_Speed_Limiter_value variable by 5  */
                if(Global_Speed_Limiter_value < Max_Speed_Limit_value)
                {
                    Global_Speed_Limiter_value += 5; 
                }
            }
        }
        /*🙆‍♂️🙆‍♂️🙆‍♂️🙆‍♂️*/
        DashBoard_updateSpeedLimitValue();

    }
    else
    {
        SL_FirstTime_INC = YES_Condition ;
        SL_INC_repeation = 0;

    }


/* (Button 8️⃣) Handle decrease in speed limit   */
    /*  Handle Decreasing part for speed limiter    */
    static uint8 SL_FirstTime_DEC = YES_Condition ;
    static uint8 SL_DEC_repeation = 0 ;
    if(local_currentValue_keypad == Keypad_SpeedLimit_Dec_pressed_value)
    {
        /*  Make counter with zero to start count from zero for DM */
        // TimeOut_Counter = 0 ;//old one when I use timer1
        Timer0_Overflow_counter_DM = 0 ;

        /*  Change state to update in LCD*/
        DrivingMonetoring_Current_Status = DM_Meet ;

        if(SL_FirstTime_DEC == YES_Condition )
        {
            if(Global_Speed_Limiter_value > Min_speed_Limit_value)
            {
                Global_Speed_Limiter_value -= 5;    
            }
            SL_FirstTime_DEC = NO_Condition ;
        }
        else /* Enter it when SL_FirstTime_INC = NO_Condition   */
        {
            SL_DEC_repeation += 1;
            if(SL_DEC_repeation == 3)
            {
                SL_DEC_repeation = 0;
                /*   Increase Global_Speed_Limiter_value variable by 5  */
                if(Global_Speed_Limiter_value > Min_speed_Limit_value)
                {
                    Global_Speed_Limiter_value -= 5;    
                }
            }
        }
        /*🙆‍♂️🙆‍♂️🙆‍♂️🙆‍♂️*/
        DashBoard_updateSpeedLimitValue();

    }
    else
    {
        SL_FirstTime_DEC = YES_Condition ;
        SL_DEC_repeation = 0;

    }

}








static void Braking_Button_Handling(void)
{
    /*  Make initial state that Button is released  */
    static uint8 Braking_BTN_State = BTN_Released_State ;
    /*  Will Enter this condition only when press button Only (this will make failling edge)  */
    if(Braking_BTN_State == BTN_Released_State)
    {
        /*  So when I release utton will make Rising Edge so I need to make setup to detect this state to turn led off  */
        INT1_init(RISING_EDGE_TRIGGER,INPUT_PIN); /*    If swap between that command and next command will face problem that If I make very short press will face problem  that led will turn on only not turn off also and this not required*/

        Buzzer_GiveSound = YES_Condition; 

        /*  Make update to state    */
        Braking_BTN_State = BTN_Pressed_State;
        /*  Update global varaible that carry state of car speed    */
        Global_Braking_BTN_State = Braking_BTN_State;
        /*  Turn led on  */
        LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN,LED_ON);
/*                Here when I press in Braking if in D mode should Disable ACCS mode                                                       */
/*
*   I face very big problem as this Button has two scienaros (very short press and normal or long press )
*   In very short press I will face problem if I Enable ACCS as there are if condition will be true and this code will take time for execute (failing edge followed by rising edge ) and code in if condition execution time greater than time of(convert from failling edge to rising edge)
*/
        // if((GearBox_Current_State == D_GearBox) && (ACCS_Currnet_state == ACCS_Enable))
        // {
        //     /*	Enable Global Interrupt  */
	    //     sei();

        //     /*  Disable ACCS if Enabled  */
        //     ACCS_Currnet_state = ACCS_Disable;
        //     /*  Turn off led of it was turned on  */
        //     LED_OnOffPositiveLogic(Green_LED_PORT,Green_LED_PIN,LED_OFF);
        //     /*  Update LCD with new change*/
        //     DashBoard_Update_CCS_State(ACCS_Currnet_state);

        //     DashBoard_DistanceHide();


        // }
        tessst();
    }
    /*  Will Enter this condition only when release button Only (this will make failling edge)  */
    else if(Braking_BTN_State == BTN_Pressed_State)
    {

        INT1_init(FALLING_EDGE_TRIGGER,INPUT_PIN);
        Braking_BTN_State = BTN_Released_State;
        /*  Update global varaible that carry state of car speed    */
        Global_Braking_BTN_State = Braking_BTN_State;
        LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN,LED_OFF);
    }
}


void tessst (void)
{
        if((GearBox_Current_State == D_GearBox))
        {
            /*	Enable Global Interrupt  */
	        sei();
            /*  If it was CCS enabled should disabled and update in LCD*/
            if(CCS_Currnet_state == CCS_Enable)
            {
                /*  Disable ACCS if Enabled  */
                CCS_Currnet_state = CCS_Disable;

                /*  Update LCD with new change*/
                DashBoard_Update_CCS_State(CCS_Currnet_state);
            }

            /*  If it was Braking Assist enabled should disabled and update in LCD*/
            if(BrakingAssist_Current_State == BrakingAssist_Enable)
            {
                /*  Disable BA Sysystem */
                BrakingAssist_Current_State = BrakingAssist_Disable ;

                /*  Update LCD with new change*/
                DashBoard_Update_BrakingAssist_State(BrakingAssist_Current_State);
            }

            // /*  If it was Speed Limiter enabled should disabled and update in LCD*/
            // if(SpeedLimit_Current__State == SpeedLimit_Enable)
            // {
            //     /*  Disable BA Sysystem */
            //     SpeedLimit_Current__State = SpeedLimit_Disable ;
                
            //     /*  Update LCD with new change*/
            //     DashBoard_Update_SpeedLimiter_State(SpeedLimit_Current__State);
            // }

            // DashBoard_DistanceHide();
            //DashBoard_DistanceHide_small();


            /*  Make counter with zero to start count from zero for DM */
            // TimeOut_Counter = 0 ;//old one when I use timer1
            Timer0_Overflow_counter_DM = 0 ;

            /*  Change state to update in LCD*/
            DrivingMonetoring_Current_Status = DM_Meet ;

        }
}


void Braking_LongPressHandle(void)
{
    if(Global_Braking_BTN_State == BTN_Pressed_State)
    {
        /*  ⚠️Here make disable for Cruise control sysytem (CCS) as there bug 
        *   when press in brake system if CCS is enaled will disaled but during  pressing brake if CCS activated again will not handled
        */
        if(CCS_Currnet_state == CCS_Enable)
        {
            /*  Disable ACCS if Enabled  */
            CCS_Currnet_state = CCS_Disable;

            /*  Update LCD with new change*/
            DashBoard_Update_CCS_State(CCS_Currnet_state);
        }

        /*  ⚠️Here when press on brakeing pedal will detected as A press and if DM activated and after 5 second make alarm for no action from driver 
        *   so will give alarm and when press on braking pedal alarm will stop but after another 5 second there another alarm fired although I'm still press on braking padel 
        *   As system can't handle this so Here I handle this bug
        */
        
        /*  Make counter with zero to start count from zero for DM */
        //TimeOut_Counter = 0 ; //old one when I use timer1
        Timer0_Overflow_counter_DM = 0 ;
    }
}




static void DashBoard_updateTime(void)
{
    cli();
    if(Page_Current_State == Page_4_LCD)
    {
        LCD_MoveCursor(1,0);
        LCD_DisplayString("T=");if(Clock_hour < 10)
        {
            LCD_DisplayCharacter(' ');
            LCD_intToString(Clock_hour);
        }
        else
        {
            LCD_intToString(Clock_hour);
        }
        LCD_DisplayCharacter(':');
        if(Clock_min < 10)
        {
            LCD_DisplayCharacter(' ');
            LCD_intToString(Clock_min);
        }
        else
        {
            LCD_intToString(Clock_min);
        }
        LCD_DisplayCharacter(':');
        if(Clock_sec < 10)
        {
            LCD_DisplayCharacter(' ');
            LCD_intToString(Clock_sec);
        }
        else
        {
            LCD_intToString(Clock_sec);
        }
        LCD_DisplayCharacter(' ');
        
    }
    sei();
}

static void ACCS_CatchDistance(void)
{
    /*  ⚠️🙆‍♂️🚩Here I need to disable interrupt as I don't know when I press braking button 
    * as may be before printing point(.) and number after point  press braking button and this lead to call DashBoard_DistanceHide() function
    * and this make cursor position that I make disable  be at last colimn in last row and will return here to continue this code here 
    * so this lead to make data overwrite in LCD 
    * "this is one scenario from a lot of scenarios "
    */
    cli();
    volatile uint16 Adc_value_pure = ADC_ReadChannelSingleConvertion(ADC_Channel_0);
    distance_ACCS = (Adc_value_pure * 10) / 1023.0 ; 
    /*  Here trying to get first number after Sign  */
    volatile uint8 distance_after_point = ( (uint8)(distance_ACCS * 10) )  % 10;
    LCD_MoveCursor(3,11);
    /*  For Small LCD*/
    //LCD_MoveCursor(1,11);
	LCD_intToString((uint8)distance_ACCS);
	LCD_DisplayCharacter('.');
    LCD_intToString(distance_after_point);
    LCD_DisplayString("M ");
    sei();
}



static void ACCS_DicisionTake(void)
{
    if((CCS_Currnet_state == CCS_Enable) && (D_GearBox == GearBox_Current_State))
    {

        cli();
        if((uint8)(distance_ACCS) >= 8) /*  Case 1  */
        {
            
            /*  Do no thing */
            LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_OFF);
            LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN,LED_OFF);

           
        }
        else if(((uint8)(distance_ACCS) >= 6)) /*  Case 2  */
        {
           
            /*  in this case only turn yellow led only */
            LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_ON);
            LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN,LED_OFF);

          

            /*  Try to return back to speed that was make fixed*/
        }
        else if (((uint8)(distance_ACCS) >= 4)) /*  Case 3  */
        {
            

            /*  in this case turn yellow and red led on*/
            LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_ON);

            LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN,LED_ON);

        }
        else if (((uint8)(distance_ACCS) >= 2)) /*  Case 4  */
        {


            /*  turn yellow led on and make red led toggles continuesly with very speed */
            LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_ON);

            LED_Toggle(Red_LED_PORT,Red_LED_PIN);

        }   
        else if (((uint8)(distance_ACCS) >= 0)) /*  Case 5  */
        {
            /*  Turn Of all leds    */
            LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN,LED_OFF);
            LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_OFF);


            /*  Display Crash message   */
            LCD_ClearScreen();
            LCD_DisplayString((const uint8 *)"Crushed car ):");
            

            /*  flash Relay  */

            /*  Disable all Button*/
            while(1);
        }
        
        sei();
    }
}

static void App_CarSpeedUpdate(void)
{
    static volatile uint16 Prev_Adc_value_pure = 0;
    /*  Read current value for Potentiometer that work as Accelerator  */
    volatile uint16 Adc_value_pure = ADC_ReadChannelSingleConvertion(ADC_Channel_0);  
    /*  Get speed that be assigned depend on next condition state  */ 
    Temp_Speed = (uint8)( ( (200) * ((uint32) Adc_value_pure)  ) / 1023 ) ;

    Diff_between_ADCS =  (sint16)Prev_Adc_value_pure - (sint16)Adc_value_pure;

    if((Diff_between_ADCS > 19) || (Diff_between_ADCS < -19)) // by try found that potentiometer in real life its value vary with max change = 15 so I want change greater than 25 in CCR or CR to accept it as human change not noise in potentiometer
    {
        Car_Speed = Temp_Speed ;
        Timer0_Overflow_counter_DM =0 ; // when there are new change in potentiometer (accelemetor) reset time counter for Driving monetering 
        
        /*  Change state to update in LCD*/
        DrivingMonetoring_Current_Status = DM_Meet ;

        if((CCS_Currnet_state == CCS_Enable) && (GearBox_Current_State == D_GearBox))
        {
            /*  As in requirement Cruise control will be Disabled when press in accelerator pedal if I in "D" Gearbox  and CCS was activated */
            CCS_Currnet_state = CCS_Disable ;
            DashBoard_Update_CCS_State(CCS_Currnet_state);
        }
    }
        cli();
        LCD_MoveCursor(1,14);
        /*  call function to handle speed for motor */
        LCD_intToString((uint8)Car_Speed) ;
        LCD_DisplayString("KM ");

        /*  Update Dc motor speed  */
        if(GearBox_Current_State == N_GearBox)
        {
            DC_Motor_Speed(&DC_pins_Motor,DC_Motor_Stop,0);
        }
        else if(GearBox_Current_State == D_GearBox)
        {
            uint8 Speed_0_100 = (Car_Speed * (uint16) 100) / 200 ;
            DC_Motor_Speed(&DC_pins_Motor,DC_Motor_CW,(uint8)Speed_0_100);
        }
        else if(GearBox_Current_State == R_GearBox)
        {
            uint8 Speed_0_100 = (Car_Speed * (uint16) 100) / 200 ;
            DC_Motor_Speed(&DC_pins_Motor,DC_Motor_ACW,(uint8)Speed_0_100);
        }
        
        sei();
    /*  Save last change in Speed variable that will display in LCD  */
    Prev_Adc_value_pure = Adc_value_pure ;

}



/*  👀👀👀👀 Look Here function handle Time overflow    */
static void TImer0_OVF_Handling_Fun(void)
{
    /*  Here handle */
    if( (GearBox_Current_State == D_GearBox) || (GearBox_Current_State == R_GearBox) )
    
    
    Timer0_Overflow_counter_DM++; 
    /*  No need to increment this variable as DM disabled  */
    if(DrivingMonetoring_Current_State == DirivingMonetoring_Disable)
    {
        Timer0_Overflow_counter_DM = 0 ;
    }

    else if(Timer0_Overflow_counter_DM == Timer0_OVF_5_sec_DrivingMonetoring)
    {
        Timer0_Overflow_counter_DM = 0;
        /*  Here happen time out that it may be user is in Sleep  */
        DrivingMonetoring_Current_Status = DM_Failed ;

    }
    
    if(Buzzer_GiveSound == YES_Condition )
    {
        Buzzer_Timer0_OVF_count++;
        Buzzer_OnOffPositiveLogic(Buzzer_PORT,Buzzer_PIN,Buzzer_ON);
        if(Buzzer_Timer0_OVF_count == Timer0_OVF_Buzzer_Notify_sound)
        {
            Buzzer_GiveSound = NO_Condition ;
            Buzzer_OnOffPositiveLogic(Buzzer_PORT,Buzzer_PIN,Buzzer_OFF);
        }
    }
    else if(Buzzer_GiveSound == NO_Condition)
    {
        Buzzer_Timer0_OVF_count = 0;
    }


    Timer0_Overflow_Counter_RTClock++;
    if(Timer0_Overflow_Counter_RTClock == Timer0_OVF_1_sec_RTClock)
    {
        Timer0_Overflow_Counter_RTClock = 0;
        /*  handle update of car moved Kilo meters  */
        /*  Distance = speed * time   -> and speed = KM/H  so distance = (KM/H) * H 
        but as I make Demo I will not wait hour for update so I make update for every second
        so equation will be Distance = Speed * 1sec / 60
        */

       if((GearBox_Current_State == D_GearBox) || (GearBox_Current_State == R_GearBox))
       {
            /*  Must take count when moving in D or R mode*/
            Accumulative_Distance_KM += Car_Speed / 60.0 ; 
       }

        /*  This is part for update real time clock  */
        Clock_sec ++ ;
        if(Clock_sec == 60)
        {
            Clock_sec =  0 ;
            Clock_min ++;
        }
        if(Clock_min == 60)
        {
            Clock_min = 0 ;
            Clock_hour ++;
        }
    }


}


static void APP_CarMovedKiloMeters(void)
{
    if(Page_Current_State == Page_2_LCD)
    {
        cli();
        LCD_MoveCursor(1,4);
        LCD_FloatToString(Accumulative_Distance_KM);
        
        sei();
    }
    else 
    {
        /*  Do Nothing  */
    }
}


/******************************************************************************/





// static void DashBoard_DistanceShow_small(void)
// {
//     LCD_MoveCursor(1,8);
//     LCD_DisplayString((const uint8 * )",D:");
 
// }

// static void DashBoard_DistanceHide_small(void)
// {
//     LCD_MoveCursor(1,8);
//     LCD_DisplayString((const uint8 * )"        ");
// }




// static void DashBoard_DistanceShow(void)
// {
//     LCD_MoveCursor(3,0);
//     LCD_DisplayString((const uint8 * )"Distance : ");
// }


// static void DashBoard_DistanceHide(void)
// {
//     LCD_MoveCursor(3,0);
//     LCD_DisplayString((const uint8 * )"                    ");
// }



// static void Buttons_Update(void)
// {   

//     /*  This variable used to carry if button is still pressed after last pressed as any action taken once with first step and if still press nothing happen    */
//     static uint8 GearBox_IsStillPressed = NO_Condition;
//     /*  Take current state for button  to check if still pressed*/
//     uint8 GearBox_BTN_State = BUTTON_GetValue(GearBox_BTN_PORT,GearBox_BTN_PIN);
    
//     if(GearBox_BTN_State == BTN_Pressed_State)
//     {
//         /*  This condition placed here to take action for button press only when pressed and if still pressed Do nothing    */
//         if(GearBox_IsStillPressed == NO_Condition)
//         {
//             /* turn buzzer on and give timer 0 clock and set timeout    */
//             Buzzer_NotifySound();

//             GearBox_IsStillPressed = YES_Condition ;
//             /*  Go to next state for gearbox*/
//             GearBox_Current_State ++ ;
//             if(GearBox_Current_State == GearBox_Return_to_N  )
//             {
//                 GearBox_Current_State = N_GearBox ;
                
//             }

//             /*  call function to update gearbox state in Dashboard*/
//             DashBoard_Update_GearBox_state(GearBox_Current_State);
//             /*  Initailize for small LCD*/
//             //DashBoard_Update_GearBox_state_small(GearBox_Current_State);
//         }
        
//     }
//     else
//     {
//         /*  Enter this state when Button released*/
//         GearBox_IsStillPressed = NO_Condition ;
//     }
  

    // if(GearBox_Current_State == D_GearBox)
    // {
    //     /*  This variable used to carry if button is still pressed after last pressed as any action taken once with first step and if still press nothing happen    */
    //     static uint8 ACCS_IsStillPressed = NO_Condition;
    //     /*  Take current state for button  to check if still pressed*/
    //     uint8 ACCS_BTN_State = BUTTON_GetValue(ACCS_BTN_PORT,ACCS_BTN_PIN);
        
    //     if(ACCS_BTN_State == BTN_Pressed_State)
    //     {
    //         /*  This condition placed here to take action for button press only when pressed and if still pressed Do nothing    */
    //         if(ACCS_IsStillPressed == NO_Condition)
    //         {
    //             /* turn buzzer on and give timer 0 clock and set timeout    */
    //             Buzzer_NotifySound();

    //             ACCS_IsStillPressed = YES_Condition ;
                
    //             if(ACCS_Currnet_state == ACCS_Disable ) 
    //             {
                    
    //                 /*  Update ACCS state with new value (Enabled)*/
    //                 ACCS_Currnet_state = ACCS_Enable;
    //                 DashBoard_Update_CCS_State(ACCS_Currnet_state);
    //                 /*  Initailize for small LCD*/
    //                 //DashBoard_Update_CCS_State_small(ACCS_Currnet_state);
    //                 DashBoard_DistanceShow();
    //                 //DashBoard_DistanceShow_small();
    //             }
    //             else
    //             {
    //                 ACCS_Currnet_state = ACCS_Disable;

    //                 /*  Turn off led that work in Adaptive cruise control  as may be  in not safe area and  turn off Adaptive cruise control   */
    //                 //LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_OFF);
    //                 /*  🚩🚩🚩🚩🚩🚩🙆‍♂️🙆‍♂️🙆‍♂️ i think that I need to put diable and enable to interrupt as I may be ACCS enabled and when I disable and press braiking at same time */
    //                 //LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN,LED_OFF);

    //                 DashBoard_Update_CCS_State(ACCS_Currnet_state);
    //                 /*  Initailize for small LCD*/
    //                 //DashBoard_Update_CCS_State_small(ACCS_Currnet_state);

                    
    //                 DashBoard_DistanceHide();
    //                 //DashBoard_DistanceHide_small();
    //             }

 
    //         }
    //     }
    //     else
    //     {
    //         /*  Enter this state when Button released*/
    //         ACCS_IsStillPressed = NO_Condition ;
    //     }
    // }

// }

