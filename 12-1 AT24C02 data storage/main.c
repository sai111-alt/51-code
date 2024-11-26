#include "Delay.h"

unsigned char KeyNum = 0;
unsigned int Num = 0;

void main()
{
	LCD_Init();
	LCD_ShowNum(1, 1, Num, 5);
	while (1)
	{
		KeyNum = IndependentKey();
		if (KeyNum == 1)
		{
			Num++;
			LCD_ShowNum(1, 1, Num, 5);
		}
		if (KeyNum == 2)
		{
			Num--;
			LCD_ShowNum(1, 1, Num, 5);
		}
		if (KeyNum == 3)
		{
			AT24C02_WriterByte(0, Num % 256); // 取出Num的低8位
			Delay(5);
			AT24C02_WriterByte(1, Num / 256); // 取出Num的高8位
			Delay(5);
			LCD_ShowString(2, 1, "Wrtite OK");
			Delay(1000);
			LCD_ShowString(2, 1, "         ");
		}
		if (KeyNum == 4)
		{
			Num = AT24C02_ReadByte(0);
			Num |= AT24C02_ReadByte(1) << 8;
			LCD_ShowNum(1, 1, Num, 5);
			LCD_ShowString(2, 1, "Read OK");
			Delay(1000);
			LCD_ShowString(2, 1, "       ");
		}
	}
}
