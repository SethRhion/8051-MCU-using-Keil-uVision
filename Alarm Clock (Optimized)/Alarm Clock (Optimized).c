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

#include "ds1307.h"

sbit ModePIN = P1^3;
sbit SetPIN = P1^4;
sbit StatePIN = P1^5;
sbit AlarmPIN = P1^7;

unsigned int pressed = 0;

unsigned int Mode = 0;
unsigned int State = 0;

unsigned char TriggerHH_24;
unsigned char address1;
unsigned char TriggerMM;
unsigned char address2;
unsigned char TriggerDurationHH;
unsigned char address3;
unsigned char TriggerDurationMM;
unsigned char address4;

/*Function for displaying Date and Time*/
void display_TimeDate()
{
	unsigned char sec,min,hour,format,day,month,year,weekday;
	unsigned char weekdays[]={'M','T','W','T','F','S','S'};
	
	/* Read the Time from RTC(ds1307) */
	ds1307_GetTime(&hour,&min,&sec,&format);
	
	/* Read the Date from RTC(ds1307) */
	ds1307_GetDate(&day,&month,&year,&weekday);
	
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
	/*Display weekday*/
	lcd_printchar(' ');
	lcd_printchar(weekdays[weekday-1]);
}

/*Function for displaying State and Output*/
void display_StateOutput()
{
	lcd_clear();
		
	/* Display "State" on first line*/
	lcd_setcursor(0,0);
	lcd_printstring("State: ");
	if (State == 0)
	{
		lcd_printstring("Automatic");   //Automatic State
	}
	else
	{
		lcd_printstring("Manual");   //Manual State
	}
	
		
	/* Display "ON/OFF" on Second line*/
	lcd_setcursor(1,0);
	lcd_printstring("Output: ");
	if (AlarmPIN == 0)
	{
		lcd_printstring("OFF");   //OFF State
	}
	else
	{
		lcd_printstring("ON");   //ON State
	}
}

