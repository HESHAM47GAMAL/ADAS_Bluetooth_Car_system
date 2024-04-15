 /******************************************************************************
 *
 * Module: I2C
 *
 * File Name: I2C_program.c
 *
 * Description: contain Implementation of I2C Driver 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "I2C_private.h"
#include "I2C_interface.h"
#include "I2C_config.h"
#include "../../SERVICE/COMMON_MACROS.h"
#include "../../SERVICE/IVT.h"



/**************************                   Extern Global variable                   **************************/
extern I2C_ConfigType  I2C_ConfigTypeParam ;

/**************************                   Function Implement                   **************************/

void I2C_Init(void)
{
    /*  set preScaler for I2C*/
    TWSR |= (I2C_ConfigTypeParam.I2C_PreScaler_value & 0x03 );
    /*  set Bit Rate  */
    TWBR = I2C_ConfigTypeParam.I2C_BitRate ;
    /*  Set Slave Address  */
    TWAR |= ( (I2C_ConfigTypeParam.I2C_SlaveAddress & 0x7F)  << TWA0 );
    /* Enable I2C  */
    SET_BIT(TWCR,TWEN);
 
}


void I2C_Start(void)
{
    /*  Set start Bit in I2C  & flag bit  to clear it  */
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

    /*  Wait until this flag  become  High value (start bit send successfully)*/
    while(BIT_IS_CLEAR(TWCR,TWINT));
}


void I2C_Stop(void)
{
    /*  Set bit of stop & clear I2C Flag*/
    TWCR |= (1 << TWINT) | (1 << TWSTO) | (1<<TWEN) ;
}


void I2C_WriteByte(uint8 data)
{
    /*  Should Load I2C Data register before Clear flag*/
    TWDR = data ;
    /*  Set flag bit  to clear it */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /*  Wait until this flag  become  High value (AS Slave address + W/R OR date was are sendded successfully)*/
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 I2C_ReadByteWithACK(void)
{
    /*  Return ACk @end of data or this address called  & clear flag  */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /*  Wait until data received*/
    while(BIT_IS_CLEAR(TWCR,TWINT));
    return TWDR;
}

uint8 I2C_ReadByteWithNACK(void)
{
    /*  clear flag  */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /*  Wait until data received*/
    while(BIT_IS_CLEAR(TWCR,TWINT));
    return TWDR;
}

uint8 TWI_getStatus(void)
{
    return (TWSR & 0xF8);
}


void I2C_EnableGeneralCallRecognition(void)
{
    SET_BIT(TWAR,TWGCE);
}

void I2C_DisableGeneralCallRecognition(void)
{
    CLEAR_BIT(TWAR,TWGCE);
}