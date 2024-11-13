#include "Delay.h"
#include <INTRINS.H>

int LedMode = 0;

void main()
{
	int KeyNum = 0;
	P2 = 0xFE;
	Timer0Init();
	while (1)
	{
		KeyNum = IndependentKey();
		if (KeyNum)
		{
			LedMode++;
			if (LedMode >= 2)
			{
				LedMode = 0;
			}
		}
	}
}

void Timer0_Routine() interrupt 1 // 定时器T0的中断程序命名，这是标准定义，不能随意更改
{
	static unsigned int T0Count;
	TH0 = 0xFC; // 每次计时计完后需要重新赋初值，若
	TL0 = 0x18; // 不赋初值，它会默认重0开始计时
	T0Count++;
	if (T0Count >= 1000)
	{
		T0Count = 0;
		if (LedMode == 0)
		{
			P2 = _crol_(P2, 1);
		}
		if (LedMode == 1)
		{
			P2 = _cror_(P2, 1);
		}
	}
}