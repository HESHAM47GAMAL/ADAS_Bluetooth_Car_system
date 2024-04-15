 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: GPIO_interface.h
 *
 * Description: Header contain function prototype to be used 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

// gard file
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


/**************************                   Definitions macro                   **************************/
#define NUM_PORT     				4
#define NUM_FOR_PINS_PER_PORT       8



#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7
#define PINS_ALL               8

#define ZEROS_WORD 0x00
#define ONES_WORD  0xFF


#define PUD     2  //bit in register SFIOR responsible for control all internal pullup resistor 


/**************************                   Type Declaration                   **************************/

typedef enum
{
	INPUT_PIN,
	INPUT_PIN_PULLUP,//case to activate internal pull up register for pin
	OUTPUT_PIN
}GPIO_PinDirectionTypes;

typedef enum
{
	INPUT_PORT =0,
	INPUT_PORT_PULLUP =1,//case to activate internal pull up register for port
	OUTPUT_PORT = 0xFF
}GPIO_PortDirectionTypes;


typedef  struct 
{
    uint8 PORT_Selected ; //write wanted port 
    uint8 PIN_SELECT ; // select any pin from 8 pins (PIN0_ID , PIN1_ID , .....) or write PINS_ALL --> to mean that this setting will be for all port
    uint8 INPUT_OUTPUT;
    //     |
    //     |
    // ---- ---------------------------------
    // |                                       |
    // \/                                      |
    // PINS_ALL                              PIN0_ID  , PIN1_ID , PIN2_ID ,.....
    // |                                                           |
    // |use                                                        |use   
    // |                                                           |
    // \/                                                          \/            
    // GPIO_PortDirectionTypes                                GPIO_PinDirectionTypes

}GPIO_PORT_PIN_config;




/**************************                   Function Declaration                   **************************/

/*
*   @brief : this function used to initailize Pins or Ports for GPIO at first using GPIO_config.h as contain pins configuration (used once @first)
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void GPIO_init(void);

/*
*   @brief : this function used to initailize pins for GPIO that will used by another Modules
*   @arg1  PORTX: Port number
*   @arg2  PIN: Pin number
*   @arg3  PinDirction: Pin direction
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void GPIO_SetPinDirection(uint8 PORTX , uint8 PIN ,GPIO_PinDirectionTypes PinDirction );

/*
*   @brief : this function used to read value of pin from port
*   @arg1  PORTX:Port want to read value from depend on pin
*   @arg2  PIN: pin that will read its value
*   @return: return pin value (0,1)
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
uint8 GPIO_ReadPin(uint8 PORTX , uint8 PIN );

/*
*   @brief : this function used to write value for pin from port
*   @arg1  PORTX:Port want to write value from depend on pin
*   @arg2  PIN: pin that will Written
*   @arg3 value : value that will assigned to pin (0,1)
*   @return: no return 
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void GPIO_WritePin(uint8 PORTX , uint8 PIN ,uint8 value);

/*
*   @brief : this function used to Toggle value for pin from port
*   @arg1  PORTX:Port want to write value from depend on pin
*   @arg2  PIN: pin that will Toggle
*   @return: no return 
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void GPIO_TogglePin(uint8 PORTX , uint8 PIN );

/*
*   @brief : this function used to initailize Port for GPIO that will used by another Modules
*   @arg1  PORTX: Port number
*   @arg2  PortDirection:  port direction
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void GPIO_SetPortDirection(uint8 PORTX , GPIO_PortDirectionTypes PortDirection);

/*
*   @brief : this function used to read port 
*   @arg1  PORTX:Port want to read its value
*   @return: return  value (0:255)
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
uint8 GPIO_ReadPort(uint8 PORTX);

/*
*   @brief : this function used to write value for port
*   @arg1  PORTX:Port want to write value for it
*   @arg2 value : value that will assigned to port (0:255)
*   @return: no return 
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void GPIO_WritePort(uint8 PORTX  ,uint8 value);

/*
*   @brief : this function used to Toggle value for port
*   @arg1  PORTX:Port want to toggle value for it
*   @return: no return 
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void GPIO_TogglePort(uint8 PORTX);



#endif
