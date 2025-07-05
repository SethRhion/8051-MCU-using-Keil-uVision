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

void lcd_cmd(unsigned char abc)  //Funtion for sending commands to LCD display
{
	rs = 0;
	en = 1;
	P2 = abc;
	delay(50);
	en = 0;
}

void lcd_init()
{
	lcd_cmd(0x38) ;  // initialize
	lcd_cmd (0x02);  //return home
	lcd_cmd(0x01);   //clear display
  lcd_cmd(0x0C);   //Display ON cursor OFF
  lcd_cmd(0x06) ;   //Increment cursor (shift cursor to the right)
}

void lcd_printchar(unsigned char abc)   //Funtion to print to LCD display (recieves only one character at a time)
{
	rs = 1;
	en = 1;
	P2 = abc;
	delay(50);
	en = 0;
}

void lcd_printstring(unsigned char text[])   //My own generated function (recieves entire string/text at a time)
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

void lcd_clear()
{
	lcd_cmd(0x01);   //clear display
}

void lcd_setcursor(unsigned int row, unsigned int column)
{
	unsigned int address;
	if(row == 0)
	{
		if(column <= 15)
		{
			address = 0x80 + column;   //Address where lcddata should be printed (0x80 means row=0,column=0) i.e address is from 0x80 to 0x8F
			lcd_cmd(address);
		}
		else
		{
			address = 0x80;
			lcd_cmd(address);
			lcd_printstring("Address ERROR");
		}
	}
	else if(row == 1)
	{
		if(column <= 15)
		{
			address = 0xC0 + column;   //Address where lcddata should be printed (0x80 means row=1,column=0) i.e address is from 0xC0 to 0xCF
			lcd_cmd(address);
		}
		else
		{
			address = 0xC0;
			lcd_cmd(address);
			lcd_printstring("Address ERROR");
		}
	}
	else
	{
		lcd_printstring("Address ERROR");
	}
}

void lcd_printnumber(unsigned int num)   //My own generated function (recieves a number, converts to string & prints it)
{
	unsigned int revnum=0,i,n=0;
	unsigned char str[5];     //NOTE:8051 can only print whole numbers from 0 to 65535(0xFFFF) i.e highest 16-bits number
	
  while(num!=0)
  {
		revnum = revnum*10 + num%10;   //Obtaining the reversed form of given number
    num = num/10;
		n++;      //Counting the number of digits in given number
	}
	
  for(i=0 ; i<n ; i++)
  {
		str[i] = revnum%10 + '0';   //Obtaining string from reversed form of given number
    revnum = revnum/10;
  }
  str[n] = '\0';                //NULL-terminating the string
	
  for (i=0 ; i<n ; i++)      //prints each character of given text/string at a time
	{
		rs = 1;
	  en = 1;
	  P2 = str[i];
	  delay(50);
	  en = 0;
	}
}

void lcd_clearRow(unsigned int row)
{
	unsigned int i;
	if(row==0)    //Clear first row
	{
		lcd_cmd(0x80);
    for (i=1 ; i<=16 ; i++)
    {
			lcd_printstring(" ");   //Use lcd_printstring() to print space i.e lcd_printchar() prints random chars
    }
    lcd_cmd(0x80);
	}
	else if(row==1)   //Clear second row
	{
		lcd_cmd(0xC0);
    for (i=1 ; i<=16 ; i++)
    {
			lcd_printstring(" ");
    }
    lcd_cmd(0xC0);
	}
	else    //Clears All rows i.e clears entire display
	{
		lcd_cmd(0x01);
	}
}

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
	  lcd_printstring("Random Number");
	  lcd_setcursor(1,0);
	  lcd_printnumber(60050);    //NOTE:Can only print whole numbers from 0 to 65535(0xFFFF) i.e highest 16-bits number
		delay(1000);
		
		lcd_clearRow(0);
	  lcd_printstring("Percentage");
		lcd_clearRow(1);
	  lcd_printnumber(85);
		lcd_printchar('%');
		delay(1000);
	}
}