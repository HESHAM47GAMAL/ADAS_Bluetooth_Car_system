 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD_private.h
 *
 * Description: Header file as have function Prototype as can't called by user
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"

/**************************                   Macros Definition                   **************************/

#define LCD_CLEAR_DISPLAY                           0x01
#define LCD_RETURN_TO_HOME_IN_SCREEN                0x02
#define LCD_DISPLAY_ON_CURSOR_ON_BLINKING_OFF       0x0E
#define LCD_DISPLAY_ON_CURSOR_ON_BLINKING_ON        0x0F
#define LCD_DISPLAY_ON_CURSOR_OFF                   0x0C
#define LCD_DISPLAY_OFF_CURSOR_NO                   0x0A
#define LCD_DISPLAY_OFF_CURSOR_OFF                  0x08
#define LCD_CURSOR_MOVE_RIGHT                       0x14
#define LCD_CURSOR_MOVE_LEFT                        0x10
#define LCD_ENTIRE_DISPLAY_RIGHT                    0x1C
#define LCD_ENTIRE_DISPLAY_LEFT                     0x18
#define LCD_2_LINE_8_BIT_5x8_DOT                    0x38
#define LCD_2_LINE_4_BIT_5x8_DOT                    0x28
#define LCD_SET_CURSOR_LOCATION                     0x80  // related to  DDRAM
#define LCD_CGRAM_LOCATION                          0x40  // related to CGRAM

/**************************                   Function Prototype                   **************************/

/*
*   @brief : this function used to to send Intruction to LCD like mode of operation (write operation to LCD)
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_SendCommand(uint8 Instruction_value);

#endif