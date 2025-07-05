#include <reg51.h>
#include "delay.h"

unsigned int lcd_port=2;      //Specify Port used for rs,en,datapins as global variable
sbit en = P1^1;
sbit rs = P1^0;     //Specify rs and en pins as global variable

#include "LCD.h"

sbit SCL = P3^0;
sbit SDA = P3^1;

#include "I2C.h"

#include "DS1307.h"

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