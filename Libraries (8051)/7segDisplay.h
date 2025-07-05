//#include <reg51.h>

void displayNum(unsigned int num,unsigned int port);     //Displays given number on 7segDisplay

void displayNum(unsigned int num,unsigned int port)
{
	if(port==0)
	{
		switch(num)
		{
			case 0:
				P0 = 0x3F;  //0b00111111
			  break;
			case 1:
				P0 = 0x06;  //0b00000110
			  break;
			case 2:
				P0 = 0x5B;  //0b01011011
			  break;
			case 3:
				P0 = 0x4F;  //0b01001111
			  break;
			case 4:
				P0 = 0x66;  //0b01100110
			  break;
			case 5:
				P0 = 0x6D;  //0b01101101
			  break;
			case 6:
				P0 = 0x7D;  //0b01111101
			  break;
			case 7:
				P0 = 0x07;  //0b00000111
			  break;
			case 8:
				P0 = 0x7F;  //0b01111111
			  break;
			case 9:
				P0 = 0x6F;  //0b01101111
			  break;
			default:
				P0 = 0x80;  //0b10000000
			  break;
		}
	}
	else if(port==1)
	{
		switch(num)
		{
			case 0:
				P1 = 0x3F;  //0b00111111
			  break;
			case 1:
				P1 = 0x06;  //0b00000110
			  break;
			case 2:
				P1 = 0x5B;  //0b01011011
			  break;
			case 3:
				P1 = 0x4F;  //0b01001111
			  break;
			case 4:
				P1 = 0x66;  //0b01100110
			  break;
			case 5:
				P1 = 0x6D;  //0b01101101
			  break;
			case 6:
				P1 = 0x7D;  //0b01111101
			  break;
			case 7:
				P1 = 0x07;  //0b00000111
			  break;
			case 8:
				P1 = 0x7F;  //0b01111111
			  break;
			case 9:
				P1 = 0x6F;  //0b01101111
			  break;
			default:
				P1 = 0x80;  //0b10000000
			  break;
		}
	}
	else if(port==2)
	{
		switch(num)
		{
			case 0:
				P2 = 0x3F;  //0b00111111
			  break;
			case 1:
				P2 = 0x06;  //0b00000110
			  break;
			case 2:
				P2 = 0x5B;  //0b01011011
			  break;
			case 3:
				P2 = 0x4F;  //0b01001111
			  break;
			case 4:
				P2 = 0x66;  //0b01100110
			  break;
			case 5:
				P2 = 0x6D;  //0b01101101
			  break;
			case 6:
				P2 = 0x7D;  //0b01111101
			  break;
			case 7:
				P2 = 0x07;  //0b00000111
			  break;
			case 8:
				P2 = 0x7F;  //0b01111111
			  break;
			case 9:
				P2 = 0x6F;  //0b01101111
			  break;
			default:
				P2 = 0x80;  //0b10000000
			  break;
		}
	}
	else if(port==3)
	{
		switch(num)
		{
			case 0:
				P3 = 0x3F;  //0b00111111
			  break;
			case 1:
				P3 = 0x06;  //0b00000110
			  break;
			case 2:
				P3 = 0x5B;  //0b01011011
			  break;
			case 3:
				P3 = 0x4F;  //0b01001111
			  break;
			case 4:
				P3 = 0x66;  //0b01100110
			  break;
			case 5:
				P3 = 0x6D;  //0b01101101
			  break;
			case 6:
				P3 = 0x7D;  //0b01111101
			  break;
			case 7:
				P3 = 0x07;  //0b00000111
			  break;
			case 8:
				P3 = 0x7F;  //0b01111111
			  break;
			case 9:
				P3 = 0x6F;  //0b01101111
			  break;
			default:
				P3 = 0x80;  //0b10000000
			  break;
		}
	}
	else
	{
		//do nothing
	}
}