/*Functions for MENU Navigation*/
void checkModePINstate()
{
  if (ModePIN == pressed) {
    if (Mode < 10) {
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

/*Functions for State Switching*/
void checkStatePINstate()
{
  if (StatePIN == pressed) {
    if (State < 2) {
      State ++;
    }
    else
    {
      State = 0;
    }

    while (StatePIN == pressed)
    {
      //Do nothing
    }
  }
}

/*Functions for setting Time Parameters*/
void SetTimeHH()
{
  unsigned char HH,MM,SS,format;
	
	ds1307_GetTime(&HH,&MM,&SS,&format);
	
	lcd_clear();   //Displaying on LCD Display
  lcd_setcursor(0, 0);
  lcd_printstring("Set Time (hrs)");
  lcd_setcursor(1, 0);
  lcd_printnumberXdigits(HH,2);
	lcd_printchar(' ');
	lcd_printchar(':');
	lcd_printchar(' ');
	lcd_printnumberXdigits(MM,2);
	
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
				ds1307_SetHour(HH,'0');     //Transition between 00:00 and 23:00
			}
			else
			{
				HH = 12;
				ds1307_SetHour(HH,'A');     //Transition from 23:00 to 12AM
			}
		}
		else if(format=='A')
		{
			
			if(HH == 12)
			{
				HH = 1;
				ds1307_SetHour(HH,'A');    //Transition from 12AM to 1AM
			}
			else if(HH < 11)
			{
				HH ++;
				ds1307_SetHour(HH,'A');    //Transition between 1AM to 11AM
			}
			else if(HH == 11)
			{
				HH = 12;
				ds1307_SetHour(HH,'P');    //Transition from 11AM to 12PM
			}
		}
		else if(format=='P')
		{
			if(HH == 12)
			{
				HH = 1;
				ds1307_SetHour(HH,'P');    //Transition from 12PM to 1PM
			}
			else if(HH < 11)
			{
				HH ++;
				ds1307_SetHour(HH,'P');    //Transition between 1PM to 11PM
			}
			else if(HH == 11)
			{
				HH = 0;
				ds1307_SetHour(HH,'0');    //Transition from 11PM to 00:00 midnight
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
	unsigned char HH,MM,SS,format;
	ds1307_GetTime(&HH,&MM,&SS,&format);
	
	lcd_clear();   //Displaying on LCD Display
  lcd_setcursor(0, 0);
  lcd_printstring("Set Time (mins)");
  lcd_setcursor(1, 0);
  lcd_printnumberXdigits(HH,2);
	lcd_printchar(' ');
	lcd_printchar(':');
	lcd_printchar(' ');
	lcd_printnumberXdigits(MM,2);
	
	if(format != '0')
	{
		lcd_printstring(" ");
		lcd_printchar(format);
	}
  
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

/*Functions for setting Date Parameters*/
void SetDateDay()
{
	unsigned char day,month,year,weekday;
	unsigned char weekdays[]={'M','T','W','T','F','S','S'};
	ds1307_GetDate(&day,&month,&year,&weekday);
	
	lcd_clear();   //Displaying on LCD Display
  lcd_setcursor(0, 0);
  lcd_printstring("Set Date (day)");
  lcd_setcursor(1, 0);
  lcd_printnumberXdigits(day,2);
	lcd_printchar(' ');
	lcd_printchar('/');
	lcd_printchar(' ');
	lcd_printnumberXdigits(month,2);
	lcd_printchar(' ');
	lcd_printchar('/');
	lcd_printchar(' ');
	lcd_printnumberXdigits(year,2);
	lcd_printchar(' ');
	lcd_printchar(weekdays[weekday-1]);
  
  if(SetPIN == pressed) //If SetPINstate is pressed during Day setting
  {
    if(day < 31)
    {
      day ++;
    }
    else
    {
      day = 1;
    }
    while (SetPIN == pressed)
    {
      //Do nothing
    }
  }
	
  ds1307_SetDate(day, month, year, weekday);   //Update Date in ds1307
}

void SetDateMonth()
{
	unsigned char day,month,year,weekday;
	unsigned char weekdays[]={'M','T','W','T','F','S','S'};
	ds1307_GetDate(&day,&month,&year,&weekday);
	
	lcd_clear();   //Displaying on LCD Display
  lcd_setcursor(0, 0);
  lcd_printstring("Set Date (month)");
  lcd_setcursor(1, 0);
  lcd_printnumberXdigits(day,2);
	lcd_printchar(' ');
	lcd_printchar('/');
	lcd_printchar(' ');
	lcd_printnumberXdigits(month,2);
	lcd_printchar(' ');
	lcd_printchar('/');
	lcd_printchar(' ');
	lcd_printnumberXdigits(year,2);
	lcd_printchar(' ');
	lcd_printchar(weekdays[weekday-1]);
  
  if(SetPIN == pressed) //If SetPINstate is pressed during Month setting
  {
    if(month < 12)
    {
      month ++;
    }
    else
    {
      month = 1;
    }
    while (SetPIN == pressed)
    {
      //Do nothing
    }
  }
	
  ds1307_SetDate(day, month, year, weekday);   //Update Date in ds1307
}

void SetDateYear()
{
	unsigned char day,month,year,weekday;
	unsigned char weekdays[]={'M','T','W','T','F','S','S'};
	ds1307_GetDate(&day,&month,&year,&weekday);
	
	lcd_clear();   //Displaying on LCD Display
  lcd_setcursor(0, 0);
  lcd_printstring("Set Date (year)");
  lcd_setcursor(1, 0);
  lcd_printnumberXdigits(day,2);
	lcd_printchar(' ');
	lcd_printchar('/');
	lcd_printchar(' ');
	lcd_printnumberXdigits(month,2);
	lcd_printchar(' ');
	lcd_printchar('/');
	lcd_printchar(' ');
	lcd_printnumberXdigits(year,2);
	lcd_printchar(' ');
	lcd_printchar(weekdays[weekday-1]);
  
  if(SetPIN == pressed) //If SetPINstate is pressed during Year setting
  {
    if(year < 99)
    {
      year ++;
    }
    else
    {
      year = 1;
    }
    while (SetPIN == pressed)
    {
      //Do nothing
    }
  }
	
  ds1307_SetDate(day, month, year, weekday);   //Update Date in ds1307
}

void SetDateWeekday()
{
	unsigned char day,month,year,weekday;
	unsigned char weekdays[]={'M','T','W','T','F','S','S'};
	ds1307_GetDate(&day,&month,&year,&weekday);
	
	lcd_clear();   //Displaying on LCD Display
  lcd_setcursor(0, 0);
  lcd_printstring("Set Date (wkday)");
  lcd_setcursor(1, 0);
  lcd_printnumberXdigits(day,2);
	lcd_printchar(' ');
	lcd_printchar('/');
	lcd_printchar(' ');
	lcd_printnumberXdigits(month,2);
	lcd_printchar(' ');
	lcd_printchar('/');
	lcd_printchar(' ');
	lcd_printnumberXdigits(year,2);
	lcd_printchar(' ');
	lcd_printchar(weekdays[weekday-1]);
  
  if(SetPIN == pressed) //If SetPINstate is pressed during Weekday setting
  {
    if(weekday < 7)
    {
      weekday ++;
    }
    else
    {
      weekday = 1;
    }
    while (SetPIN == pressed)
    {
      //Do nothing
    }
  }
	
  ds1307_SetDate(day, month, year, weekday);   //Update Date in ds1307
}

/*Functions for setting TriggerTime Parameters*/
void SetTriggerTimeHH()
{
	TriggerHH_24 = EEPROM_read(address1);
	TriggerMM = EEPROM_read(address2);
	
	//lcd_clear();   //Displaying on LCD Display
  //lcd_setcursor(0, 0);
  //lcd_printstring("Set ON Time (H)");
  //lcd_setcursor(1, 0);
  //lcd_printstring("Hours:");
  //lcd_printnumberXdigits(TriggerHH_24, 2);
	//lcd_setcursor(1, 9);
  //lcd_printstring("Mins:");
  //lcd_printnumberXdigits(TriggerMM, 2);
	
	lcd_clear();   //Displaying on LCD Display
  lcd_setcursor(0, 0);
  lcd_printstring("Set ON Time (H)");
  lcd_setcursor(1, 0);
  lcd_printnumberXdigits(TriggerHH_24,2);
	lcd_printchar(' ');
	lcd_printchar(':');
	lcd_printchar(' ');
	lcd_printnumberXdigits(TriggerMM,2);
  
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
	TriggerHH_24 = EEPROM_read(address1);
	TriggerMM = EEPROM_read(address2);
	
	lcd_clear();   //Displaying on LCD Display
  lcd_setcursor(0, 0);
  lcd_printstring("Set ON Time (m)");
  lcd_setcursor(1, 0);
  lcd_printnumberXdigits(TriggerHH_24,2);
	lcd_printchar(' ');
	lcd_printchar(':');
	lcd_printchar(' ');
	lcd_printnumberXdigits(TriggerMM,2);
  
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

/*Functions for setting TriggerDuration Parameters*/
void SetTriggerDurationHH()
{
	TriggerDurationHH = EEPROM_read(address3);
	TriggerDurationMM = EEPROM_read(address4);
	
	//lcd_clear();   //Displaying on LCD Display
  //lcd_setcursor(0, 0);
  //lcd_printstring("Set ON Period(H)");
  //lcd_setcursor(1, 0);
  //lcd_printstring("Hours:");
  //lcd_printnumberXdigits(TriggerDurationHH, 2);
	//lcd_setcursor(1, 9);
  //lcd_printstring("Mins:");
  //lcd_printnumberXdigits(TriggerDurationMM, 2);
	
	lcd_clear();   //Displaying on LCD Display
  lcd_setcursor(0, 0);
  lcd_printstring("Set ON Period(H)");
  lcd_setcursor(1, 0);
  lcd_printnumberXdigits(TriggerDurationHH,2);
	lcd_printchar(' ');
	lcd_printchar(':');
	lcd_printchar(' ');
	lcd_printnumberXdigits(TriggerDurationMM,2);
  
  if(SetPIN == pressed) //If SetPIN is pressed during Hour setting
  {
    if(TriggerDurationHH < 23)
    {
      TriggerDurationHH ++;
    }
    else
    {
      TriggerDurationHH = 0;
    }
    while (SetPIN == pressed)
    {
      //Do nothing
    }
  }
  EEPROM_write(address3, TriggerDurationHH);
}

void SetTriggerDurationMM()
{
	TriggerDurationHH = EEPROM_read(address3);
	TriggerDurationMM = EEPROM_read(address4);
	
	lcd_clear();   //Displaying on LCD Display
  lcd_setcursor(0, 0);
  lcd_printstring("Set ON Period(m)");
  lcd_setcursor(1, 0);
  lcd_printnumberXdigits(TriggerDurationHH,2);
	lcd_printchar(' ');
	lcd_printchar(':');
	lcd_printchar(' ');
	lcd_printnumberXdigits(TriggerDurationMM,2);
  
  if(SetPIN == pressed) //If SetPIN is pressed during Hour setting
  {
    if(TriggerDurationMM < 59)
    {
      TriggerDurationMM ++;
    }
    else
    {
      TriggerDurationMM = 0;
    }
    while (SetPIN == pressed)
    {
      //Do nothing
    }
  }
  EEPROM_write(address4, TriggerDurationMM);
}

/*Function for Time Controlled Trigger*/
void TimeControlledTrigger()
{
  unsigned char currentHH;
  unsigned char currentMM;
	unsigned char currentSS;
	unsigned char format;
	
	ds1307_GetTime(&currentHH, &currentMM, &currentSS, &format);      //Getting Current time details from RTC
	
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
  ds1307_SetDate(31,12,19,1);  //Initially Setting Date  
 
	delay(1000);
	
	//ds1307_GetTime(&HH,&MM,&SS);
	
	AlarmPIN = 0;   //Initially setting alarm OFF
		
	while(1)
	{
		checkModePINstate();     //MENU Navigation
		
		switch(Mode)
		{
			case 1:
				SetTimeHH();
			  break;
			case 2:
				SetTimeMM();
			  break;
			case 3:
				SetDateDay();
        break;
			case 4:
				SetDateMonth();
        break;
			case 5:
				SetDateYear();
        break;
			case 6:
				SetDateWeekday();
        break;
			case 7:
				SetTriggerTimeHH();
			  break;
			case 8:
				SetTriggerTimeMM();
			  break;
			case 9:
				SetTriggerDurationHH();
			  break;
			case 10:
				SetTriggerDurationMM();
			  break;
			default:
				display_TimeDate();
			  display_StateOutput();
			  break;
		}
		
		checkStatePINstate();     //Automatic / Manual
		
		if (State == 0)
		{
			TimeControlledTrigger();   //Automatic State
		}
		else if (State == 1)
		{
			AlarmPIN = 0;   //Manual OFF State
		}
		else
		{
			AlarmPIN = 1;   //Manual ON State
		}
  
	}

}