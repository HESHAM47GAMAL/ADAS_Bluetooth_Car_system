 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: EXT_EEPROM_interface.h
 *
 * Description: Header contain function prototype to be used 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef EXT_EEPROM_INTERFACE_H_
#define EXT_EEPROM_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "EXT_EEPROM_config.h"


/**************************                   Definition                   **************************/
#define Success_EEPROM      1
#define Error_EEPROM        0

#define SLA_W_I2C    ( (EXT_EEPROM_ADDRESS << 1) + 0b0 )
#define SLA_R_I2C    ( (EXT_EEPROM_ADDRESS << 1) + 0b1 )

/**************************                   Function Prototype                   **************************/
uint8 EEPROM_writeByte(uint8 u8addr,uint8 u8data);
uint8 EEPROM_readByte(uint8 u8addr,uint8 *u8data);


#endif