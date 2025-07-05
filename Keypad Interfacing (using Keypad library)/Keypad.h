//#include <reg51.h>

//unsigned int keypad_port=3;
//unsigned int keypad_totalrows=4,keypad_totalcolumnns=3;
//unsigned int keypad_rowpins[]={4,5,6,7};
//unsigned int keypad_columnpins[]={0,1,2};
//unsigned char keys[4][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};

//#include "Keypad.h"

int checkkeypad();      //Checks Keypad pins to detect whether a key is pressed (if yes it returns 1,else it returns 0)
char getkey();      //It returns the value corresponding to a particular pressed key

int checkkeypad()
{
	unsigned int i,j,k;
	unsigned int detect=0;
	
	if(keypad_port == 0)     /*PORT 0*/
	{
		for(i=0 ; i<keypad_totalrows ; i++)
		{
			P0 &= ~(1<<keypad_rowpins[i]);     //Set '0' to only one row at a time
			for(j=0 ; j<keypad_totalrows ; j++)
			{
				if(i != j)
				{
					P0 |= (1<<keypad_rowpins[j]);     //Set '1' to all others rows at a time
				}
				else
				{
					continue;
				}
			}
			
			for(k=0 ; k<keypad_totalcolumnns ; k++)
			{
				if((P0 & (1<<keypad_columnpins[k])) == 0)     //Searching for '0' in each column one by one
				{
					detect=1;
					while((P0 & (1<<keypad_columnpins[k])) == 0)
					{
						//Do nothing
					}
					break;
				}
			}
		}
	}
	else if(keypad_port == 1)     /*PORT 1*/
	{
		for(i=0 ; i<keypad_totalrows ; i++)
		{
			P1 &= ~(1<<keypad_rowpins[i]);     //Set '0' to only one row at a time
			for(j=0 ; j<keypad_totalrows ; j++)
			{
				if(i != j)
				{
					P1 |= (1<<keypad_rowpins[j]);     //Set '1' to all others rows at a time
				}
				else
				{
					continue;
				}
			}
			
			for(k=0 ; k<keypad_totalcolumnns ; k++)
			{
				if((P1 & (1<<keypad_columnpins[k])) == 0)     //Searching for '0' in each column one by one
				{
					detect=1;
					while((P1 & (1<<keypad_columnpins[k])) == 0)
					{
						//Do nothing
					}
					break;
				}
			}
		}
	}
	else if(keypad_port == 2)     /*PORT 2*/
	{
		for(i=0 ; i<keypad_totalrows ; i++)
		{
			P2 &= ~(1<<keypad_rowpins[i]);     //Set '0' to only one row at a time
			for(j=0 ; j<keypad_totalrows ; j++)
			{
				if(i != j)
				{
					P2 |= (1<<keypad_rowpins[j]);     //Set '1' to all others rows at a time
				}
				else
				{
					continue;
				}
			}
			
			for(k=0 ; k<keypad_totalcolumnns ; k++)
			{
				if((P2 & (1<<keypad_columnpins[k])) == 0)     //Searching for '0' in each column one by one
				{
					detect=1;
					while((P2 & (1<<keypad_columnpins[k])) == 0)
					{
						//Do nothing
					}
					break;
				}
			}
		}
	}
	else if(keypad_port == 3)     /*PORT 3*/
	{
		for(i=0 ; i<keypad_totalrows ; i++)
		{
			P3 &= ~(1<<keypad_rowpins[i]);     //Set '0' to only one row at a time
			for(j=0 ; j<keypad_totalrows ; j++)
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
			
			for(k=0 ; k<keypad_totalcolumnns ; k++)
			{
				if((P3 & (1<<keypad_columnpins[k])) == 0)     //Searching for '0' in each column one by one
				{
					detect=1;
					while((P3 & (1<<keypad_columnpins[k])) == 0)
					{
						//Do nothing
					}
					break;
				}
			}
		}
	}
	else
	{
		//Do nothing
	}
	return detect;
}


char getkey()
{
	unsigned int i,j,k;
	unsigned char key_x;
	
	if(keypad_port == 0)     /*PORT 0*/
	{
		for(i=0 ; i<keypad_totalrows ; i++)
		{
			P0 &= ~(1<<keypad_rowpins[i]);     //Set '0' to only one row at a time
			for(j=0 ; j<keypad_totalrows ; j++)
			{
				if(i != j)
				{
					P0 |= (1<<keypad_rowpins[j]);     //Set '1' to all others rows at a time
				}
				else
				{
					continue;
				}
			}
			
			for(k=0 ; k<keypad_totalcolumnns ; k++)
			{
				if((P0 & (1<<keypad_columnpins[k])) == 0)     //Searching for '0' in each column one by one
				{
					key_x = keys[i][k];
					break;
				}
			}
		}
	}
	else if(keypad_port == 1)     /*PORT 1*/
	{
		for(i=0 ; i<keypad_totalrows ; i++)
		{
			P1 &= ~(1<<keypad_rowpins[i]);     //Set '0' to only one row at a time
			for(j=0 ; j<keypad_totalrows ; j++)
			{
				if(i != j)
				{
					P1 |= (1<<keypad_rowpins[j]);     //Set '1' to all others rows at a time
				}
				else
				{
					continue;
				}
			}
			
			for(k=0 ; k<keypad_totalcolumnns ; k++)
			{
				if((P1 & (1<<keypad_columnpins[k])) == 0)     //Searching for '0' in each column one by one
				{
					key_x = keys[i][k];
					break;
				}
			}
		}
	}
	else if(keypad_port == 2)     /*PORT 2*/
	{
		for(i=0 ; i<keypad_totalrows ; i++)
		{
			P2 &= ~(1<<keypad_rowpins[i]);     //Set '0' to only one row at a time
			for(j=0 ; j<keypad_totalrows ; j++)
			{
				if(i != j)
				{
					P2 |= (1<<keypad_rowpins[j]);     //Set '1' to all others rows at a time
				}
				else
				{
					continue;
				}
			}
			
			for(k=0 ; k<keypad_totalcolumnns ; k++)
			{
				if((P2 & (1<<keypad_columnpins[k])) == 0)     //Searching for '0' in each column one by one
				{
					key_x = keys[i][k];
					break;
				}
			}
		}
	}
	else if(keypad_port == 3)     /*PORT 3*/
	{
		for(i=0 ; i<keypad_totalrows ; i++)
		{
			P3 &= ~(1<<keypad_rowpins[i]);     //Set '0' to only one row at a time
			for(j=0 ; j<keypad_totalrows ; j++)
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
			
			for(k=0 ; k<keypad_totalcolumnns ; k++)
			{
				if((P3 & (1<<keypad_columnpins[k])) == 0)     //Searching for '0' in each column one by one
				{
					key_x = keys[i][k];
					break;
				}
			}
		}
	}
	else
	{
		//Do nothing
	}
	
	return key_x;
}