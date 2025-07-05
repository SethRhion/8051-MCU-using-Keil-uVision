#include <reg51.h>
#include "delay.h"

unsigned int lcd_port=2;      //Specify Port used for rs,en,datapins as global variable
sbit en = P1^1;
sbit rs = P1^0;     //Specify rs and en pins as global variable

#include "LCD.h"

sbit SCL = P3^0;
sbit SDA = P3^1;

#include "I2C.h"

void main()
{
	unsigned char x;
	
	lcd_init();
	lcd_setcursor(0,0);
	lcd_printstring("8051 Project");
	lcd_setcursor(1,0);
	lcd_printstring("I2C Protocol");
	delay(1000);
	
	/*Writing Data to slave*/
	I2C_start();
	I2C_datawrite(0xA0);   //sending slave address '1010 000-0' (7-bit address + 1-bit R/W ('0'=write, '1'=read))
	I2C_datawrite(0x00);   //sending register's address/memory location address (8-bits address)
	I2C_datawrite('S');   //Writing Data (8-bits Data) to slave
	I2C_stop();
	
	delay(500);     //Necessasily for distinguishing write and read operations
	
	/*Reading Data from slave*/
	I2C_start();
	I2C_datawrite(0xA0);   //sending slave address '1010 000-0' (7-bit address + 1-bit R/W ('0'=write, '1'=read))
	I2C_datawrite(0x00);   //sending register's address/memory location address (8-bits address)
	I2C_start();
	I2C_datawrite(0xA1);   //sending slave address '1010 000-1' (7-bit address + 1-bit R/W ('0'=write, '1'=read))
	x = I2C_dataread();   //Reading Data (8-bits Data) from slave
	I2C_stop();
	
	lcd_clear();
	lcd_setcursor(0,0);
	lcd_printstring("Recieved Data");
	lcd_setcursor(1,0);
	lcd_printchar(x);
	
	while(1)
	{
		//MY CODE
	}
}