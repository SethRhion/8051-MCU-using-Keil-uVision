#include <reg51.h>
#include "delay.h"

unsigned int lcd_port=2;      //Specify Port used for rs,en,datapins as global variable
sbit en = P1^1;
sbit rs = P1^0;     //Specify rs and en pins as global variable

#include "LCD.h"

sbit SCL = P3^0;
sbit SDA = P3^1;

#include "I2C.h"

#define EEPROM_ID 0xA0     // EEPROM ID

#include "EEPROM.h"

void main()
{
	unsigned char data1,data2;
	unsigned char letter='S';
	unsigned char address1=0x00;
	unsigned char address2 = address1 + sizeof(letter);
	
	lcd_init();
	lcd_setcursor(0,0);
	lcd_printstring("8051 Project");
	lcd_setcursor(1,0);
	lcd_printstring("I2C Protocol");
	delay(1000);
	
	/*Writing Data to slave*/
	EEPROM_write(address1, letter);
	EEPROM_write(address2, 132);     //NOTE: Maximum is 8-bit(i.e 255) data per register address
	
	delay(500);     //Necessasily for distinguishing write and read operations
	
	/*Reading Data from slave*/
	data1 = EEPROM_read(address1);
	data2 = EEPROM_read(address2);
	
	lcd_clear();
	lcd_setcursor(0,0);
	lcd_printstring("Recieved Data");
	lcd_setcursor(1,0);
	lcd_printchar(data1);
	lcd_printnumber(data2);
	
	while(1)
	{
		//MY CODE
	}
}