 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: GPIO_config.h
 *
 * Description: Header to configure pins for all ports
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef GPIO_CONFIG_H_
#define GPIO_CONFIG_H_

/**************************                   INCLUDES                   **************************/
#include "GPIO_interface.h"

/*
0 -> Enable pull up resistor
1 -> Disable pull up resistor
*/

#define Enable_PullUp_resistor      1
#define Disable_PullUp_resistor     0
#define Param_Disable_All_PULLUP_resistor     Enable_PullUp_resistor


/**************************                   Definitions macro                   **************************/
#define Configuration_NUM 				1


// Here write all configuration you want for pins

GPIO_PORT_PIN_config GPIO_configParam [Configuration_NUM] = {

		{PORTD_ID , PINS_ALL , OUTPUT_PORT}, //0



};


#endif
