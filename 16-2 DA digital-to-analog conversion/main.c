#include "Delay.h"

sbit DA = P2 ^ 1;

unsigned char Counter = 0;
unsigned char Compare = 0;
unsigned char i = 0;

void main()
{
	Timer0Init();
	Compare = 5;
	while (1)
	{
		for (i = 0; i < 100; i++)
		{
			Compare = i;
			Delay(10);
		}
		for (i = 100; i > 0; i--)
		{
			Compare = i;
			Delay(10);
		}
	}
}

void Timer0_Routine() interrupt 1
{
	TL0 = 0x9C; // 设置定时初始值
	TH0 = 0xFF; // 设置定时初始值
	Counter++;

	// 这里还可以用Counter%=100代替该if语句，两者效果相同
	if (Counter >= 100)
	{
		Counter = 0;
	}

	// 产生PWM
	if (Counter < Compare)
	{
		DA = 1;
	}
	else
	{
		DA = 0;
	}
}