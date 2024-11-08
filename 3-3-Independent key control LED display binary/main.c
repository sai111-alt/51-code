#include <REGX52.H>

void Delay(unsigned int xms)	//@12MHz
{
	unsigned char data i, j;

	while(xms--)
	{
		i = 2;
		j = 239;
		do 
		{
			while (--j);
		} while (--i);
		}
}

void main()
{
	unsigned char LEDNum;
	while(1)
	{
		if(P3_1==0)
		{
			Delay(20);
			while(P3_1==0);
			Delay(20);
			
			LEDNum++;
			P2=~LEDNum;
		}
	}
}