#include <reg51.h>
#include "delay.h"

sbit rs = P1^0;
sbit en = P1^1;
unsigned int lcd_port=2;

#include "LCD.h"   //Declared after rs,en and port declaration i.e rs,en and port are used in LCD.h functions

int main()
{
	unsigned char keys[4][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
	unsigned int keypad_port = 3;
	unsigned int keypad_rowpins[] = {4,5,6,7};
	unsigned int keypad_columnpins[] = {0,1,2};
	unsigned int r=4,c=3,i,j,k;
	
	lcd_init();
	lcd_clear();
	lcd_setcursor(0,0);
	lcd_printstring("LCD ON");
	delay(1000);
	
	lcd_clear();
	lcd_setcursor(0,0);
	
	while(1)
	{
		for(i=0 ; i<r ; i++)
		{
			P3 &= ~(1<<keypad_rowpins[i]);     //Set '0' to only one row at a time
			for(j=0 ; j<r ; j++)
			{
				if(i != j)
				{
					P3 |= (1<<keypad_rowpins[j]);     //Set '1' to all others rows at a time
				}
				else
				{
					continue;
				}
			}
			
			for(k=0 ; k<c ; k++)
			{
				if((P3 & (1<<keypad_columnpins[k])) == 0)     //Searching for '0' in each column one by one
				{
					lcd_printchar(keys[i][k]);
					while((P3 & (1<<keypad_columnpins[k])) == 0)
					{
						//Do nothing
					}
				}
			}
			
		}
	}
}