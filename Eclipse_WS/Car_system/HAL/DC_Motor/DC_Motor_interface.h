 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: DC_Motor_interface.h
 *
 * Description: Header contain function prototype to be used 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef DC_MOTOR_INTERFACE_H_
#define DC_MOTOR_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"

#if(current_Timer_Source_Used == TImer0_Source)
    #include "../../MCAL/TIMER0/TIMER0_interface.h"
    #include "../../MCAL/TIMER0/TIMER0_config.h"
#elif(current_Timer_Source_Used == TImer1_Source)
    #include "../../MCAL/TIMER1/TIMER1_interface.h"
    #include "../../MCAL/TIMER0/TIMER1_config.h"
#elif(current_Timer_Source_Used == TImer2_Source)
/*  Not completed net🥹🥲 */
#endif


typedef struct 
{
    uint8 DC_EN1_PORT ;
    uint8 DC_EN1_PIN  ;
    uint8 DC_EN2_PORT ;
    uint8 DC_EN2_PIN  ;
}DC_Pin_Type;


typedef enum 
{
    DC_Motor_CW , 
    DC_Motor_ACW ,
    DC_Motor_Stop
}DC_movementState_Type;


void DC_Motor_Init(DC_Pin_Type *DC_Pin_Value);

void DC_Motor_Speed(DC_Pin_Type *DC_Pin_Value , DC_movementState_Type DC_movementState_value , uint8 speed);






#endif