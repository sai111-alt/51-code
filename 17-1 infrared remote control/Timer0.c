#include <REGX52.H>

void Timer0Init() // 1ms@12MHz
{
	TMOD &= 0xF0;
	TMOD |= 0x01;

	TF0 = 0;
	TR0 = 1; // 即初始化关闭定时器0计时

	TH0 = 0xFC;
	TL0 = 0x18;
}

// 此函数用于设置定时器的定时时间
void Timer0_SetCounter(unsigned int Value)
{
	TH0 = Value / 256;
	TL0 = Value % 256;
}

// 此函数用于得到定时器计时当前的时间
unsigned int Timer0_GetCounter(void)
{
	return (TH0 << 8) | TL0;
}

// 此函数负责开启和关闭定时器
void Timer0_Run(unsigned char Flag)
{
	TR0 = Flag;
}