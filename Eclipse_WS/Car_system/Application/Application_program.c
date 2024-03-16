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





/**************************                   Type Declaration                    **************************/
enum GearBox_State {N_GearBox,D_GearBox,R_GearBox , GearBox_Return_to_N};
enum ACCS_State {ACCS_Disable,ACCS_Enable};


/**************************                   Global variable                   **************************/

uint8 GearBox_Current_State = N_GearBox; /* Carry current state of GearBox*/
uint8 ACCS_Currnet_state = ACCS_Disable; /* Carry Current dtate of ACCS and Note that it will take in consideration when GearBox_State == D*/
volatile float32 distance_ACCS = 0 ;    /*  Global Variable carry distance between my car and car in front  of me and will take in consideration when GearBox_State == D && ACCS_state == ON   */

/*  Should be signed as If press brake in N mode will decrease -2 and if data type uint8 so when decrease will happen underflow and if value equal Zero at first so will be 254 so program will have bug*/
static sint16 Car_Speed = 0; /*  Global variable carry Speed of Car  */

static volatile uint8 Global_Braking_BTN_State = BTN_Released_State ;

/*  Carry speed that should move with in ACCS system  */
static volatile uint8 Global_ACCS_Speed = 0 ;   

/*  Enable increase speed only when ACCS Enabled  and no danger to increase speed  */
static volatile uint8 Accelerate_Enbaled_ACCS_Safe = YES_Condition ;

/*  Enable inceaseing speed only when distance is safe value    */
static volatile uint8 Accelerate_Enbaled_ACCS_Danger = NO_Condition ;

void App_Init(void)
{
    /*	Enable Global Interrupt  */
	sei();

    /*  Intialize LCD   */
    LCD_init();

    /*  Initialize Buzzer */
    Buzzer_Init(Buzzer_PORT,Buzzer_PIN);

    /* Initialize Button Accelerate & ACCS & GearBox    */
    BUTTON_Init(Accelerate_BTN_PORT,Accelerate_BTN_PIN,INPUT_PIN);
    BUTTON_Init(ACCS_BTN_PORT,ACCS_BTN_PIN,INPUT_PIN);
    BUTTON_Init(GearBox_BTN_PORT,GearBox_BTN_PIN,INPUT_PIN);

    /*  Initialize Braking Button with EXT_INT 1    */
    INT1_init(FALLING_EDGE_TRIGGER,INPUT_PIN);
    /*  Set call back function  */
    INT1_SetCallBack(Braking_Button_Handling);

    /*  Initialize LEDS(BLUE,Red,Green,Yellow) all os them connected positive logic */
    LED_Init(Blue_LED_PORT,BLUE_LED_PIN);
    LED_Init(Red_LED_PORT,Red_LED_PIN);
    LED_Init(Green_LED_PORT,Green_LED_PIN);
    LED_Init(Yellow_LED_PORT,Yellow_LED_PIN);

    /*  Turn Of all of this led  */
    LED_OnOffPositiveLogic(Blue_LED_PORT,BLUE_LED_PIN, LED_OFF);
    LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN, LED_OFF);
    LED_OnOffPositiveLogic(Green_LED_PORT,Green_LED_PIN, LED_OFF);
    LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN, LED_OFF);

    /*  initialize Timer0   */
    Timer0_Init();

    /*  Set callback function that will called when Timeout happen to turn of buzzer and handle anything another    */
    Timer0_SetCallBack(Buzzer_timeOutOff);

    /*  Initialize ADC to be used by Potentiometer to work as RADAR(Ultrasonic)*/
    ADC_Init();

    /*  Intialize Potentiometer */
    POT_Init(ADC_Channel_0);
    
    /*  Intialize Bash Board for Car*/
    //DashBoard_Init();
    /*  Initailize for small LCD*/

    DashBoard_Init_small();
}



void StateMachineUpdate(void)
{
    Hanndle_GrearBox_N_State();
    Hanndle_GrearBox_D_State();
    Hanndle_GrearBox_R_State();
    Buttons_Update();
}


