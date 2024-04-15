 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: EXT_EEPROM_program.c
 *
 * Description: contain Implementation of External EEPROM Driver 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/

#include "../../MCAL/I2C/I2C_interface.h"
#include "../../SERVICE/COMMON_MACROS.h"
#include "../../SERVICE/IVT.h"
#include "EXT_EEPROM_interface.h"

uint8 EEPROM_writeByte(uint8 u8addr,uint8 u8data)
{
    /*  Start communication*/
    I2C_Start();

    /*  get state and check it as expected to be start condition state  */
    if(TWI_getStatus() != I2C_Start_Condition)
        return Error_EEPROM;

    /*  send EEPROM Address + write access*/
    I2C_WriteByte(SLA_W_I2C);

    /*  get state and check it as expected to be slave take its address + write operation  */
    if(TWI_getStatus() != I2C_SLA_W_transmitted_ACK)
        return Error_EEPROM;
    
    /*  send word address that I will write data to it*/
    I2C_WriteByte(u8addr);

    /*  get state and check it as expected to data transimited and received ACK  */
    if(TWI_getStatus() != I2C_Date_transmitted_ACK)
        return Error_EEPROM;


    /*  send data that will assigned to this word address */
    I2C_WriteByte(u8data);

    /*  get state and check it as expected to data transimited and received ACK  */
    if(TWI_getStatus() != I2C_Date_transmitted_ACK)
        return Error_EEPROM;

    /*  Send Stop Bit*/
    I2C_Stop();

    return Success_EEPROM;
}



uint8 EEPROM_readByte(uint8 u8addr,uint8 *u8data)
{
    /*  Start communication*/
    I2C_Start();

    /*  get state and check it as expected to be start condition state  */
    if(TWI_getStatus() != I2C_Start_Condition)
        return Error_EEPROM;

    /*  Send Slave Address + W  */
    I2C_WriteByte(SLA_W_I2C);

    /*  Wait until Slave respond  */
    if(TWI_getStatus() != I2C_SLA_W_transmitted_ACK)
        return Error_EEPROM ;

    /*  Write address of word byte i will read from  */
    I2C_WriteByte(u8addr);

    /*  check that data send and received by slave */
    if(TWI_getStatus() != I2C_Date_transmitted_ACK)
        return Error_EEPROM ;   
    
    /*  make repeat start to make slave send data to master  */
    I2C_Start() ;

    /*  check that data send and slave respond to this  */
    if(TWI_getStatus() != I2C_Repeat_Start_condition)
        return Error_EEPROM ;

    /*  Send Slave Address + R*/
    I2C_WriteByte(SLA_R_I2C);

    /*  Check that slave respond with ACK  */
    if(TWI_getStatus() != I2C_SLA_R_transmitted_ACK)
        return Error_EEPROM ;
    
    /*  Master will wait until receive data */
    *u8data = I2C_ReadByteWithNACK();

    /*  check on data received with NACK*/
    if(TWI_getStatus() != I2C_Date_received_NACK)
        return Error_EEPROM ;
    /*  send stop bit  */
    I2C_Stop();

    return Success_EEPROM ;
}


    
    // /*  Make repeat start to send another byte that is data will written to word address*/
    // I2C_Start();

    // /*  get state and check it as expected to ACk for Repeated start   */
    // if(TWI_getStatus() != I2C_Repeat_Start_condition)
    //     return Error_EEPROM;