 /******************************************************************************
 *
 * Module: I2C
 *
 * File Name: I2C_config.c
 *
 * Description: include configuration that will applied
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "I2C_config.h"

I2C_ConfigType I2C_ConfigTypeParam ={
	I2C_PS_1 ,  /*  Choose prescaler  */
	8 ,    /*  Choose Bit Rate */
	0b00000010  /*    Choose Slave Address    */

};
