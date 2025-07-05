#include <reg51.h>

void UART_init()
{
	SCON = 0x50;       //(0101 0000) setting mode=1 (variable 8-bit mode), REN=1 (recieve enable)
	TMOD = 0x20;       //timer1 = auto_reload mode (0010 0000)
	TH1 = 0xFD;       //loading  253 to TH1 so as to get 9600 baudrate (formula: TH1 = 255 - ((freq/12)/(32*baudrate)))
	TR1 = 1;         //start timer1
}

void UART_sendchar(unsigned char Data)
{
	SBUF = Data;
	while(TI == 0);     //stay here while transmission is going on
	TI = 0;             //Resetting TI for the next transmission
}

void UART_sendstring(unsigned char text[])
{
  unsigned int n=0, i;
  while(text[n] != '\0')      //calculates number of characters in text/string
  {
      n++;
  }
	
  for (i=0 ; i<n ; i++)       //sends each character of given text/string individually
	{
		SBUF = text[i];
		while(TI == 0);     //stay here while transmission is going on
		TI = 0;             //Resetting TI for the next transmission
	}
}

unsigned char UART_recieve()
{
	while(RI == 0);     //stay here while reception is going on
	RI = 0;             //Resetting RI for the next reception
	return SBUF;       //Returns received data (character)
}

void main()
{
	unsigned char word[] = "Press any key: ";
	unsigned char Data;
	
	UART_init();
	UART_sendstring(word);
	
	while(1)
	{
		Data = UART_recieve();
		UART_sendchar(0x0D);       //Sets to next line in UART terminal
		UART_sendstring("Received Data: ");
		UART_sendchar(Data);
		P1 = Data;
	}
}