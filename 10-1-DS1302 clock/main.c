#include "Delay.h"


void main()
{
	LCD_Init();
	DS1302_Init();

	LCD_ShowString(1, 1, "  -  -");
	LCD_ShowString(2, 1, "  :  :");

	DS1302_WriteByte(DS1302_WP, 0X00); // 关闭写保护，以使函数DS1302_WriteByte能成功写入数据

	DS1302_SetTime();

	while (1)
	{
		DS1302_ReadTime();
		LCD_ShowNum(1, 1, DS1302_Time[0], 2);
		LCD_ShowNum(1, 4, DS1302_Time[1], 2);
		LCD_ShowNum(1, 7, DS1302_Time[2], 2);
		LCD_ShowNum(2, 1, DS1302_Time[3], 2);
		LCD_ShowNum(2, 4, DS1302_Time[4], 2);
		LCD_ShowNum(2, 7, DS1302_Time[5], 2);
	}
}