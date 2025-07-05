//#include <reg51.h>
//#include "delay.h"

//sbit SCL = P3^0;
//sbit SDA = P3^1;

//#include "I2C.h"

//#define EEPROM_ID 0xA0     // EEPROM ID

//#include "EEPROM.h"

void EEPROM_write(unsigned char address, unsigned char Data);     //Writes given Data to the specified address
unsigned char EEPROM_read(unsigned char address);     //Writes given Data to the specified address

void EEPROM_write(unsigned char address, unsigned char Data)
{
	I2C_start();
	I2C_datawrite(EEPROM_ID);   //sending slave address '1010 000-0' (7-bit address + 1-bit R/W ('0'=write, '1'=read))
	I2C_datawrite(address);   //sending register's address/memory location address (8-bits address)
	I2C_datawrite(Data);   //Writing Data (8-bits Data) to slave  NB;Maximum is 8-bit(i.e 255) data per register address
	I2C_stop();
}

unsigned char EEPROM_read(unsigned char address)
{
	unsigned char Data;
	
	I2C_start();
	I2C_datawrite(EEPROM_ID);   //sending slave address '1010 000-0' (7-bit address + 1-bit R/W ('0'=write, '1'=read))
	I2C_datawrite(address);   //sending register's address/memory location address (8-bits address)
	I2C_start();
	I2C_datawrite(EEPROM_ID | 0x01);   //sending slave address '1010 000-1' (7-bit address + 1-bit R/W ('0'=write, '1'=read))
	Data = I2C_dataread();   //Reading Data (8-bits Data) from slave
	I2C_NoAck();
	I2C_stop();
	
	return Data;
}