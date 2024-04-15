 /******************************************************************************
 *
 * Module: USART
 *
 * File Name: USART_program.c
 *
 * Description: contain Implementation of USART Driver 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "USART_private.h"
#include "USART_interface.h"
#include "USART_config.h"
#include "../GPIO/GPIO_interface.h"
#include "../../SERVICE/COMMON_MACROS.h"
#include "../../SERVICE/IVT.h"



/**************************                   Extern Global variable                   **************************/
extern USART_ConfigType  USART_ConfigTypeParam ;

/**************************                   Function Implement                   **************************/


static volatile void (*g_CallBackPtr_Receive_USART)(void) = NULL_PTR;


ISR(USART_RXC)
{
    if(g_CallBackPtr_Receive_USART != NULL_PTR)
    {
        g_CallBackPtr_Receive_USART();
    }
}

void USART_Init(void)
{
        /* configue ability of transmit and recieve  */
    if(USART_ConfigTypeParam.USART_COM_OPTION_value == USART_Transmit_Only)
    {
        SET_BIT(UCSRB,TXEN);
    }
    else if(USART_ConfigTypeParam.USART_COM_OPTION_value == USART_Receive_Only)
    {
        SET_BIT(UCSRB,RXEN);
    }
    else if(USART_ConfigTypeParam.USART_COM_OPTION_value == USART_Transmit_Receive)
    {
        SET_BIT(UCSRB,RXEN);
        SET_BIT(UCSRB,TXEN);
    }
    #if(USART_CURRENT_MODE == USART_Asynchronous_Normal_Speed)
    /*  SEt Asynchronous mode & parity & stop & data setting */
    UCSRC = (1 << URSEL) | (USART_ConfigTypeParam.USART_Parity_value << UPM0) | (USART_ConfigTypeParam.USART_NUM_STOP_Bit_value << USBS) | ((USART_ConfigTypeParam.USART_DATA_Bit_value ) << UCSZ0);
    /*  Set 9 data bit if exist in setting in config.c*/
    UCSRB = (UCSRB & 0xFB) | ((USART_ConfigTypeParam.USART_DATA_Bit_value & 0x04) << UCSZ2) ;

    #elif(USART_CURRENT_MODE == USART_Asynchronous_Double_Speed)
    /*  SEt Asynchronous mode & parity & stop & data setting */
    UCSRC = (1 << URSEL) | (~(1 << UMSEL)) | (USART_ConfigTypeParam.USART_Parity_value << UPM0) | (USART_ConfigTypeParam.USART_NUM_STOP_Bit_value << USBS) | ((USART_ConfigTypeParam.USART_DATA_Bit_value & 0x03) << UCSZ0);
    /*  Set 9 data bit if exist in setting in config.c*/
    UCSRB = (UCSRB & 0xFB) | ((USART_ConfigTypeParam.USART_DATA_Bit_value & 0x04) << UCSZ2) ;
    /*  Activate Double speed of Asynchronous   */
    SET_BIT(UCSRA,U2X);
    #elif(USART_CURRENT_MODE == USART_Synchronous)
    /*  Set pin PB0 (XCK)  direction  */
    if(USART_ConfigTypeParam.USART_XCK_STATE_value == MASTER_clk)
        GPIO_SetPinDirection(PORTB_ID,PIN0_ID,OUTPUT_PIN);
    else if(USART_ConfigTypeParam.USART_XCK_STATE_value == SLAVE_clk)
        GPIO_SetPinDirection(PORTB_ID,PIN0_ID,INPUT_PIN);
    /*  SEt synchronous mode & parity & stop & data setting & clock synchronization Polarity */
    UCSRC = (1 << URSEL) | (1 << UMSEL) | (USART_ConfigTypeParam.USART_Parity_value << UPM0) | (USART_ConfigTypeParam.USART_NUM_STOP_Bit_value << USBS) | ((USART_ConfigTypeParam.USART_DATA_Bit_value & 0x03) << UCSZ0) | (USART_ConfigTypeParam.USART_CLK_Polarity_vlaue << UCPOL);
    /*  Set 9 data bit if exist in setting in config.c*/
    UCSRB = (UCSRB & 0xFB) | ((USART_ConfigTypeParam.USART_DATA_Bit_value & 0x04) << UCSZ2) ;
    #endif

    /*  setting value of UBRR  */
    UBRRH = ((USART_ConfigTypeParam.UBRR_value >> 8));
    UBRRL = (uint8)(USART_ConfigTypeParam.UBRR_value )  ; /* take only low * bits*/


    /*  ⚠️ there are problem in this code  commented */


    // /* configue ability of transmit and recieve  */
    // if(USART_ConfigTypeParam.USART_COM_OPTION_value == USART_Transmit_Only)
    // {
    //     SET_BIT(UCSRB,TXEN);
    // }
    // else if(USART_ConfigTypeParam.USART_COM_OPTION_value == USART_Receive_Only)
    // {
    //     SET_BIT(UCSRB,RXEN);
    // }
    // else if(USART_ConfigTypeParam.USART_COM_OPTION_value == USART_Transmit_Receive)
    // {
    //     SET_BIT(UCSRB,RXEN);
    //     SET_BIT(UCSRB,TXEN);
    // }
    // #if(USART_CURRENT_MODE == USART_Asynchronous_Normal_Speed)
    // /*  SEt Asynchronous mode & parity & stop & data setting */
    // UCSRC = (1 << URSEL) | (~(1 << UMSEL)) | (USART_ConfigTypeParam.USART_Parity_value << UPM0) | (USART_ConfigTypeParam.USART_NUM_STOP_Bit_value << USBS) | ((USART_ConfigTypeParam.USART_DATA_Bit_value & 0x03) << UCSZ0);
    // /*  Set 9 data bit if exist in setting in config.c*/
    // UCSRB = (UCSRB & 0xFB) | ((USART_ConfigTypeParam.USART_DATA_Bit_value & 0x04) << UCSZ2) ;

    // #elif(USART_CURRENT_MODE == USART_Asynchronous_Double_Speed)
    // /*  SEt Asynchronous mode & parity & stop & data setting */
    // UCSRC = (1 << URSEL) | (~(1 << UMSEL)) | (USART_ConfigTypeParam.USART_Parity_value << UPM0) | (USART_ConfigTypeParam.USART_NUM_STOP_Bit_value << USBS) | ((USART_ConfigTypeParam.USART_DATA_Bit_value & 0x03) << UCSZ0);
    // /*  Set 9 data bit if exist in setting in config.c*/
    // UCSRB = (UCSRB & 0xFB) | ((USART_ConfigTypeParam.USART_DATA_Bit_value & 0x04) << UCSZ2) ;
    // /*  Activate Double speed of Asynchronous   */
    // SET_BIT(UCSRA,U2X);
    // #elif(USART_CURRENT_MODE == USART_Synchronous)
    // /*  Set pin PB0 (XCK)  direction  */
    // if(USART_ConfigTypeParam.USART_XCK_STATE_value == MASTER_clk)
    //     GPIO_SetPinDirection(PORTB_ID,PIN0_ID,OUTPUT_PIN);
    // else if(USART_ConfigTypeParam.USART_XCK_STATE_value == SLAVE_clk)
    //     GPIO_SetPinDirection(PORTB_ID,PIN0_ID,INPUT_PIN);
    // /*  SEt synchronous mode & parity & stop & data setting & clock synchronization Polarity */
    // UCSRC = (1 << URSEL) | (1 << UMSEL) | (USART_ConfigTypeParam.USART_Parity_value << UPM0) | (USART_ConfigTypeParam.USART_NUM_STOP_Bit_value << USBS) | ((USART_ConfigTypeParam.USART_DATA_Bit_value & 0x03) << UCSZ0) | (USART_ConfigTypeParam.USART_CLK_Polarity_vlaue << UCPOL);
    // /*  Set 9 data bit if exist in setting in config.c*/
    // UCSRB = (UCSRB & 0xFB) | ((USART_ConfigTypeParam.USART_DATA_Bit_value & 0x04) << UCSZ2) ;
    // #endif

    // /*  setting value of UBRR  */
    // UBRRL = (uint8)(USART_ConfigTypeParam.UBRR_value & 0x00FF)  ; /* take only low * bits*/
    // if(USART_ConfigTypeParam.UBRR_value > 0xFF)
    // {
    //     UBRRH = (~(1 << URSEL)) | ((USART_ConfigTypeParam.UBRR_value >> 8) & 0x0F);
    // }

}


