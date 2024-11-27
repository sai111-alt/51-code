#include "Delay.h"

sbit Motor = P1 ^ 0;

unsigned char Counter = 0;
unsigned char Compare = 0;
unsigned char KeyNum = 0;
unsigned char Speed = 0;

void main()
{
	Timer0Init();
	Compare = 5;
	while (1)
	{
		KeyNum = IndependentKey();
		if (KeyNum == 1)
		{
			Speed++;
			Speed %= 4; // 相当于if(Speed>=4){Speed=0;}
			if (Speed == 0)
			{
				Compare = 0;
			}
			if (Speed == 1)
			{
				Compare = 50;
			}
			if (Speed == 2)
			{
				Compare = 75;
			}
			if (Speed == 3)
			{
				Compare = 100;
			}
		}
		NixieTube(1, Speed);
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
		Motor = 1;
	}
	else
	{
		Motor = 0;
	}
}