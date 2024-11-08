#include <REGX52.H>

void Delay(int xms)	//@12MHz
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
	while(1)
	{
		if(P3_1==0)//判断按键是否按下
		{
			Delay(20);//按键已经按下，此程序进行按键闭合的消抖
			while(P3_1==0);
			Delay(20);//经过while循环判断一直到按键断开，按键断开后，
								//利用此程序进行按键断开的消抖,至此完成按键消抖的一个周期
			P2_0=~P2_0;
		}
	}
}