void USART_SendBytePolling(uint16 send_data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
    while(BIT_IS_CLEAR(UCSRA,UDRE));
    /*  Should set value of 9th bit  of data if exist before setting value of UDR*/
    if(send_data & 0x0100)
        SET_BIT(UCSRB,TXB8);
    else
        CLEAR_BIT(UCSRB,TXB8);

    /*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
    UDR = (uint8)(send_data & 0x00FF);
}


uint16 USART_ReceiveBytePolling(void)
{
    uint16 Returned_value = 0;

    /*  Will wait until receive data */
    /*  So you stuck here call this function and there are not MCU send Data for you*/
    while(BIT_IS_CLEAR(UCSRA,RXC));
    /*  Should read 9th bit of data if use 9 bit data before UDR*/
    Returned_value = ( (UCSRB & 0x02) << 7) ;
    Returned_value |= UDR ;
    return Returned_value;
}



void USART_SendStringPolling(const uint8 * send_data)
{
    uint8 it = 0;
    while(send_data[it] != '\0')
    {
        USART_SendBytePolling(send_data[it]);
        it++;
    }
}


void USART_ReceiveStringPolling(uint8 * receive_data)
{
    uint8 it =0 ;
    receive_data[it] = (uint8)USART_ReceiveBytePolling();
    while(receive_data[it] != '#')
    {
        it++;
        receive_data[it] = (uint8)USART_ReceiveBytePolling();
    }
    receive_data[it] = '\0';
}



void USART_EnableReceiveInerrupt(void)
{
    SET_BIT(UCSRB,RXCIE);
}



void USART_receiveByteAsynchCallBack(void(*a_ptr)(void))
{

    g_CallBackPtr_Receive_USART = a_ptr;
}

void USART_receiveStringAsynchCallBack(void(*a_ptr)(void))
{

    g_CallBackPtr_Receive_USART = a_ptr;
}




uint16 USART_Catch_UDR_Value(void)
{
    uint16 Returned_value = 0;
    /*  Should read 9th bit of data if use 9 bit data before UDR*/
    Returned_value = ( (UCSRB & 0x02) << 7) ;
    Returned_value |= UDR ;
    return Returned_value;
}