 /******************************************************************************
 *
 * Module: Keypad
 *
 * File Name: Keypad_program.c
 *
 * Description: implementation for keypad 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
  
#include "Keypad_config.h"
#include "Keypad_interface.h"

#if(Option_PIN_KEYPAD == KEYPAD_NOTSequencePin)

uint8 sequelizeCOL[KEYPAD_COL_NUM]= {KEYPAD_COL0,KEYPAD_COL1,KEYPAD_COL2,KEYPAD_COL3};
uint8 sequelizeROW[KEYPAD_ROW_NUM]= {KEYPAD_ROW_0,KEYPAD_ROW_1,KEYPAD_ROW_2,KEYPAD_ROW_3};

#endif



/**************************                   Functions Definition                   **************************/

void Keypad_init(void)
{
    #if(Option_PIN_KEYPAD == KEYPAD_SequencePin)
        for(uint8 it = 0 ; it < KEYPAD_ROW_NUM ; it++)  // to setup all rows
        {
            #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)

            GPIO_SetPinDirection(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_ROW_ID + it , INPUT_PIN_PULLUP );

            #elif(KEYPAD_PRESSED_STATE == LOGIC_HIGH)

            GPIO_SetPinDirection(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_ROW_ID + it , INPUT_PIN );  // need external pull down

            #endif
        }
        for(uint8 it = 0 ; it < KEYPAD_COL_NUM ; it++)
        {
            GPIO_SetPinDirection(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + it , OUTPUT_PIN );
            #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)
                GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + it , LOGIC_HIGH ); // set all columns to High
            #elif  (KEYPAD_PRESSED_STATE == LOGIC_HIGH)
                GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + it , LOGIC_LOW ); // set all columns to low
            #endif
        }
    #elif(Option_PIN_KEYPAD == KEYPAD_NOTSequencePin)
        for(uint8 it = 0 ; it < KEYPAD_ROW_NUM ; it++)  // to setup all rows
        {
            #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)

            GPIO_SetPinDirection(KEYPAD_ROW_PORT ,sequelizeROW[it] , INPUT_PIN_PULLUP );
            

            #elif(KEYPAD_PRESSED_STATE == LOGIC_HIGH)
            GPIO_SetPinDirection(KEYPAD_ROW_PORT ,sequelizeROW[it] , INPUT_PIN ); // need external pull down

            #endif
        }
        for(uint8 it = 0 ; it < KEYPAD_COL_NUM ; it++)
        {
            GPIO_SetPinDirection(KEYPAD_COL_PORT , sequelizeCOL[it] , OUTPUT_PIN );
            #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)
                GPIO_WritePin(KEYPAD_COL_PORT , sequelizeCOL[it] , LOGIC_HIGH ); // set all columns to High
            #elif  (KEYPAD_PRESSED_STATE == LOGIC_HIGH)
                GPIO_WritePin(KEYPAD_COL_PORT , sequelizeCOL[it] , LOGIC_LOW );// set all columns to low
            #endif
        }

    #endif
}


