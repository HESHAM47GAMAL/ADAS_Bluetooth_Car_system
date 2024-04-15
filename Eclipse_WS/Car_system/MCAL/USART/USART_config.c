 /******************************************************************************
 *
 * Module: USART
 *
 * File Name: USART_config.c
 *
 * Description: include configuration that will applied
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "USART_config.h"



#if ((USART_CURRENT_MODE == USART_Asynchronous_Normal_Speed) || (USART_CURRENT_MODE == USART_Asynchronous_Double_Speed))

USART_ConfigType USART_ConfigTypeParam ={
    USART_8_bit ,   /*  set number of data bit in frame*/
    USART_No_Parity ,     /*  Set type of parity used*/
    USART_1_STOP ,      /*  set number of stop bit*/
    USART_Transmit_Receive , 
    BUADRATE_9600_8HZ_UX20   /* Set UBRR value Here*/
};

#elif(USART_CURRENT_MODE == USART_Synchronous)
USART_ConfigType USART_ConfigTypeParam ={
    USART_8_bit ,   /*  set number of data bit in frame*/
    USART_No_Parity ,     /*  Set type of parity used*/
    USART_1_STOP ,      /*  set number of stop bit*/
    USART_Transmit_Receive , 
    USART_TX_RISING_RX_FALLING ,
    MASTER_clk,
    415   /* Set UBRR value Here*/
};

#endif


