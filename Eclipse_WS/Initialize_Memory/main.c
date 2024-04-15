/*
 * main.c
 *
 *  Created on: Feb 29, 2024
 *      Author: moham
 */


#include "HAL/LCD/LCD_interface.h"
#include "HAL/EXT_EEPROM/EXT_EEPROM_interface.h"
#include "MCAL/I2C/I2C_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
#define F_CPU 8000000UL
#include "util/delay.h"

#define EEPROM_LOCATION    0x10



int main()
{
	LCD_init();
	I2C_Init();
	uint8 counter = 0 ;
	/*	Initialize Float number  */
	for(; counter < 4 ; counter++)
	{
		EEPROM_writeByte(EEPROM_LOCATION + counter, 0);
		_delay_ms(50);
	}
	/*	Initialize GearBox  */
	EEPROM_writeByte(EEPROM_LOCATION + counter, 0);
	_delay_ms(50);
	counter++;
	/*	Initialize Speed limit */
	EEPROM_writeByte(EEPROM_LOCATION + counter, 40);
	_delay_ms(50);
	counter++;
	/*	Initilize start page  */
	EEPROM_writeByte(EEPROM_LOCATION + counter, 1);
	
	LCD_DisplayString("Done ");

	while(1)
	{
	


	}

}
