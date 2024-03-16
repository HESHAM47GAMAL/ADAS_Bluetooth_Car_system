 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD_interface.h
 *
 * Description: Header file conatain necessary definition
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


/**************************                   Macros Definition                   **************************/

/*  Location to access CGRAM */
#define LCD_CGRAM_LOCATION_1               0
#define LCD_CGRAM_LOCATION_2               1
#define LCD_CGRAM_LOCATION_3               2
#define LCD_CGRAM_LOCATION_4               3
#define LCD_CGRAM_LOCATION_5               4
#define LCD_CGRAM_LOCATION_6               5
#define LCD_CGRAM_LOCATION_7               6
#define LCD_CGRAM_LOCATION_8               7


/**************************                   Function Prototype                   **************************/

/*
*   @brief : this function used to initailize LCD  pins like RS , RW , E and Data pins 
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_init(void);



/*
*   @brief : this function used to display charcter on LCD or store Custom character in CGRAM
*   @arg1  char_value : ASCI value for character will displayed OR location from 0:7 to custom character will displayed 
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_DisplayCharacter(uint8 char_value);

/*
*   @brief : this function used to display of charcter
*   @arg1  str_content : pointer to start charcter of array of character
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_DisplayString(const uint8 * str_content);

/*
*   @brief : this function used to change position of cursor or place that any charcter will written to row and col
*   @arg1  row : row position (0,1)
*   @arg2  col : column position (0:15)
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_MoveCursor(uint8 row , uint8 col);

/*
*   @brief : this function used to start displaying string at row and col
*   @arg1  str_content : pointer to start charcter of array of character
*   @arg2  row : row position (0,1)
*   @arg3  col : column position (0:15)
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_DisplayStringRowCol(const uint8 * str_content , uint8 row , uint8 col);

/*
*   @brief : this function used to display integer number as convert this integr to array of character
*   @arg1  data : integer value that will display in LCD
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_intToString(uint32 data);

/*
*   @brief : this function used to clear all character and return to row = 0 and col =0
*   @args  : No arg
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_ClearScreen(void);

/*
*   @brief : this function used to move Cursor right 
*   @more Discription Special case : if cursor @ row = 0 , col =15 after function will be @ row = 1 , col =1
    if cursor @ row =1 , col = 15 after function will be @ row =0 , col =0
    Note ⛔🙆‍♂️ : not handled until now to work with shit entire screen right or left
*   @args  : No arg
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_MoveCursorRight(void);

/*
*   @brief : this function used to move Cursor left 
*   @more Discription Special case : if cursor @ row = 0 , col =0 after function will be @ row = 1 , col =15
    if cursor @ row =1 , col = 0 after function will be @ row =0 , col =15
    Note ⛔🙆‍♂️ : not handled until now to work with shit entire screen right or left
*   @args  : No arg
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_MoveCursorLeft(void);

/*
*   @brief : this function used to move entire displayed in LCD to right 
    Note ⛔🙆‍♂️: not handled to make string displayed if in last col in row 0 to shift and take last character to display in row=1 col=0
*   @args  : No arg
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_ShitEntireDisplayRight(void);

/*
*   @brief : this function used to move entire displayed in LCD to left 
    Note ⛔🙆‍♂️: not handled to make string displayed if in last col in row 0 to shift and take last character to display in row=1 col=0
*   @args  : No arg
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_ShitEntireDisplayLeft(void);

/*
*   @brief : this function used to store custom character in CGRAM as there are 8 location for 8 custom character
*   @arg1  Custom_character: pointer to array of 8 character that represent custom character
*   @arg2 location : location that charcter will stored in (LCD_CGRAM_LOCATION_1 : LCD_CGRAM_LOCATION_8)
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_GenerateCharacterCGRAM(const uint8 * Custom_character , uint8 location);

/*
*   @brief : this function used to display custom character
*   @arg1 location : location that charcter stored in (LCD_CGRAM_LOCATION_1 : LCD_CGRAM_LOCATION_8)
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_DisplayCustomCharacter(uint8 location);

/*
*   @brief : this function used to display custom character
*   @arg1 location : location that charcter stored in (LCD_CGRAM_LOCATION_1 : LCD_CGRAM_LOCATION_8)
*   @arg2 row : row position (0,1)
*   @arg3 col : column position (0:15)
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void LCD_DisplayCustomCharacterRowCol(uint8 location , uint8 row ,uint8 col);




#endif