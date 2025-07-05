#include <reg51.h>
#include "delay.h"

sbit rs = P1^0;
sbit en = P1^1;
unsigned int lcd_port=2;

unsigned int keypad_port=3;
unsigned int keypad_totalrows=4,keypad_totalcolumnns=4;
unsigned int keypad_rowpins[]={0,1,2,3};
unsigned int keypad_columnpins[]={4,5,6,7};
unsigned char keys[4][4] = {{'7','8','9','/'},{'4','5','6','x'},{'1','2','3','-'},{'C','0','=','+'}};

#include "LCD_Keypad.h"


int main()
{
	unsigned int key_pressed;
	//unsigned char key;
	
	lcd_init();     //Intialises LCD Display
	lcd_clear();
	lcd_setcursor(0,0);
	lcd_printstring("LCD ON");
	delay(1000);
	
	lcd_clear();
	lcd_setcursor(0,0);
	
	while(1)
	{
		key_pressed = checkkeypad();     //Checking if there is any pressed key
		while(key_pressed == 1)
		{
			//key = getkey();
			//lcd_printchar(key);
			
			//delay(1000);
			
			lcd_printkey();
		}
	}
}