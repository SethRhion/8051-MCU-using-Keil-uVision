#include<reg51.h>

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
void main()
{
	while(1)
	{
		P3 = 0xAA;
		delay(500);
		P3 = 0x55;
		delay(500);
	}
}