sint8 Keypad_GetPressedKey(void)
{
    #if(Option_PIN_KEYPAD == KEYPAD_SequencePin)

    #if(WHAT_DO_WITH_PRESS == RETURN_NUM_ONLY_ONCE_UNTIL_RELEASE)
        /*Set variables for this option*/
        static uint8 pressed_BTN = 200 ;
        static uint8 pressed_BTN_IsReleased = FALSE ;
    #endif
        for(uint8 it = 0 ; it < KEYPAD_COL_NUM ; it++)
        {
            // set  one column with value want to read to loop in rows to read which key from this column pressed
            #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)
                GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + it , LOGIC_HIGH ); // set all columns to High
            #elif  (KEYPAD_PRESSED_STATE == LOGIC_HIGH)
                GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + it , LOGIC_LOW ); // set all columns to low
            #endif
        }
        
        while(1)
        {
            uint8 col , row, pressed_key;
            for(col = 0 ; col < KEYPAD_COL_NUM ; col++)
            {
                // set  one column with value want to read to loop in rows to read which key from this column pressed
                #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)
                    GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + col , LOGIC_LOW ); // set one of columns to low
                #elif  (KEYPAD_PRESSED_STATE == LOGIC_HIGH)
                    GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + col , LOGIC_HIGH ); // set one of columns to high
                #endif

                for(row = 0 ; row < KEYPAD_ROW_NUM ; row++)
                {
                    if(GPIO_ReadPin(PORT_FOR_KEYPAD,KEYPAD_FIRST_PIN_ROW_ID + row) == KEYPAD_PRESSED_STATE)
                    {
                        #if(KEYPAD_COL_NUM == 3)
                            pressed_key = Keypad_4X3_AdjustKeyNumber((row*KEYPAD_COL_NUM)+col+1);
                        #elif (KEYPAD_COL_NUM == 4)
                            pressed_key = Keypad_4X4_AdjustKeyNumber((row*KEYPAD_COL_NUM)+col+1);
                        #endif
                        #if(WAIT_BEFORE_RETURN_PRESSED_KEY ==  WHAT_DO_WITH_PRESS)
                            while(GPIO_ReadPin(PORT_FOR_KEYPAD,KEYPAD_FIRST_PIN_ROW_ID + row) == KEYPAD_PRESSED_STATE); //wait until pressed key released
                        #endif

                    #if(WHAT_DO_WITH_PRESS == RETURN_NUM_ONLY_ONCE_UNTIL_RELEASE)
                            /*Check if the same previous pressed BTN is still pressed */
                        if( (GPIO_ReadPin(PORT_FOR_KEYPAD,KEYPAD_FIRST_PIN_ROW_ID + pressed_BTN) == KEYPAD_PRESSED_STATE) && (pressed_BTN_IsReleased) )
                        {
                            /*Wait until this BTN released */
                            while( GPIO_ReadPin(PORT_FOR_KEYPAD,KEYPAD_FIRST_PIN_ROW_ID + row) == KEYPAD_PRESSED_STATE );
                            pressed_BTN_IsReleased = FALSE;
                            /*and ignore this value*/
                            continue;
                        }

                        pressed_BTN_IsReleased = TRUE;
                        /*store last pressed BTN*/
                        pressed_BTN = row ;
                    #endif
                        return pressed_key ;

                    }         //          |
                }             //          |
                            //          |     I mean this step
                            //          |
                            //          \/
                // retrive change happen to make same thing to next column
                #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)
                    GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + col , LOGIC_HIGH ); // set all columns to High
                #elif  (KEYPAD_PRESSED_STATE == LOGIC_HIGH)
                    GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + col , LOGIC_LOW ); // set all columns to low
                #endif

            }
    #if(WHAT_DO_WITH_PRESS == RETURN_NUM_ONLY_ONCE_UNTIL_RELEASE)
            pressed_BTN_IsReleased = FALSE;
    #endif
        }

    #elif(Option_PIN_KEYPAD == KEYPAD_NOTSequencePin)


        #if(WHAT_DO_WITH_PRESS == RETURN_NUM_ONLY_ONCE_UNTIL_RELEASE)
            /*Set variables for this option*/
            static uint8 pressed_BTN = 200 ;
            static uint8 pressed_BTN_IsReleased = FALSE ;
        #endif
        
            // set  one column with value want to read to loop in rows to read which key from this column pressed
            #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)
                for(uint8 it = 0 ; it < KEYPAD_COL_NUM ; it++)
                {
                    GPIO_WritePin(KEYPAD_COL_PORT , sequelizeCOL[it] , LOGIC_HIGH ); // set all columns to High
                }

            #elif  (KEYPAD_PRESSED_STATE == LOGIC_HIGH)
                for(uint8 it = 0 ; it < KEYPAD_COL_NUM ; it++)
                {
                    GPIO_WritePin(KEYPAD_COL_PORT , sequelizeCOL[it] , LOGIC_LOW ); // set all columns to High
                }
            #endif

            while(1)
            {
                uint8 col , row;
                signed pressed_key = -1 ;
                for(col = 0 ; col < KEYPAD_COL_NUM ; col++)
                {
                    // set  one column with value want to read to loop in rows to read which key from this column pressed
                    #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)
                        GPIO_WritePin(KEYPAD_COL_PORT ,  sequelizeCOL[col] , LOGIC_LOW ); // set one of columns to low
                    #elif  (KEYPAD_PRESSED_STATE == LOGIC_HIGH)
                        GPIO_WritePin(KEYPAD_COL_PORT , sequelizeCOL[col] , LOGIC_HIGH ); // set one of columns to high
                    #endif

                    for(row = 0 ; row < KEYPAD_ROW_NUM ; row++)
                    {
                        if(GPIO_ReadPin(KEYPAD_ROW_PORT,sequelizeROW[row]) == KEYPAD_PRESSED_STATE)
                        {
                            #if(KEYPAD_COL_NUM == 3)
                                pressed_key = Keypad_4X3_AdjustKeyNumber((row*KEYPAD_COL_NUM)+col+1);
                            #elif (KEYPAD_COL_NUM == 4)
                                pressed_key = Keypad_4X4_AdjustKeyNumber((row*KEYPAD_COL_NUM)+col+1);
                            #endif
                            #if(WAIT_BEFORE_RETURN_PRESSED_KEY ==  WHAT_DO_WITH_PRESS)
                                while(GPIO_ReadPin(KEYPAD_ROW_PORT,sequelizeROW[row]) == KEYPAD_PRESSED_STATE); //wait until pressed key released
                            #endif

                        #if(WHAT_DO_WITH_PRESS == RETURN_NUM_ONLY_ONCE_UNTIL_RELEASE)
                                /*Check if the same previous pressed BTN is still pressed */
                            if( (GPIO_ReadPin(KEYPAD_ROW_PORT,sequelizeROW[pressed_BTN]) == KEYPAD_PRESSED_STATE) && (pressed_BTN_IsReleased) )
                            {
                                /*Wait until this BTN released */
                                while( GPIO_ReadPin(KEYPAD_ROW_PORT,sequelizeROW[row]) == KEYPAD_PRESSED_STATE );
                                pressed_BTN_IsReleased = FALSE;
                                /*and ignore this value*/
                                continue;
                            }

                            pressed_BTN_IsReleased = TRUE;
                            /*store last pressed BTN*/
                            pressed_BTN = row ;
                        #endif
                            return pressed_key ;

                        }         //          |
                    }             //          |
                                //          |     I mean this step
                                //          |
                                //          \/
                    // retrive change happen to make same thing to next column
                    #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)
                        GPIO_WritePin(KEYPAD_COL_PORT , sequelizeCOL [col] , LOGIC_HIGH ); // set all columns to High
                    #elif  (KEYPAD_PRESSED_STATE == LOGIC_HIGH)
                        GPIO_WritePin(KEYPAD_COL_PORT , sequelizeCOL[col] , LOGIC_LOW ); // set all columns to low
                    #endif

                }
                return pressed_key ;

   
            #if(WHAT_DO_WITH_PRESS == RETURN_NUM_ONLY_ONCE_UNTIL_RELEASE)
                    pressed_BTN_IsReleased = FALSE;
            #endif
            }
            

    #endif

}



