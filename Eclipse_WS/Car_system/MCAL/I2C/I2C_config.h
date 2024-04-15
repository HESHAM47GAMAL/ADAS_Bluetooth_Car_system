 /******************************************************************************
 *
 * Module: I2C
 *
 * File Name: I2C_config.h
 *
 * Description: Header to configure I2C
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


#define Enable_Interrupt_I2C                1        //  Option 1 -----------|
#define Disable_Interrupt_I2C               0        //  Option 2 -----------|
//                                                                             |
#define INTERUPT_STATE_I2C          Disable_Interrupt_I2C    //<------------|


typedef enum 
{
    I2C_PS_1 , 
    I2C_PS_4 ,
    I2C_PS_16 ,
    I2C_PS_64
}I2C_PreScaler ;


typedef struct 
{
    I2C_PreScaler I2C_PreScaler_value ;
    uint8 I2C_BitRate ;
    uint8 I2C_SlaveAddress ;
}I2C_ConfigType ;




#endif