static void Hanndle_GrearBox_D_State(void)
{
    if((ACCS_Currnet_state == ACCS_Enable) && (D_GearBox == GearBox_Current_State))
    {
        ACCS_CatchDistance();
        /*  may be interrupt happen here so inside next function check if brake button pressed and make disable for ACCS    */
        ACCS_DicisionTake();
        
    }
}



static void Hanndle_GrearBox_N_State(void)
{
    if(GearBox_Current_State == N_GearBox)
    {
        if(ACCS_Currnet_state == ACCS_Enable)
        {
            /*  Disable ACCS if Enabled  */
            ACCS_Currnet_state = ACCS_Disable;
            /*  Turn off led of it was turned on  */
            LED_OnOffPositiveLogic(Green_LED_PORT,Green_LED_PIN,LED_OFF);
            /*  Update LCD with new change*/
            //DashBoard_Update_ACCS_State(ACCS_Currnet_state);
            /*  Initailize for small LCD*/
            DashBoard_Update_ACCS_State_small(ACCS_Currnet_state);
            
            //DashBoard_DistanceHide();
            DashBoard_DistanceHide_small();

        }
    }
   
}


static void Hanndle_GrearBox_R_State(void)
{
    if(GearBox_Current_State == R_GearBox)
    {
        /*  Turn off led that work in Adaptive cruise control  as may make switch by gearBox so I need to handle this   */
        LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_OFF);
        if(ACCS_Currnet_state == ACCS_Enable)
        {
            /*  Disable ACCS if Enabled  */
            ACCS_Currnet_state = ACCS_Disable;
            /*  Turn off led of it was turned on  */
            LED_OnOffPositiveLogic(Green_LED_PORT,Green_LED_PIN,LED_OFF);
            /*  Update LCD with new change*/
            //DashBoard_Update_ACCS_State(ACCS_Currnet_state);
            /*  Initailize for small LCD*/
            DashBoard_Update_ACCS_State_small(ACCS_Currnet_state);
            
            //DashBoard_DistanceHide();
            DashBoard_DistanceHide_small();
        }
    }
}



