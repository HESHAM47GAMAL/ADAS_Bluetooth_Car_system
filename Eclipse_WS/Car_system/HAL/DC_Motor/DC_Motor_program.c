 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: DC_Motor_program.c
 *
 * Description: contain Implementation of DC motor Driver 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/

#include "DC_Motor_config.h"
#include "DC_Motor_interface.h"
#include "../../MCAL/GPIO/GPIO_interface.h"

/**************************                   Impelementation                   **************************/

void DC_Motor_Init(DC_Pin_Type *DC_Pin_Value)
{
    /*  Set direction as output for first pin of control direction for Motor*/
    GPIO_SetPinDirection(DC_Pin_Value->DC_EN1_PORT , DC_Pin_Value->DC_EN1_PIN , OUTPUT_PIN);

    /*  Set direction as output for first pin of control direction for Motor*/
    GPIO_SetPinDirection(DC_Pin_Value->DC_EN2_PORT , DC_Pin_Value->DC_EN2_PIN , OUTPUT_PIN);

    /*  Set motor @ first stopped   */
    GPIO_WritePin(DC_Pin_Value->DC_EN1_PORT , DC_Pin_Value->DC_EN1_PIN ,LOGIC_LOW);
    GPIO_WritePin(DC_Pin_Value->DC_EN2_PORT , DC_Pin_Value->DC_EN2_PIN ,LOGIC_LOW);

    /*  Init used Timer     */
    #if(current_Timer_Source_Used == TImer0_Source)
        Timer0_Init();
    #elif(current_Timer_Source_Used == TImer1_Source)
        Timer1_Init();
    #elif(current_Timer_Source_Used == TImer2_Source)

    #endif

}

void DC_Motor_Speed(DC_Pin_Type *DC_Pin_Value , DC_movementState_Type DC_movementState_value , uint8 speed)
{
    switch (DC_movementState_value)
    {
        case DC_Motor_CW :
            GPIO_WritePin(DC_Pin_Value->DC_EN1_PORT , DC_Pin_Value->DC_EN1_PIN ,LOGIC_LOW);
            GPIO_WritePin(DC_Pin_Value->DC_EN2_PORT , DC_Pin_Value->DC_EN2_PIN ,LOGIC_HIGH); 
        break ;

        case DC_Motor_ACW :
            GPIO_WritePin(DC_Pin_Value->DC_EN1_PORT , DC_Pin_Value->DC_EN1_PIN ,LOGIC_HIGH);
            GPIO_WritePin(DC_Pin_Value->DC_EN2_PORT , DC_Pin_Value->DC_EN2_PIN ,LOGIC_LOW); 
        break ;

        case DC_Motor_Stop :
            GPIO_WritePin(DC_Pin_Value->DC_EN1_PORT , DC_Pin_Value->DC_EN1_PIN ,LOGIC_LOW);
            GPIO_WritePin(DC_Pin_Value->DC_EN2_PORT , DC_Pin_Value->DC_EN2_PIN ,LOGIC_LOW); 
        break ;
    }

    /*  Set pin value of PWM*/
    #if(current_Timer_Source_Used == TImer0_Source)
        #if(TIMER0_CURRENT_MODE == T0_FAST_PWM_MODE)
            if(speed >=100) 
                speed = 99 ;
            else if(speed <= 0)
                speed = 1;
            Timer0_FastPWMSetDutyCycle(speed);

        #elif (TIMER0_CURRENT_MODE == T0_PHASE_CORRECT_PWM_MODE)
            if(speed >=100) 
                speed = 99 ;
            else if(speed <= 0)
                speed = 1;
            Timer0_PhaseCorrectPWMSetDutyCycle(speed);
        #endif
    
    #elif(current_Timer_Source_Used == TImer1_Source)


    #elif(current_Timer_Source_Used == TImer2_Source)


    #endif

}
