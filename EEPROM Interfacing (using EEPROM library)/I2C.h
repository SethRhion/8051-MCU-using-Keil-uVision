//#include <reg51.h>
//#include "delay.h"

//sbit SCL = P3^0;
//sbit SDA = P3^1;

//#include "I2C.h"

void I2C_start();
void I2C_stop();
void I2C_datawrite(unsigned char I2C_data);     //Writes one byte of Data (8-bits), 1-bit at time
unsigned char I2C_dataread();     //Reads one byte of Data (8-bits), 1-bit at time
void I2C_Clock(void);
void I2C_Ack();      //Sending positive-ACK from master
void I2C_NoAck();     //Sending negative-ACK from master

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
	//I2C_NoAck();     //Sending negative-ACK from master
	return I2C_data;
}

void I2C_Clock()
{
	delay(5);
	SCL = 1;
	
	delay(5);
	SCL = 0;        
}

void I2C_Ack()
{
	SDA = 0;
	I2C_Clock();
	SDA = 1;        
}

void I2C_NoAck()
{
	SDA = 1;
	I2C_Clock();
	SCL = 1;     
}