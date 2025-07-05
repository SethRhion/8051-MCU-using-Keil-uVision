//#include <reg51.h>
//#include "delay.h"

//sbit SCL = P3^0;
//sbit SDA = P3^1;

//#include "I2C.h"

//#include "DS1307.h"

/* Below given values are fixed and should not be changed.
    Refer Ds1307 DataSheet for more info*/ 
#define DS1307_ID 0xD0     // ds1307 ID
#define SEC_ADDRESS   0x00 // address to access ds1307 SEC register
#define MIN_ADDRESS   0x01 // address to access ds1307 MIN register
#define HOUR_ADDRESS  0x02 // address to access ds1307 HOUR register
#define DAY_ADDRESS   0x03 // address to access ds1307 DAY register
#define DATE_ADDRESS  0x04 // address to access ds1307 DATE register
#define MONTH_ADDRESS   0x05 // address to access ds1307 MONTH register
#define YEAR_ADDRESS   0x06 // address to access ds1307 YEAR register
#define control       0x07 // address to access ds1307 CONTROL register

void ds1307_Init();
void ds1307_SetTime(unsigned char hh, unsigned char mm, unsigned char ss);
void ds1307_Set24Hour(unsigned char hh);
void ds1307_Set12Hour(unsigned char hh,unsigned char am_pm);
void ds1307_SetMin(unsigned char mm);
void ds1307_SetDayOfWeek(unsigned char day);
void ds1307_SetDate(unsigned char dd, unsigned char mm, unsigned char yy);
void ds1307_SetDay(unsigned char dd);
void ds1307_SetMonth(unsigned char mm);
void ds1307_SetYear(unsigned char yy);

unsigned int decimalToBCDdec(unsigned int num);
void ds1307_GetTime(unsigned char *h_ptr,unsigned char *m_ptr,unsigned char *s_ptr);
void ds1307_GetHour(unsigned char *h_ptr, unsigned char *format);
void ds1307_GetMin(unsigned char *m_ptr);
void ds1307_GetDate(unsigned char *d_ptr,unsigned char *m_ptr,unsigned char *y_ptr);
void ds1307_GetDay(unsigned char *d_ptr);
void ds1307_GetMonth(unsigned char *m_ptr);
void ds1307_GetYear(unsigned char *y_ptr);

/*Function to convert two-digit binary number to BCD-decimal*/
unsigned int decimalToBCDdec(unsigned int num)
{
    unsigned int m = num,n;
    unsigned int a[8]={0,0,0,0,0,0,0,0};
    unsigned int BCD=0,power,x;
    unsigned int i=7,j,k;

    while(m > 0)
    {
        n = m%10;
        m = m/10;

        while(n > 0)
        {
            a[i] = n%2;
            n = n/2;
            i--;
        }

        i=3;
    }

    for(j=0; j<8 ; j++)
    {
        power=7-j;
        x=1;
        for(k=0; k<power ; k++)
        {
            x = x*2;
        }
        BCD = BCD + (x*a[j]);
    }

    return BCD;
}


/*Functions to Set values into DS1307*/
/*ds1307 initilization*/
void ds1307_Init()
{
	I2C_start();        // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(control);
	I2C_datawrite(0x00);
	
	I2C_stop();
}

/*Function to Set time entirely*/
void ds1307_SetTime(unsigned char hh, unsigned char mm, unsigned char ss)
{
	I2C_start();            // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(SEC_ADDRESS);
	I2C_datawrite(decimalToBCDdec(ss));
	I2C_datawrite(decimalToBCDdec(mm));
	I2C_datawrite(decimalToBCDdec(hh));
	
	I2C_stop();             // Stop i2c communication after Setting the Time
}

/*Function to Set time hours only in 24-hour format*/
void ds1307_Set24Hour(unsigned char hh)
{
	I2C_start();            // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(HOUR_ADDRESS);
	I2C_datawrite(decimalToBCDdec(hh));
	
	I2C_stop();             // Stop i2c communication after Setting the Time
}

