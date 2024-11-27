#include "Delay.h"

sbit LED = P2 ^ 0;

void Delay1(unsigned int t)
{
	while (t--)
		;
}

void main()
{
	unsigned char Time;
	unsigned char i;
	while (1)
	{
		for (Time = 0; Time < 100; Time++)
		{
			for (i = 0; i < 20; i++)
			{
				LED = 0;
				Delay1(Time);
				LED = 1;
				Delay1(100 - Time);
			}
		}
		for (Time = 100; Time > 0; Time--)
		{
			for (i = 0; i < 20; i++)
			{
				LED = 0;
				Delay1(Time);
				LED = 1;
				Delay1(100 - Time);
			}
		}
	}
}