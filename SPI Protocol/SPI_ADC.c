#include <reg51.h>
#include "delay.h"

unsigned int lcd_port=2;      //Specify Port used for rs,en,datapins as global variable
sbit en = P1^1; sbit rs = P1^0;     //Specify rs and en pins as global variable

sbit cs=P1^5;   //chip select i.e slave select
sbit clk=P1^2;   //serial clock
sbit din=P1^3;   //MOSI
sbit dout=P1^4;   //MISO

#include "LCD.h"

unsigned int SPI_ADC_value()
{
	unsigned int i,temp;
	cs=0;
	clk=0; din=1 ; clk=1;   //start
	clk=0; din=1 ; clk=1;   //single ended
	
	/*ADC Channel selection*/
	//E.g d2=0,d1=0,d0=0 : CH0
	clk=0; din=0 ; clk=1;   //d2
	clk=0; din=0 ; clk=1;   //d1
	clk=0; din=0 ; clk=1;   //d0
	
	clk=0; din=1 ; clk=1;   //t sample
	clk=0; din=1 ; clk=1;   //nullbit
	
	/*Reading Data from slave*/
	for (i=11; i>=0 ; i--)
	{
		clk=0;
		if(dout==1)
		{
			temp |= (1<<i);
		}
		clk=1;
	}
	cs=1;
	
	return temp;
}

void main()
{
	unsigned int temp;
	
	lcd_init();
	lcd_clear();
	lcd_setcursor(0,0);
	lcd_printstring("8051 Project");
	lcd_setcursor(1,0);
	lcd_printstring("SPI Protocol");
	delay(1000);
	
	while(1)
	{
		temp = SPI_ADC_value();   //Getting ADC value from slave
		lcd_clear();
	  lcd_setcursor(0,0);
	  lcd_printstring("ADC value");
	  lcd_setcursor(1,0);
	  lcd_printnumber(temp);    //NOTE:Can only print whole numbers from 0 to 65535(0xFFFF) i.e highest 16-bits number
	}
}