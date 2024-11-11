#include "Delay.h"

void main()
{
	int KeyNum = 0;
	LCD_Init();
	LCD_ShowString(1,1,"MatrixKeyboard:");
	while(1)
	{
		KeyNum = MatrixKeyboard();
		if(KeyNum)
		{
			LCD_ShowNum(2,1,KeyNum,2);
		}
	}
}
