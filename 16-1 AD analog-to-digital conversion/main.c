#include "Delay.h"

unsigned int ADValue = 0;

void main()
{
	LCD_Init();
	LCD_ShowString(1, 1, "ADJ NTC RG");
	while (1)
	{
		ADValue = XPT2046_ReadAD(XPT2046_XP_8);
		LCD_ShowNum(2, 1, ADValue, 3);
		Delay(10);
		ADValue = XPT2046_ReadAD(XPT2046_YP_8);
		LCD_ShowNum(2, 5, ADValue, 3);
		Delay(10);
		ADValue = XPT2046_ReadAD(XPT2046_VBAT_8);
		LCD_ShowNum(2, 9, ADValue, 3);
		Delay(10);
	}
}