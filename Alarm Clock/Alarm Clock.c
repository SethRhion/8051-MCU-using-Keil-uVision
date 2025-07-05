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

#include "DS1307.h"

sbit ModePIN = P1^3;
sbit SetPIN = P1^4;
sbit AlarmPIN = P1^6;

unsigned int pressed = 0;

unsigned int Mode = 0;
unsigned char HH;
unsigned char MM;

unsigned char TriggerHH_24;
unsigned char address1;
unsigned char TriggerMM;
unsigned char address2;
unsigned char TriggerDurationHH;
unsigned char address3;
unsigned char TriggerDurationMM;
unsigned char address4;

void display_TimeDate()
{
	unsigned char sec,min,hour,format,day,month,year;
	
	/* Read the Time from RTC(ds1307) */
	ds1307_GetTime(&hour,&min,&sec);
	ds1307_GetHour(&hour,&format);
	
	/* Read the Date from RTC(ds1307) */
	ds1307_GetDate(&day,&month,&year);
	
	lcd_clear();
	lcd_setcursor(0,0);
		
	/* Display "time" on first line*/
	lcd_printstring("Time: ");
		
	/* Display "date" on Second line*/
	lcd_setcursor(1,0);
	lcd_printstring("Date: ");
	
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
	
	lcd_setcursor(0,15);
	if(format != '0')
	{
		lcd_printchar(format);      //Prints 'AM' or 'PM'
	}
	
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

void checkModePINstate()
{
  if (ModePIN == pressed) {
    if (Mode < 4) {
      Mode ++;
    }
    else
    {
      Mode = 0;
    }

    while (ModePIN == pressed)
    {
      //Do nothing
    }
  }
}

void SetTimeHH()
{
  unsigned char format;
	
	ds1307_GetHour(&HH,&format);
	
	lcd_clear();   //Displaying on LCD Display
  lcd_setcursor(0, 0);
  lcd_printstring("Set Time");
  lcd_setcursor(1, 0);
  lcd_printstring("Set Hr: ");
  lcd_printnumberXdigits(HH,2);
	if(format != '0')
	{
		lcd_printstring(" ");
		lcd_printchar(format);
	}
	

  if(SetPIN == pressed) //If SetPINstate is pressed during Hour setting
  {
    if(format=='0')
		{
			if(HH < 23)
			{
				HH ++;
				ds1307_Set24Hour(HH);     //Transition between 00:00 and 23:00
			}
			else
			{
				HH = 12;
				ds1307_Set12Hour(HH,'A');     //Transition from 23:00 to 12AM
			}
		}
		else if(format=='A')
		{
			
			if(HH == 12)
			{
				HH = 1;
				ds1307_Set12Hour(HH,'A');    //Transition from 12AM to 1AM
			}
			else if(HH < 11)
			{
				HH ++;
				ds1307_Set12Hour(HH,'A');    //Transition between 1AM to 11AM
			}
			else if(HH == 11)
			{
				HH = 12;
				ds1307_Set12Hour(HH,'P');    //Transition from 11AM to 12PM
			}
		}
		else if(format=='P')
		{
			if(HH == 12)
			{
				HH = 1;
				ds1307_Set12Hour(HH,'P');    //Transition from 12PM to 1PM
			}
			else if(HH < 11)
			{
				HH ++;
				ds1307_Set12Hour(HH,'P');    //Transition between 1PM to 11PM
			}
			else if(HH == 11)
			{
				HH = 0;
				ds1307_Set24Hour(HH);    //Transition from 11PM to 00:00 midnight
			}
		}

    while (SetPIN == pressed)
    {
      //Do nothing
    }
  }
	
}

void SetTimeMM()
{
  ds1307_GetMin(&MM);   //Get current time-mins from ds1307
	
	lcd_clear();   //Displaying on LCD Display
  lcd_setcursor(0, 0);
  lcd_printstring("Set Time");
  lcd_setcursor(1, 0);
  lcd_printstring("Set Mins: ");
  lcd_printnumberXdigits(MM, 2);
  
  if(SetPIN == pressed) //If SetPINstate is pressed during Minutes setting
  {
    if(MM < 59)
    {
      MM ++;
    }
    else
    {
      MM = 0;
    }
    while (SetPIN == pressed)
    {
      //Do nothing
    }
  }
	
  ds1307_SetMin(MM);   //Update Mins in ds1307
}

void SetTriggerTimeHH()
{
	TriggerHH_24 = EEPROM_read(address1);
	
	lcd_clear();   //Displaying on LCD Display
  lcd_setcursor(0, 0);
  lcd_printstring("Set Trigger Time");
  lcd_setcursor(1, 0);
  lcd_printstring("Set Hr(24h): ");
  lcd_printnumberXdigits(TriggerHH_24, 2);
  
  if(SetPIN == pressed) //If SetPIN is pressed during Hour setting
  {
    if(TriggerHH_24 < 23)
    {
      TriggerHH_24 ++;
    }
    else
    {
      TriggerHH_24 = 0;
    }
    while (SetPIN == pressed)
    {
      //Do nothing
    }
  }
  EEPROM_write(address1, TriggerHH_24);
}

void SetTriggerTimeMM()
{
	TriggerMM = EEPROM_read(address2);
	
	lcd_clear();   //Displaying on LCD Display
  lcd_setcursor(0, 0);
  lcd_printstring("Set Trigger Time");
  lcd_setcursor(1, 0);
  lcd_printstring("Set Mins: ");
  lcd_printnumberXdigits(TriggerMM, 2);
  
  if(SetPIN == pressed) //If SetPIN is pressed during Hour setting
  {
    if(TriggerMM < 59)
    {
      TriggerMM ++;
    }
    else
    {
      TriggerMM = 0;
    }
    while (SetPIN == pressed)
    {
      //Do nothing
    }
  }
  EEPROM_write(address2, TriggerMM);
}

void TimeControlledTrigger()
{
  unsigned char currentHH;
  unsigned char currentMM;
	unsigned char format;
	
	ds1307_GetHour(&currentHH,&format);      //Getting Hour(s) value of Current time from RTC
	ds1307_GetMin(&currentMM);            //Getting Minute(s) value of Current time from RTC
	
	TriggerHH_24 = EEPROM_read(address1);
	TriggerMM = EEPROM_read(address2);
	TriggerDurationHH = EEPROM_read(address3);
	TriggerDurationMM = EEPROM_read(address4);
	
  if (((currentHH >= TriggerHH_24)&&(currentHH <= (TriggerHH_24+TriggerDurationHH))) && ((currentMM >= TriggerMM)&&(currentMM <= (TriggerMM+TriggerDurationMM))))
  {
    AlarmPIN = 1;
  }
  else
  {
    AlarmPIN = 0;
  }
}

void main()
{
	address1 = 0x00;                                   //EEPROM address for TriggerHH_24
	address2 = address1 + sizeof(TriggerHH_24);        //EEPROM address for TriggerMM
	address3 = address2 + sizeof(TriggerMM);           //EEPROM address for TriggerDurationHH
	address4 = address3 + sizeof(TriggerDurationHH);   //EEPROM address for TriggerDurationMM
	
	EEPROM_write(address1, 00);     //Initially storing TriggerHH as '00' into EEPROM
	EEPROM_write(address2, 01);     //Initially storing TriggerMM as '01' into EEPROM
	EEPROM_write(address3, 00);     //Initially storing TriggerDurationHH as '00' into EEPROM
	EEPROM_write(address4, 03);     //Initially storing TriggerDurationMM as '03' into EEPROM
	
	lcd_init();
	lcd_setcursor(0,0);
	lcd_printstring("8051 Project");
	lcd_setcursor(1,0);
	lcd_printstring("ALARM CLOCK");
	
	/* Initilize the RTC(ds1307)*/
	ds1307_Init();
 
  /*set the time and Date only once */
  ds1307_SetTime(23,59,30);  //Initially Setting time
  ds1307_SetDate(31,12,19);  //Initially Setting Date  
 
	delay(1000);
	
	//ds1307_GetTime(&HH,&MM,&SS);
	
	AlarmPIN = 0;   //Initially setting alarm OFF
		
	while(1)
	{
		checkModePINstate();
		switch(Mode)
		{
			case 1:
				SetTimeHH();
			  break;
			case 2:
				SetTimeMM();
			  break;
			//case 3:
				//SetDate();
        //break;
			//case 4:
				//SetMonth();
        //break;
			//case 5:
				//SetYear();
        //break;
			case 3:
				SetTriggerTimeHH();
			  break;
			case 4:
				SetTriggerTimeMM();
			  break;
			//case 8:
				//SetTriggerDuration();
			  //break;
			default:
				display_TimeDate();
			  break;
		}
		
		TimeControlledTrigger();
  
	}

}