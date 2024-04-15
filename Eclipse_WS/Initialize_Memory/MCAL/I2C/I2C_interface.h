 /******************************************************************************
 *
 * Module: USART
 *
 * File Name: USART_interface.h
 *
 * Description: Header contain function prototype to be used 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "I2C_config.h"

/**************************                   Definition                   **************************/
#define I2C_Start_Condition                         0x08
#define I2C_Repeat_Start_condition                  0x10
#define I2C_SLA_W_transmitted_ACK                   0x18
#define I2C_SLA_W_transmitted_NACK                  0x20
#define I2C_Date_transmitted_ACK                    0x28 
#define I2C_Date_transmitted_NACK                   0x30                             
#define I2C_SLA_R_transmitted_ACK                   0x40
#define I2C_SLA_R_transmitted_NACK                  0x48
#define I2C_Date_received_ACK                       0x50
#define I2C_Date_received_NACK                      0x58

/**************************                   Function Prototype                   **************************/

void I2C_Init(void);

void I2C_Stasrt(void);

void I2C_Stop(void);

void I2C_WriteByte(uint8 data);

uint8 I2C_ReadByteWithACK(void);

uint8 I2C_ReadByteWithNACK(void);

uint8 TWI_getStatus(void);

void I2C_EnableGeneralCallRecognition(void);

void I2C_DisableGeneralCallRecognition(void);

#endif