static void Buttons_Update(void)
{   

    /*  This variable used to carry if button is still pressed after last pressed as any action taken once with first step and if still press nothing happen    */
    static uint8 GearBox_IsStillPressed = NO_Condition;
    /*  Take current state for button  to check if still pressed*/
    uint8 GearBox_BTN_State = BUTTON_GetValue(GearBox_BTN_PORT,GearBox_BTN_PIN);
    
    if(GearBox_BTN_State == BTN_Pressed_State)
    {
        /*  This condition placed here to take action for button press only when pressed and if still pressed Do nothing    */
        if(GearBox_IsStillPressed == NO_Condition)
        {
            /* turn buzzer on and give timer 0 clock and set timeout    */
            Buzzer_NotifySound();

            GearBox_IsStillPressed = YES_Condition ;
            /*  Go to next state for gearbox*/
            GearBox_Current_State ++ ;
            if(GearBox_Current_State == GearBox_Return_to_N  )
            {
                GearBox_Current_State = N_GearBox ;
                
            }

            /*  call function to update gearbox state in Dashboard*/
            //DashBoard_Update_GearBox_state(GearBox_Current_State);
            /*  Initailize for small LCD*/
            DashBoard_Update_GearBox_state_small(GearBox_Current_State);
        }
        
    }
    else
    {
        /*  Enter this state when Button released*/
        GearBox_IsStillPressed = NO_Condition ;
    }
  

    if(GearBox_Current_State == D_GearBox)
    {
        /*  This variable used to carry if button is still pressed after last pressed as any action taken once with first step and if still press nothing happen    */
        static uint8 ACCS_IsStillPressed = NO_Condition;
        /*  Take current state for button  to check if still pressed*/
        uint8 ACCS_BTN_State = BUTTON_GetValue(ACCS_BTN_PORT,ACCS_BTN_PIN);
        
        if(ACCS_BTN_State == BTN_Pressed_State)
        {
            /*  This condition placed here to take action for button press only when pressed and if still pressed Do nothing    */
            if(ACCS_IsStillPressed == NO_Condition)
            {
                /* turn buzzer on and give timer 0 clock and set timeout    */
                Buzzer_NotifySound();

                ACCS_IsStillPressed = YES_Condition ;
                /*  change state of led that refer to ACCS*/
                LED_Toggle(Green_LED_PORT,Green_LED_PIN); 
                if(ACCS_Currnet_state == ACCS_Disable ) 
                {
                    /*  Assign speed that you want to make car to keep it  */
                    Global_ACCS_Speed = Car_Speed ;
                    /*  Update ACCS state with new value (Enabled)*/
                    ACCS_Currnet_state = ACCS_Enable;
                    //DashBoard_Update_ACCS_State(ACCS_Currnet_state);
                    /*  Initailize for small LCD*/
                    DashBoard_Update_ACCS_State_small(ACCS_Currnet_state);
                    //DashBoard_DistanceShow();
                    DashBoard_DistanceShow_small();
                }
                else
                {
                    ACCS_Currnet_state = ACCS_Disable;

                    /*  Turn off led that work in Adaptive cruise control  as may be  in not safe area and  turn off Adaptive cruise control   */
                    LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_OFF);
                    /*  🚩🚩🚩🚩🚩🚩🙆‍♂️🙆‍♂️🙆‍♂️ i think that I need to put diable and enable to interrupt as I may be ACCS enabled and when I disable and press braiking at same time */
                    LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN,LED_OFF);

                    //DashBoard_Update_ACCS_State(ACCS_Currnet_state);
                    /*  Initailize for small LCD*/
                    DashBoard_Update_ACCS_State_small(ACCS_Currnet_state);

                    
                    //DashBoard_DistanceHide();
                    DashBoard_DistanceHide_small();
                }

 
            }
        }
        else
        {
            /*  Enter this state when Button released*/
            ACCS_IsStillPressed = NO_Condition ;
        }
    }


    /*  This variable used to carry if button is still pressed after last pressed as give buzzer sound only once at the begin of press    */
    static uint8 Acccelerate_IsStillPressed = NO_Condition;
    /*  Take current state for button  to check if still pressed*/
    uint8 Acccelerate_BTN_State = BUTTON_GetValue(Accelerate_BTN_PORT,Accelerate_BTN_PIN);
    
    if(Acccelerate_BTN_State == BTN_Pressed_State)
    {
        LED_OnOffPositiveLogic(Blue_LED_PORT,BLUE_LED_PIN,LED_ON);
        /*  Inrease Speed work only in two state 
        *   Case 1 : when GearBox = D and if ACCS enbaled must be Accelerate_Enbaled_ACCS_Danger variable has No condition and this mean that car isn't in danger distance with front car  OR ACCS closed actaully
        *   Case 2 : when GearBox = R
        */
        if(( (GearBox_Current_State == D_GearBox) && (Accelerate_Enbaled_ACCS_Danger == NO_Condition) )|| (GearBox_Current_State == R_GearBox) )
        {
            /*  If I in ACCS Enable mode this line disable call function PID of ACCS */
            Accelerate_Enbaled_ACCS_Safe == NO_Condition;
            
            /*  Incerease Speed of Car  */
            Car_Speed += 1;
            if(Car_Speed > 100)
                Car_Speed  = 100;
            /*  Display current speed   */
            DashBoard_UpdateSpeed(); 
        }

        /*  the reason of this avoid make sound while accelerate BTN pressed    */
        if(Acccelerate_IsStillPressed == NO_Condition)
        {
            Buzzer_NotifySound();
            Acccelerate_IsStillPressed = YES_Condition ;

            
        }
    }
    else
    {
        Acccelerate_IsStillPressed = NO_Condition;
        LED_OnOffPositiveLogic(Blue_LED_PORT,BLUE_LED_PIN,LED_OFF);
        /*  Enable Again to return apply PID of ACCS if Enabled */
        Accelerate_Enbaled_ACCS_Safe = YES_Condition ;
    }

    /*  Here check if Braking Button is pressed so decrease speed of car*/
    if(Global_Braking_BTN_State ==  BTN_Pressed_State)
    {
        /*  Incerease Speed of Car  */
            Car_Speed -= 2;
            if(Car_Speed < 0)
                Car_Speed  = 0;
            /*  Display current speed   */
            DashBoard_UpdateSpeed(); 
    }

    /*  Here handle what happen when release Acceleration and Braking Button    */
    if( (GearBox_Current_State == D_GearBox ) || (GearBox_Current_State == R_GearBox ) )
    {
        /*  Here handle speed only when ACCS Enabled*/
        if( (GearBox_Current_State == D_GearBox ) && (ACCS_Currnet_state == ACCS_Enable))
        {
            /*  Will here handle alot of things*/

            /*  Until Now update value of speed that changed in ACCS_PID Function  */
            DashBoard_UpdateSpeed();
        }
        /*  Here handle Speed when ACCS Disabled and  Acceleration and Braking Button  Released */
        else if( (Global_Braking_BTN_State ==  BTN_Released_State) && (Acccelerate_BTN_State == BTN_Released_State) && (ACCS_Currnet_state == ACCS_Disable))
        {
            static uint8 repeation = 0 ;
            repeation += 1;
            if(repeation == 10)
            {
                repeation = 0;
                Car_Speed -= 1;
                if(Car_Speed < 0)
                    Car_Speed  = 0;
                /*  Display current speed   */
                DashBoard_UpdateSpeed(); 
            }
        }
    }


}



