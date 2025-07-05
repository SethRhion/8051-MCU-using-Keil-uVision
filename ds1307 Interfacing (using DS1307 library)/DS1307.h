//#include <reg51.h>
//#include "delay.h"

//sbit SCL = P3^0;
//sbit SDA = P3^1;

//#include "I2C.h"

//#include "DS1307.h"

/* Below given values are fixed and should not be changed.
    Refer Ds1307 DataSheet for more info*/ 
#define DS1307_ID 0xD0     // ds1307 ID
#define SEC_ADDRESS   0x00 // address to access ds1307 SEC register
#define DAY_ADDRESS   0x03 // address to access ds1307 DAY register
#define DATE_ADDRESS  0x04 // address to access ds1307 DATE register
#define control       0x07 // address to access ds1307 CONTROL register

void ds1307_Init();
void ds1307_SetTime(unsigned char hh, unsigned char mm, unsigned char ss);
void ds1307_SetDayOfWeek(unsigned char day);
void ds1307_SetDate(unsigned char dd, unsigned char mm, unsigned char yy);
void ds1307_GetTime(unsigned char *h_ptr,unsigned char *m_ptr,unsigned char *s_ptr);
void ds1307_GetDate(unsigned char *d_ptr,unsigned char *m_ptr,unsigned char *y_ptr);

/*ds1307 initilization*/
void ds1307_Init()
{
	I2C_start();        // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(control);
	I2C_datawrite(0x00);
	
	I2C_stop();
}

void ds1307_SetTime(unsigned char hh, unsigned char mm, unsigned char ss)
{
	I2C_start();            // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(SEC_ADDRESS);
	I2C_datawrite(ss);
	I2C_datawrite(mm);
	I2C_datawrite(hh);
	
	I2C_stop();             // Stop i2c communication after Setting the Time
}

void ds1307_SetDayOfWeek(unsigned char day)
{
	I2C_start();            // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(DAY_ADDRESS);
	I2C_datawrite(day);
	
	I2C_stop();             // Stop i2c communication after Setting the Date
}

void ds1307_SetDate(unsigned char dd, unsigned char mm, unsigned char yy)
{
	I2C_start();            // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(DATE_ADDRESS);
	I2C_datawrite(dd);
	I2C_datawrite(mm);
	I2C_datawrite(yy);
	
	I2C_stop();             // Stop i2c communication after Setting the Date
}

void ds1307_GetTime(unsigned char *h_ptr,unsigned char *m_ptr,unsigned char *s_ptr)
{
	unsigned int temp;
	I2C_start();           // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(SEC_ADDRESS);
	
	I2C_stop();
	
	I2C_start();
	
	I2C_datawrite(0xD1);
	temp = I2C_dataread();                   //Read hex value of sec from RTC
	*s_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of sec into decimal form
	I2C_Ack();
	temp = I2C_dataread();                   //Read hex value of min from RTC
	*m_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of min into decimal form
	I2C_Ack();
	temp = I2C_dataread();                   //Read hex value of hour from RTC
	*h_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of hour into decimal form
	I2C_NoAck();
	
	I2C_stop();               // stop i2c communication after reading the Time
}

void ds1307_GetDate(unsigned char *d_ptr,unsigned char *m_ptr,unsigned char *y_ptr)
{
	unsigned int temp;
	I2C_start();            // start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(DATE_ADDRESS);
	
	I2C_stop();
	
	I2C_start();
	I2C_datawrite(0xD1);
	
	temp = I2C_dataread();                   //Read hex value of date from RTC
	*d_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of date into decimal form
	I2C_Ack();
	temp = I2C_dataread();                   //Read hex value of month from RTC
	*m_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of month into decimal form
	I2C_Ack();
	temp = I2C_dataread();                   //Read hex value of year from RTC
	*y_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of year into decimal form
	I2C_NoAck();
	
	I2C_stop();         // stop i2c communication after reading the Time
}