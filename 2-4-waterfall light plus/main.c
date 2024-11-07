#include <REGX52.H>

void Delay1ms(unsigned int xms)	//注意单片机中的int类型是16位
{
	unsigned char data i, j;
	while(--xms)
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
	int x = 50;
	while(1)
	{
		P2=0xFE;
		Delay1ms(1000);
		P2=0xFD;
		Delay1ms(1000);
		P2=0xFB;
		Delay1ms(x);
		P2=0xF7;
		Delay1ms(x);
		P2=0xEF;
		Delay1ms(x);
		P2=0xDF;
		Delay1ms(x);
		P2=0xBF;
		Delay1ms(x);
		P2=0x7F;
		Delay1ms(x);
	}
}

