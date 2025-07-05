#include <reg51.h>
#include "delay.h"

unsigned int lcd_port=2;      //Specify Port used for rs,en,datapins as global variable
sbit en = P1^1;
sbit rs = P1^0;     //Specify rs and en pins as global variable

#include "LCD.h"

sbit SCL = P3^0;
sbit SDA = P3^1;

void I2C_start();
void I2C_stop();
void I2C_datawrite(unsigned char I2C_data);     //Writes one byte of Data (8-bits), 1-bit at time
unsigned char I2C_dataread();     //Reads one byte of Data (8-bits), 1-bit at time

void I2C_start()
{
	SCL = 1;
	SDA = 1;
	delay(5);
	SDA = 0;
	delay(5);
	SCL = 0;
}

void I2C_stop()
{
	SCL = 0;
	SDA = 0;
	delay(5);
	SCL = 1;
	delay(5);
	SDA = 1;
}

void I2C_datawrite(unsigned char I2C_data)     //Writes one byte of Data (8-bits), 1-bit at time
{
	unsigned char i;
	for(i=0 ; i<8 ; i++)
	{
		SDA = (I2C_data & 0x80)?1:0;    //If first MSB is '1' send '1' else send '0'
		SCL = 1;
		delay(5);
		SCL = 0;
		I2C_data = I2C_data<<1;    //bits are sent from MSB to LSB
	}
	SDA = 1;  //Slave will return '0' as ACK i.e SDA=0, if it remains as '1' then no ACK was recieved
	SCL = 1;
	while(SDA==1)   //waiting for '0' (ACK) from slave
	{
		//Do nothing or Wait
	}
	SCL = 0;
	delay(5);
}

unsigned char I2C_dataread()     //Reads one byte of Data (8-bits), 1-bit at time
{
	bit rd_bit;
	unsigned char i, I2C_data;
	for(i=0 ; i<8 ; i++)
	{
		delay(5);
		SCL = 1;
		delay(5);
		rd_bit = SDA;    //Storing 1-bit recieved from SDA
		I2C_data = I2C_data<<1;    //bits are recieved from MSB to LSB
		I2C_data = I2C_data | rd_bit;
		SCL = 0;
	}
	SDA = 1;   //Sending negative-ACK from master
	SCL = 1;
	delay(5);
	SCL = 0;
	return I2C_data;
}

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
	I2C_datawrite('A');   //Writing Data (8-bits Data) to slave
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