//#include <reg51.h>
//#include "delay.h"

//unsigned int lcd_port;      //Specify Port used for rs,en,datapins as global variable
//sbit en = P1^1;,sbit rs = P1^0;     //Specify rs and en pins as global variable

//#include "LCD.h"

void lcd_cmd(unsigned char abc);          //Funtion for sending commands to LCD display
void lcd_init();              //Initialises the LCD Display and sets rs,en,datapins as Output
void lcd_clear();             //Clears the entire LCD Display
void lcd_setcursor(unsigned int row, unsigned int column);
void lcd_printchar(unsigned char abc);          //Prints a single character i.e %,&,*,'a','1'
void lcd_printstring(unsigned char text[]);     //Prints a string  e.g "Hello"
void lcd_printnumber(unsigned int num);         //Prints a whole number  e.g 1,5000,123567
void lcd_printnumberXdigits(unsigned int num,unsigned int digits);      //Prints a whole number in specified digits  e.g 1,5000,123567
void lcd_clearRow(unsigned int row);        //Clears a single row 'x' of the LCD Display

void lcd_cmd(unsigned char abc)  //Funtion for sending commands to LCD display
{
	rs = 0;
	en = 1;
	switch(lcd_port)
	{
		case 0:
			P0 = abc; break;
		case 1:
			P1 = abc; break;
		case 2:
			P2 = abc; break;
		case 3:
			P3 = abc; break;
		default:
			P0 = abc; break;
	}
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
	switch(lcd_port)
	{
		case 0:
			P0 = abc; break;
		case 1:
			P1 = abc; break;
		case 2:
			P2 = abc; break;
		case 3:
			P3 = abc; break;
		default:
			P0 = abc; break;
	}
	delay(50);
	en = 0;
	/*End of lcd_printchar() function*/
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
	  switch(lcd_port)
		{
			case 0:
				P0 = text[i]; break;
			case 1:
				P1 = text[i]; break;
			case 2:
				P2 = text[i]; break;
			case 3:
				P3 = text[i]; break;
			default:
				P0 = text[i]; break;
		}
	  delay(50);
	  en = 0;
	}
	/*End of lcd_printstring() function*/
}

void lcd_clear()
{
	lcd_cmd(0x01);   //clear display
	/*End of lcd_clear() function*/
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
	/*End of lcd_setcursor() function*/
}

void lcd_printnumber(unsigned int num)   //My own generated function (recieves a number, converts to string & prints it)
{
	unsigned int revnum=0,i,n=0;
	unsigned char str[5];     //NOTE:8051 can only print whole numbers from 0 to 65535(0xFFFF) i.e highest 16-bits number
	
  if(num==0)
	{
		lcd_printchar('0');
	}
	else
	{
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
			switch(lcd_port)
			{
				case 0:
					P0 = str[i]; break;
				case 1:
					P1 = str[i]; break;
				case 2:
					P2 = str[i]; break;
				case 3:
					P3 = str[i]; break;
				default:
					P0 = str[i]; break;
			}
			delay(50);
			en = 0;
		}
	}
	/*End of lcd_printnumber() function*/
}

void lcd_printnumberXdigits(unsigned int num,unsigned int digits)
{
	unsigned int n=0,temp=num,revnum,i,zeros,x=1,pow;
	
  if(num==0)
	{
		for(i=0; i<digits ; i++)
		{
			lcd_printchar('0');    //prints only zeros
		}
	}
	else
	{
		while(temp!=0)
		{
			revnum = revnum*10 + temp%10;   //Obtaining the reversed form of given number
			temp = temp/10;
			n++;      //Counting the number of digits in given number
		}
		
		if(n<=digits)   //digits required is equal to or more than digits in given number
		{
			zeros = digits-n;
			for(i=0; i<zeros ; i++)
			{
				lcd_printchar('0');   //prints zeros before actual number
			}
			lcd_printnumber(num);
		}
		else   //digits required is less than digits in given number
		{
			pow = n-digits;    //Find the powers of 10
			while(pow>0)
			{
				x = x*10;    //Calculates: 10^pow
				pow--;
			}
			temp = num/x;    //num divide by 10^pow
			lcd_printnumber(temp);    //prints more significant digits
		}
	}
	/*End of lcd_printnumberXdigits() function*/
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
	/*End of lcd_clearRow() function*/
}