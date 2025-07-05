#include <reg51.h>
#include "delay.h"

unsigned int lcd_port=2;      //Specify Port used for rs,en,datapins as global variable
sbit en = P1^1;
sbit rs = P1^0;     //Specify rs and en pins as global variable

#include "LCD.h"

sbit SCL = P3^0;
sbit SDA = P3^1;

#include "I2C.h"

/* Below given values are fixed and should not be changed.
    Refer Ds1307 DataSheet for more info*/ 
#define DS1307_ID 0xD0     // ds1307 ID
#define SEC_ADDRESS   0x00 // address to access ds1307 SEC register
#define DAY_ADDRESS   0x03 // address to access ds1307 DAY register
#define DATE_ADDRESS  0x04 // address to access ds1307 DATE register
#define control       0x07 // address to access ds1307 CONTROL register

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

void main()
{
	unsigned char sec,min,hour,day,month,year;
	
	lcd_init();
	lcd_setcursor(0,0);
	lcd_printstring("8051 Project");
	lcd_setcursor(1,0);
	lcd_printstring("RTC Interfacing");
	
	/* Initilize the RTC(ds1307)*/
	ds1307_Init();
 
  /*set the time and Date only once */
  ds1307_SetTime(0x23,0x59,0x30);  //Set time  
  ds1307_SetDate(0x31,0x12,0x19);  //Set Date  
 
	delay(1000);

	lcd_clear();
	lcd_setcursor(0,0);
		
	/* Display "time" on first line*/
	lcd_printstring("Time: ");
		
	/* Display "date" on Second line*/
	lcd_setcursor(1,0);
	lcd_printstring("Date: ");
		
	
	/* Display the time and date continously */
	while(1)
	{
		/* Read the Time from RTC(ds1307) */
		ds1307_GetTime(&hour,&min,&sec);        
 
		/* Display the time on firstline 7th position*/
		lcd_setcursor(0,6);
		/*Display hours*/
		lcd_printnumberXdigits(hour,2);
		lcd_printchar(':');
		/*Display mins*/
		lcd_printnumberXdigits(min,2);
		lcd_printchar(':');
		/*Display secs*/
		lcd_printnumberXdigits(sec,2);
		
		/* Read the Date from RTC(ds1307) */
		ds1307_GetDate(&day,&month,&year);        
 
		/* Display the Date on secondline 7th position*/
		lcd_setcursor(1,6);
		/*Display date*/
		lcd_printnumberXdigits(day,2);
		lcd_printchar('/');
		/*Display month*/
		lcd_printnumberXdigits(month,2);
		lcd_printchar('/');
		/*Display year*/
		lcd_printnumberXdigits(year,2);
	}

}