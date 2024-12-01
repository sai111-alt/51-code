#include "Delay.h"

float T = 0;

void main()
{
	DS18B20_ConvertT(); // 上电进行温度显示时，它会首先显示芯片里的默认值，所以提前转换，可以使开机时便可显示当前温度值
	Delay(1000);

	LCD_Init();
	LCD_ShowString(1, 1, "Temperature:");

	while (1)
	{
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		if (T < 0)
		{
			LCD_ShowChar(2, 1, '-');
		}
		else
		{
			LCD_ShowChar(2, 1, '+');
		}
		LCD_ShowNum(2, 2, T, 3);
		LCD_ShowChar(2, 5, '.');

		// 这里float T是以10进制进行显示，所以将T*10000再强转为long，因为float不能进行取余操作，
		// 最后再%10000取出其后4位小数数值
		LCD_ShowNum(2, 6, (unsigned long)(T * 10000) % 10000, 4);
	}
}