/*Function to Set time hours only in 12-hour format*/
void ds1307_Set12Hour(unsigned char hh,unsigned char am_pm)
{
	if(am_pm=='A' || am_pm=='a')
	{
		I2C_start();            // Start i2c communication
		
		I2C_datawrite(DS1307_ID);
		I2C_datawrite(HOUR_ADDRESS);
		I2C_datawrite((decimalToBCDdec(hh)) | 0x40);   //010X-XXXX i.e AM
		
		I2C_stop();             // Stop i2c communication after Setting the Time
	}
	else if(am_pm=='P' || am_pm=='p')
	{
		I2C_start();            // Start i2c communication
		
		I2C_datawrite(DS1307_ID);
		I2C_datawrite(HOUR_ADDRESS);
		I2C_datawrite((decimalToBCDdec(hh)) | 0x60);   //011X-XXXX i.e PM
		
		I2C_stop();             // Stop i2c communication after Setting the Time
	}
}

/*Function to Set time minutes only*/
void ds1307_SetMin(unsigned char mm)
{
	I2C_start();            // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(MIN_ADDRESS);
	I2C_datawrite(decimalToBCDdec(mm));
	
	I2C_stop();             // Stop i2c communication after Setting the Time
}

/*Function to Set Day of the week only*/
void ds1307_SetDayOfWeek(unsigned char day)
{
	I2C_start();            // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(DAY_ADDRESS);
	I2C_datawrite(day);     //No need of BCD conversion
	
	I2C_stop();             // Stop i2c communication after Setting the Date
}

/*Function to Set Date entirely*/
void ds1307_SetDate(unsigned char dd, unsigned char mm, unsigned char yy)
{
	I2C_start();            // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(DATE_ADDRESS);
	I2C_datawrite(decimalToBCDdec(dd));
	I2C_datawrite(decimalToBCDdec(mm));
	I2C_datawrite(decimalToBCDdec(yy));
	
	I2C_stop();             // Stop i2c communication after Setting the Date
}

/*Function to Set Date only*/
void ds1307_SetDay(unsigned char dd)
{
	I2C_start();            // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(DATE_ADDRESS);
	I2C_datawrite(decimalToBCDdec(dd));
	
	I2C_stop();             // Stop i2c communication after Setting the Date
}

/*Function to Set Month only*/
void ds1307_SetMonth(unsigned char mm)
{
	I2C_start();            // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(MONTH_ADDRESS);
	I2C_datawrite(decimalToBCDdec(mm));
	
	I2C_stop();             // Stop i2c communication after Setting the Date
}

/*Function to Set Year only*/
void ds1307_SetYear(unsigned char yy)
{
	I2C_start();            // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(YEAR_ADDRESS);
	I2C_datawrite(decimalToBCDdec(yy));
	
	I2C_stop();             // Stop i2c communication after Setting the Date
}
/*End of Setting Functions*/


/*Functions to Get values from DS1307*/
/*Function to Get entire Time details*/
void ds1307_GetTime(unsigned char *h_ptr,unsigned char *m_ptr,unsigned char *s_ptr)
{
	unsigned int temp;
	I2C_start();           // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(SEC_ADDRESS);
	
	I2C_stop();
	
	I2C_start();
	
	I2C_datawrite(0xD1);
	temp = I2C_dataread();                   //Read hex value of sec from RTC
	*s_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of sec into decimal form
	I2C_Ack();
	temp = I2C_dataread();                   //Read hex value of min from RTC
	*m_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of min into decimal form
	I2C_Ack();
	temp = I2C_dataread();                   //Read hex value of hour from RTC
	*h_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of hour into decimal form
	I2C_NoAck();
	
	I2C_stop();               // stop i2c communication after reading the Time
}