// static void DashBoard_Init(void)
// {
//     /*  Display GearBox Current state  */
//     LCD_MoveCursor(0,0);
//     LCD_DisplayString((const uint8 * )"GearBox(N,D,R) : N");

//     /*  Display speed */
//     LCD_MoveCursor(1,0);
//     LCD_DisplayString((const uint8 * )"Speed : 0");

//     /*  Display state of Adaptive Cruise control  */
//     LCD_MoveCursor(2,0);
//     LCD_DisplayString((const uint8 * )"ACCS(ON,OFF) : OFF");

// }



// static void DashBoard_Update_GearBox_state(uint8 GearBox_state)
// {
//     /*  Array carry All Characters For GearBox as make display easier using index*/
//     uint8 GearBox_Characyer [] = {'N','D','R'};
//     /*  Go to index that display current GearBox state*/
//     LCD_MoveCursor(0,17);
//     /*  Edit its state with new state given to function*/
//     LCD_DisplayCharacter(GearBox_Characyer[GearBox_state]);
// }

// static void DashBoard_Update_ACCS_State(uint8 ACCS_state)
// {
//     const uint8 * ACCS_String[] = {(const uint8 * )"OFF",(const uint8 * )"ON "};
//     /*  Go to index that display current GearBox state*/
//     LCD_MoveCursor(2,15);
//     /*  Edit its state with new state given to function*/
//     LCD_DisplayString(ACCS_String[ACCS_state]);
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


static void Braking_Button_Handling(void)
{
    /*  Make initial state that Button is released  */
    static uint8 Braking_BTN_State = BTN_Released_State ;
    /*  Will Enter this condition only when press button Only (this will make failling edge)  */
    if(Braking_BTN_State == BTN_Released_State)
    {
        /*  So when I release utton will make Rising Edge so I need to make setup to detect this state to turn led off  */
        INT1_init(RISING_EDGE_TRIGGER,INPUT_PIN); /*    If swap between that command and next command will face problem that If I make very short press will face problem  that led will turn on only not turn off also and this not required*/

        Buzzer_NotifySound();

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
        //     DashBoard_Update_ACCS_State(ACCS_Currnet_state);

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
        if((GearBox_Current_State == D_GearBox) && (ACCS_Currnet_state == ACCS_Enable))
        {
            /*	Enable Global Interrupt  */
	        sei();

            /*  Disable ACCS if Enabled  */
            ACCS_Currnet_state = ACCS_Disable;

            /*  Turn off led of it was turned on as I exit from ACC System  */
            LED_OnOffPositiveLogic(Green_LED_PORT,Green_LED_PIN,LED_OFF);
            /*  Then turn off yellow as may be close to crash   */
            LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_OFF);
        


            /*  Update LCD with new change*/
            //DashBoard_Update_ACCS_State(ACCS_Currnet_state);
            /*  Initailize for small LCD*/
            DashBoard_Update_ACCS_State_small(ACCS_Currnet_state);

            //DashBoard_DistanceHide();
            DashBoard_DistanceHide_small();

        }
}


