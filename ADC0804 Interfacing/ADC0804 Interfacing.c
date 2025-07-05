#include <reg51.h>
#include "delay.h"

unsigned int lcd_port=2;      //Specify Port used for rs,en,datapins as global variable
sbit en = P0^7;
sbit rs = P0^6;     //Specify rs and en pins as global variable

#include "LCD.h"

sbit ADC_RDpin = P0^0;
sbit ADC_WRpin = P0^1;
sbit ADC_INTRpin = P0^2;
unsigned int ADC_port = 1;
sfr ADC = 0x90;  //P1 address

void main()
{
	lcd_init();
	lcd_setcursor(0,0);
	lcd_printstring("8051 Project");
	lcd_setcursor(1,0);
	lcd_printstring("ADC Interfacing");
	delay(1000);
	
	while(1)
	{
		ADC_RDpin = 1;   //Read function is Turn OFF i.e active-low
		ADC_WRpin = 0;   //Starts the conversion i.e active-low
		delay(100);
		ADC_WRpin = 1;
		while(ADC_INTRpin==1);  //Do nothing & wait for conversion to completed
		delay(100);
		ADC_RDpin = 0;   //Read converted Data from ADC to MCU
		ADC_INTRpin = 1;   //Next conversion
		
		lcd_clear();
	  lcd_setcursor(0,0);
	  lcd_printstring("ADC value");
	  lcd_setcursor(1,0);
	  lcd_printnumber(ADC);
	  delay(1000);
		
		lcd_clear();
	  lcd_setcursor(0,0);
	  lcd_printstring("Temp value");
	  lcd_setcursor(1,0);
	  lcd_printnumber(2*ADC);
	  delay(1000);
	}
}