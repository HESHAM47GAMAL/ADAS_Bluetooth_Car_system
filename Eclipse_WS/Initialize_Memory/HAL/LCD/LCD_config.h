 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD_config.h
 *
 * Description: Header to configure connection of LCD and pins 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


/**************************                   INCLUDES                   **************************/
#include "../../MCAL/GPIO/GPIO_interface.h"


/**************************                   Defination                   **************************/
/*  Configure Max number of Columns Availale for LCD  */
#define MAX_NUM_COL_LCD         20

/*  Configure Max number of Rows Availale for LCD  */
#define MAX_NUM_ROW_LCD         4

/*  Select RS pin in LCD to which pin in port will connect    */
#define LCD_RS_PORT_ID              PORTA_ID 
#define LCD_RS_PIN_ID               PIN3_ID

/*  select RW pin in LCD to which pin in port will connect  */
#define LCD_RW_PORT_ID              PORTA_ID
#define LCD_RW_PIN_ID               PIN1_ID

/*  select E pin in LCD to which pin in port will connect  */
#define LCD_E_PORT_ID               PORTA_ID
#define LCD_E_PIN_ID                PIN2_ID

/*  SELECT PORT that data will transfer through*/
#define LCD_DATA_PORT               PORTB_ID


/*  Select how many bit will used to transfer data  */
#define LCD_8_BIT_MODE              0       //      option1         ---
#define LCD_4_BIT_MODE              1       //      option2         ---        
//                                                                     | Here    
#define LCD_BITS_MODE               LCD_4_BIT_MODE      //          <--

#if( (LCD_BITS_MODE != LCD_4_BIT_MODE) && (LCD_BITS_MODE != LCD_8_BIT_MODE) )
    #error "Number of Data bits should be equal to 4 or 8   Give more attension :("
#endif

/*  will use this part to tell start pin for 4 lines connection*/
#if(LCD_BITS_MODE == LCD_4_BIT_MODE)

    #define Sequencial_PINS             0
    #define NOT_Sequencial_PINS         1

    #define OPTION_PINS             NOT_Sequencial_PINS

    #if(OPTION_PINS  == Sequencial_PINS)
        // Note⛔🙆‍♂️👀 this 4 pins will connected to DB4:7 in LCD
        #define LCD_4_BIT_START_PIN     PIN4_ID
    #elif(OPTION_PINS == NOT_Sequencial_PINS)
        #define PIN_D4      PIN0_ID
        #define PIN_D5      PIN1_ID
        #define PIN_D6      PIN2_ID
        #define PIN_D7      PIN4_ID     
    #endif

#endif


/*  Option of connection of LCD to RW pin */
#define ALWAYS_READ_LCD             0       //HERE will configure this pin to connect
#define READ_WRITE_LCD              1       //Here Won't configure it(if not exist)

#define OPTION_RW_PIN           ALWAYS_READ_LCD


#define CURSOR_OFF              0           //      option1         ---
#define CURSOR_ON_NO_BLINK      1           //      option2         ---
#define CURSOR_ON_BLINK         2           //      option3         ---
//                                                                     | Here   
#define CURSOR_STATE        CURSOR_OFF          //      <-------

#endif