static void Buzzer_NotifySound(void)
{
    /*  initialize Timer register with zero value   */
    Timer0_UpdateValue(0);
    /*  Turn Buzzer on  */
    Buzzer_OnOffPositiveLogic(Buzzer_PORT,Buzzer_PIN,Buzzer_ON);
    /*  Timer provide clock  */
    Timer0_ProvideClock();

    /*  There are another function after timeout will turn buzzer off and stop clock for timer register  */

}


void Buzzer_timeOutOff(void)
{
    Buzzer_OnOffPositiveLogic(Buzzer_PORT,Buzzer_PIN,Buzzer_OFF);
    Timer0_StopClock();
}





static void ACCS_CatchDistance(void)
{
    /*  ⚠️🙆‍♂️🚩Here I need to disable interrupt as I don't know when I press braking button 
    * as may be before printing point(.) and number after point  press braking button and this lead to call DashBoard_DistanceHide() function
    * and this make cursor position that I make disable  be at last colimn in last row and will return here to continue this code here 
    * so this lead to make data overwrite in LCD 
    * "this is one scenario from a lot of scenarios "
    */
    //cli();
    volatile uint16 Adc_value_pure = ADC_ReadChannelSingleConvertion(ADC_Channel_0);
    distance_ACCS = (Adc_value_pure * 10) / 1023.0 ; 
    /*  Here trying to get first number after Sign  */
    volatile uint8 distance_after_point = ( (uint8)(distance_ACCS * 10) )  % 10;
    //LCD_MoveCursor(3,11);
    /*  For Small LCD*/
    LCD_MoveCursor(1,11);
	LCD_intToString((uint8)distance_ACCS);
	LCD_DisplayCharacter('.');
    LCD_intToString(distance_after_point);
    LCD_DisplayString("M ");
    //sei();
}



