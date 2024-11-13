#include "Delay.h"

void main()
{
	int KeyNum = 0;
	int LedMode = 0;
	//Timer0Init();
	while(1)
	{
		KeyNum=IndependentKey();
		if(KeyNum)
		{
			if(KeyNum==1)P2_1=~P2_1;
			if(KeyNum==2)P2_2=~P2_2;
			if(KeyNum==3)P2_3=~P2_3;
			if(KeyNum==4)P2_4=~P2_4;

		}
	}
}

//void Timer0_Routine() interrupt 1 //定时器T0的中断程序命名，这是标准定义，不能随意更改
//{
//	static unsigned int T0Count;
//	TH0=0xFC;//每次计时计完后需要重新赋初值，若
//	TL0=0x18;//不赋初值，它会默认重0开始计时
//	T0Count++;
//	if(T0Count>=1000)
//	{
//		T0Count=0;
//		P2_0=~P2_0;	
//	}
//}