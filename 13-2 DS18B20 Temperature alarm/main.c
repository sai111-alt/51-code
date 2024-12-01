#include "Delay.h"

float T = 0;
float TShow = 0;
char TLow = 0;
char THigh = 0;
unsigned char KeyNum = 0;

void main()
{
	THigh = AT24C02_ReadByte(0);
	TLow = AT24C02_ReadByte(1);
	if (THigh > 125 || TLow < -55 || THigh <= TLow)
	{
		THigh = 20;
		TLow = 15;
	}
	DS18B20_ConvertT(); // 上电进行温度显示时，它会首先显示芯片里的默认值，所以提前转换，可以使开机时便可显示当前温度值
	Delay(1000);

	Timer0_Init();
	LCD_Init();
	LCD_ShowString(1, 1, "T:");
	LCD_ShowString(2, 1, "TH:");
	LCD_ShowString(2, 9, "TL:");
	LCD_ShowSignedNum(2, 4, THigh, 3);
	LCD_ShowSignedNum(2, 12, TLow, 3);

	while (1)
	{
		KeyNum = Key();
		/*温度读取与显示*/
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		if (T < 0)
		{
			LCD_ShowChar(1, 3, '-');
			TShow = -T;
		}
		else
		{
			LCD_ShowChar(1, 3, '+');
			TShow = T;
		}
		LCD_ShowNum(1, 4, TShow, 3);
		LCD_ShowChar(1, 7, '.');

		// 这里只显示两位，所以用100即可
		LCD_ShowNum(1, 8, (unsigned long)(TShow * 100) % 100, 2);

		/*温度阈值设置*/
		if (KeyNum)
		{
			if (KeyNum == 1)
			{
				THigh++;
				if (THigh > 125)
				{
					THigh = 125;
				}
			}
			if (KeyNum == 2)
			{
				THigh--;
				if (THigh <= TLow)
				{
					THigh++;
				}
			}
			if (KeyNum == 3)
			{
				TLow++;
				if (TLow >= THigh)
				{
					TLow--;
				}
			}
			if (KeyNum == 4)
			{
				TLow--;
				if (TLow < -55)
				{
					TLow = -55;
				}
			}
			LCD_ShowSignedNum(2, 4, THigh, 3);
			LCD_ShowSignedNum(2, 12, TLow, 3);
			AT24C02_WriterByte(0, THigh);
			Delay(5);
			AT24C02_WriterByte(1, TLow);
			Delay(5);
		}
		if (T > THigh)
		{
			LCD_ShowString(1, 13, "OV:H");
		}
		else if (T < TLow)
		{
			LCD_ShowString(1, 13, "OV:L");
		}
		else
		{
			LCD_ShowString(1, 13, "    ");
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count1;

	TH0 = 0xFC;
	TL0 = 0x18;

	T0Count1++;
	if (T0Count1 >= 20)
	{
		T0Count1 = 0;
		IndependentKey_Loop();
	}
}