/*Function to Get Time hour only*/
void ds1307_GetHour(unsigned char *h_ptr, unsigned char *format)
{
	unsigned int temp;
	I2C_start();           // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(HOUR_ADDRESS);
	
	I2C_stop();
	
	I2C_start();
	
	I2C_datawrite(0xD1);
	temp = I2C_dataread();                   //Read hex value of hour from RTC
	I2C_NoAck();
	
	I2C_stop();               // stop i2c communication after reading the Time
	
	if(temp < 0x40)   //Time is in 24-Hour Format
	{
		*h_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of hour into decimal form
		*format = '0';
	}
	else if((temp>=0x40) && (temp<=0x60))   //Time is in 12-Hour Format and in AM
	{
		*h_ptr = (((temp>>4)&0x01)*10)+(temp&0x0F);     //Convert hex value of hour into decimal form
		*format = 'A';
	}
	else if(temp>0x60)   //Time is in 12-Hour Format and in PM
	{
		*h_ptr = (((temp>>4)&0x01)*10)+(temp&0x0F);     //Convert hex value of hour into decimal form
		*format = 'P';
	}
}

/*Function to Get Time minutes only*/
void ds1307_GetMin(unsigned char *m_ptr)
{
	unsigned int temp;
	I2C_start();           // Start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(MIN_ADDRESS);
	
	I2C_stop();
	
	I2C_start();
	
	I2C_datawrite(0xD1);
	temp = I2C_dataread();                   //Read hex value of min from RTC
	*m_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of min into decimal form
	I2C_NoAck();
	
	I2C_stop();               // stop i2c communication after reading the Time
}

/*Function to Get entire Date details*/
void ds1307_GetDate(unsigned char *d_ptr,unsigned char *m_ptr,unsigned char *y_ptr)
{
	unsigned int temp;
	I2C_start();            // start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(DATE_ADDRESS);
	
	I2C_stop();
	
	I2C_start();
	I2C_datawrite(0xD1);
	
	temp = I2C_dataread();                   //Read hex value of date from RTC
	*d_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of date into decimal form
	I2C_Ack();
	temp = I2C_dataread();                   //Read hex value of month from RTC
	*m_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of month into decimal form
	I2C_Ack();
	temp = I2C_dataread();                   //Read hex value of year from RTC
	*y_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of year into decimal form
	I2C_NoAck();
	
	I2C_stop();         // stop i2c communication after reading the Time
}

/*Function to Get Date only*/
void ds1307_GetDay(unsigned char *d_ptr)
{
	unsigned int temp;
	I2C_start();            // start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(DATE_ADDRESS);
	
	I2C_stop();
	
	I2C_start();
	I2C_datawrite(0xD1);
	
	temp = I2C_dataread();                   //Read hex value of date from RTC
	*d_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of date into decimal form
	I2C_NoAck();
	
	I2C_stop();         // stop i2c communication after reading the Time
}

/*Function to Get Month only*/
void ds1307_GetMonth(unsigned char *m_ptr)
{
	unsigned int temp;
	I2C_start();            // start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(MONTH_ADDRESS);
	
	I2C_stop();
	
	I2C_start();
	I2C_datawrite(0xD1);
	
	temp = I2C_dataread();                   //Read hex value of month from RTC
	*m_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of month into decimal form
	I2C_NoAck();
	
	I2C_stop();         // stop i2c communication after reading the Time
}

/*Function to Get Year only*/
void ds1307_GetYear(unsigned char *y_ptr)
{
	unsigned int temp;
	I2C_start();            // start i2c communication
	
	I2C_datawrite(DS1307_ID);
	I2C_datawrite(YEAR_ADDRESS);
	
	I2C_stop();
	
	I2C_start();
	I2C_datawrite(0xD1);
	
	temp = I2C_dataread();                   //Read hex value of year from RTC
	*y_ptr = ((temp>>4)*10)+(temp&0x0F);     //Convert hex value of year into decimal form
	I2C_NoAck();
	
	I2C_stop();         // stop i2c communication after reading the Time
}
/*End of Getting Functions*/