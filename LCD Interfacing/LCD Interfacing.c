#include<reg51.h>

sbit rs = P1^0;
sbit en = P1^1;

void delay(unsigned int count)
{
	unsigned int i;
	while(count)
	{
		i = 115;
		while(i > 0)
			i--;
		count--;
	}
}

void lcd_data(unsigned char abc)   //Funtion to print to LCD display (recieves only one character at a time)
{
	rs = 1;
	en = 1;
	P2 = abc;
	delay(50);
	en = 0;
}

void lcd_cmd(unsigned char abc)  //Funtion for sending commands to LCD display
{
	rs = 0;
	en = 1;
	P2 = abc;
	delay(50);
	en = 0;
}

void lcd_data2(unsigned char text[])   //My own generated function (recieves entire string/text at a time)
{
  unsigned int n=0, i;
  while(text[n] != '\0')  //calculates number of characters in text/string
  {
      n++;
  }
  for (i=0 ; i<n ; i++)  //prints each character of given text/string at a time
	{
		rs = 1;
	  en = 1;
	  P2 = text[i];
	  delay(50);
	  en = 0;
	}
}
	
void main()
{
	lcd_cmd(0x38) ;  // initialize
  lcd_cmd (0x02);  //return home
  lcd_cmd(0x01);   //clear display
  lcd_cmd(0x0C);   //Display ON cursor OFF
  lcd_cmd(0x06) ;
  lcd_cmd(0x80);   //Address where lcddata should be printed (0x80 means row=0,column=0) i.e address is from 0x80 to 0x8F

	//lcd_data2("Hello Seth");
	
	//lcd_cmd(0xC0);   //Address where lcddata should be printed (0x80 means row=1,column=0) i.e address is from 0xC0 to 0xCF
	//lcd_data2("Welcome");
	
	lcd_data('W');
	lcd_data('e');
	lcd_data('l');
	lcd_data('c');
	lcd_data('o');
	lcd_data('m');
	lcd_data('e');
	
	while(1)
	{
		//loop
	}
}