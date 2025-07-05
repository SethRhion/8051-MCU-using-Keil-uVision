#include <reg51.h>
#include "7segDisplay.h"
#include "delay.h"

int main()
{
	unsigned int port=2;         //Port connected to 7-seg display
	
	while(1)
	{
		displayNum(0,port);      //display 0
		delay(1000);
		displayNum(1,port);      //display 1
		delay(1000);
		displayNum(2,port);      //display 2
		delay(1000);
		displayNum(3,port);      //display 3
		delay(1000);
		displayNum(4,port);      //display 4
		delay(1000);
		displayNum(5,port);      //display 5
		delay(1000);
		displayNum(6,port);      //display 6
		delay(1000);
		displayNum(7,port);      //display 7
		delay(1000);
		displayNum(8,port);      //display 8
		delay(1000);
		displayNum(9,port);      //display 9
		delay(1000);
		displayNum(10,port);      //display decimal(.)
		delay(1000);
	}
}