static void ACCS_DicisionTake(void)
{
    if((ACCS_Currnet_state == ACCS_Enable) && (D_GearBox == GearBox_Current_State))
    {

        cli();
        if((uint8)(distance_ACCS) >= 8) /*  Case 1  */
        {
            if(Accelerate_Enbaled_ACCS_Safe == YES_Condition)
            {
                /*  If speed decreased by I enter in this funxtion Case 3 or 4  so this function try to return to speed that must move with that assigned by ACCS   */
                ACCS_PID(ACCS_Keep_Speed);
            }
            /*  Do no thing */
            LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_OFF);
            LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN,LED_OFF);

            /*  Enable Accelerator*/
            Accelerate_Enbaled_ACCS_Danger = NO_Condition ;
        }
        else if(((uint8)(distance_ACCS) >= 6)) /*  Case 2  */
        {
            if(Accelerate_Enbaled_ACCS_Safe == YES_Condition)
            {
                /*  If speed decreased by I enter in this funxtion Case 3 or 4  so this function try to return to speed that must move with that assigned by ACCS   */
                ACCS_PID(ACCS_Keep_Speed);
            }
            /*  in this case only turn yellow led only */
            LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_ON);
            LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN,LED_OFF);

            /*  Enable Accelerator*/
            Accelerate_Enbaled_ACCS_Danger = NO_Condition ;

            /*  Try to return back to speed that was make fixed*/
        }
        else if (((uint8)(distance_ACCS) >= 4)) /*  Case 3  */
        {
            /*  Here car in danger case that is about to crash so shoud reduce speed   */
            ACCS_PID(ACCS_Decrease_Speed_2);

            /*  in this case turn yellow and red led on*/
            LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_ON);

            LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN,LED_ON);
            /*  Disacle Accelerator*/
            Accelerate_Enbaled_ACCS_Danger = YES_Condition ;
        }
        else if (((uint8)(distance_ACCS) >= 2)) /*  Case 4  */
        {
            /*  Here car in danger case that is about to crash so shoud reduce speed   */
            ACCS_PID(ACCS_Decrease_Speed_4);

            /*  turn yellow led on and make red led toggles continuesly with very speed */
            LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_ON);

            LED_Toggle(Red_LED_PORT,Red_LED_PIN);
            /*  Disacle Accelerator*/
            Accelerate_Enbaled_ACCS_Danger = YES_Condition ;
        }   
        else if (((uint8)(distance_ACCS) >= 0)) /*  Case 5  */
        {
            /*  Turn Of all leds    */
            LED_OnOffPositiveLogic(Red_LED_PORT,Red_LED_PIN,LED_OFF);
            LED_OnOffPositiveLogic(Yellow_LED_PORT,Yellow_LED_PIN,LED_OFF);
            LED_OnOffPositiveLogic(Blue_LED_PORT,BLUE_LED_PIN,LED_OFF);
            LED_OnOffPositiveLogic(Green_LED_PORT,Green_LED_PIN,LED_OFF);

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



static void ACCS_PID(uint8 braking_value)
{
    if (braking_value == ACCS_Keep_Speed)
    {
        /*  Here carry difference between actual velocity and speed must keep in ACCS_speed     */
        sint16 diff_bet_Actual_ACCS = Global_ACCS_Speed - Car_Speed;
    //                 |
    //                 |
    //      ------------------------------------
    //      |                                   |
    // negative number                   Positive number
// ACCS_velocity - actual_speed             ACCS_velocity - actual_speed         
//  = 30 - 31 = -1                         30    - 10 = 20 
        if(diff_bet_Actual_ACCS <= 0)
        {
            Car_Speed = Global_ACCS_Speed ;
        }
        else if(diff_bet_Actual_ACCS > 0)
        {
            Car_Speed += 1;
        }
    }
    else if(braking_value == ACCS_Decrease_Speed_2)
    {
        Car_Speed -= 2;
        if(Car_Speed < 0 )
            Car_Speed = 0; 
    }
    else if(braking_value == ACCS_Decrease_Speed_4)
    {
        Car_Speed -= 4;
        if(Car_Speed < 0 )
            Car_Speed = 0; 
    }
}


/******************************************************************************/

static void DashBoard_Init_small(void)
{
    /*  Display GearBox Current state  */
    LCD_MoveCursor(0,0);
    LCD_DisplayString((const uint8 * )"GearBox:N");

    /*  Display speed */
    LCD_MoveCursor(0,9);
    LCD_DisplayString((const uint8 * )",S:0");

    /*  Display state of Adaptive Cruise control  */
    LCD_MoveCursor(1,0);
    LCD_DisplayString((const uint8 * )"ACCS:OFF");    
}

static void DashBoard_Update_GearBox_state_small(uint8 GearBox_state)
{
    /*  Array carry All Characters For GearBox as make display easier using index*/
    uint8 GearBox_Characyer [] = {'N','D','R'};
    /*  Go to index that display current GearBox state*/
    LCD_MoveCursor(0,8);
    /*  Edit its state with new state given to function*/
    LCD_DisplayCharacter(GearBox_Characyer[GearBox_state]);    
}

static void DashBoard_Update_ACCS_State_small(uint8 ACCS_state)
{
    const uint8 * ACCS_String[] = {(const uint8 * )"OFF",(const uint8 * )"ON "};
    /*  Go to index that display current GearBox state*/
    LCD_MoveCursor(1,5);
    /*  Edit its state with new state given to function*/
    LCD_DisplayString(ACCS_String[ACCS_state]);
}

static void DashBoard_DistanceShow_small(void)
{
    LCD_MoveCursor(1,8);
    LCD_DisplayString((const uint8 * )",D:");
 
}

static void DashBoard_DistanceHide_small(void)
{
    LCD_MoveCursor(1,8);
    LCD_DisplayString((const uint8 * )"        ");
}

static void DashBoard_UpdateSpeed(void)
{
    cli();
    /*  Display speed */
    LCD_MoveCursor(0,12);
    LCD_intToString((uint8)Car_Speed);    
    LCD_DisplayCharacter(' ');
    sei();

}