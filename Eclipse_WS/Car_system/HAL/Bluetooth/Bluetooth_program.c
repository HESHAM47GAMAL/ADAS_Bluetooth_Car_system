 /******************************************************************************
 *
 * Module: Bluetooth
 *
 * File Name: Bluetooth_program.c
 *
 * Description: source file for implementation
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


/**************************                   INCLUDES                   **************************/
#include "Bluetooth_interface.h"
#include "Bluetooth_config.h"
#include "../../MCAL/USART/USART_interface.h"


uint8 UART_Buffer[DEFAULT_BUFFER_SIZE] = {};
volatile uint8 UART_Counter = 0 ;

void UART_Receive_Handler(void)
{   
    UART_Buffer[UART_Counter]  =    USART_Catch_UDR_Value();
    UART_Counter++;
    if(UART_Counter == (DEFAULT_BUFFER_SIZE - 1))
    {
        UART_Counter = 0 ;
    }
}


void Bluetooth_Init(void)
{
    /*  Initialize UART*/
    USART_Init();
    /*  Enable Receive Interrupt    */
    USART_EnableReceiveInerrupt();
    /*  Set call back function  */
    USART_receiveByteAsynchCallBack(UART_Receive_Handler);

}


void Bluetooth_Send(const uint8 * string)
{
    USART_SendStringPolling(string);
}
