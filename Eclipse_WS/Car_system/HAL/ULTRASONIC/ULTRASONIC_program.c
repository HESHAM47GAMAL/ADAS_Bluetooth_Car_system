 /******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ULTRASONIC_program.c
 *
 * Description: source file for implementation
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "ULTRASONIC_config.h"
#include "ULTRASONIC_interface.h"
#include "ULTRASONIC_private.h"

#include "../../MCAL/TIMER1/TIMER1_interface.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#define F_CPU 8000000
#include <util/delay.h>

/**************************                   Function Implementation                   **************************/

uint8 g_edgeDetect = 0; 
uint16 g_TimeOfEcho ;

void Ultrasonic_Init(void)
{
    /*  Init Timer 1 as used in ICP hardware*/
    Timer1_Init();  

    /*  Set First Edge want to Detect  as It is Rising Edge  */
    Timer1_ICU_capture_edge(Timer1_ICU_capture_Rising_edge);

    /*  Provide Clock */
    Timer1_ProvideClock();

    /*  Set Call Back funtion*/
    Timer1_SetCallBack(ULtrasonic_SignalProcessing);

    /*  Set trigger pin direction as output*/
    GPIO_SetPinDirection(Trigger_Port,Trigger_Pin,OUTPUT_PIN);

}


void Ultrasonic_Trigger(void)
{
    GPIO_WritePin(Trigger_Port,Trigger_Pin, LOGIC_HIGH);
    _delay_us(10);
    GPIO_WritePin(Trigger_Port,Trigger_Pin, LOGIC_LOW);
}


float64 Ultrasonic_Distance(void)
{
    /*  Send trigger to generste 8 pulses of 40Khz*/
    Ultrasonic_Trigger();

    /*  wait until catch riging and failing edge for Echo */
    while(g_edgeDetect != 2);

    /*  Make it equal zero to be able to perform same operation*/
    g_edgeDetect = 0 ;

    return ((uint16)g_TimeOfEcho / 58.8);

}


void ULtrasonic_SignalProcessing(void)
{
    g_edgeDetect++ ;
    if(g_edgeDetect == 1)
    {
        /*  Initialize Timer with value Zero*/
        Timer1_UpdateValue(0);
        /*  Convert to detect Failling Edge   */
        Timer1_ICU_capture_edge(Timer1_ICU_capture_Falling_edge);

    }
    else if(g_edgeDetect == 2)
    {
        g_TimeOfEcho = Icu_getInputCaptureValue();

        /*  set detect edge as rising edge for next tring to get time of echo*/
        Timer1_ICU_capture_edge(Timer1_ICU_capture_Rising_edge);
    }
}