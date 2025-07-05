#include <reg51.h>
#include "delay.h"

sbit rs = P1^0;
sbit en = P1^1;
unsigned int port=2;

#include "LCD.h"   //Declared after rs,en and port declaration i.e rs,en and port are used in LCD.h functions

void main()
{
	lcd_init();
	
	while(1)
	{
		lcd_clear();
		lcd_setcursor(0,0);
	  lcd_printstring("Hello Seth");
	  lcd_setcursor(1,0);
	  lcd_printstring("Welcome");
	  delay(1000);
	
	  lcd_clear();
	  lcd_setcursor(0,0);
	  lcd_printstring("8051 Project");
	  lcd_setcursor(1,0);
	  lcd_printstring("LCD Interfacing");
		delay(1000);
		
		lcd_clear();
	  lcd_setcursor(0,0);
	  lcd_printstring("Lucky Number");
	  lcd_setcursor(1,0);
	  lcd_printnumber(54321);    //NOTE:Can only print whole numbers from 0 to 65535(0xFFFF) i.e highest 16-bits number
		delay(1000);
		
		lcd_clearRow(0);
	  lcd_printstring("Percentage");
		lcd_clearRow(1);
	  lcd_printnumber(85);
		lcd_printchar('%');
		delay(1000);
	}
}