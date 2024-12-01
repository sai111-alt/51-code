#include "Delay.h"

unsigned char Num = 0;
unsigned char Address = 0;
unsigned char Command = 0;

void main()
{
	LCD_Init();
	LCD_ShowChar(1, 1, 'a');
	LCD_ShowString(2, 1, "string");
	LCD_ShowNum(2, 8, 647, 3);
	LCD_ShowSignedNum(2, 12, 123, 4);
	LCD_ShowHexNum(1, 3, 0xA5, 2);
	LCD_ShowBinNum(1, 6, 0xA5, 8);
	LCD_ShowChar(1, 15, 0xDF);
	LCD_ShowChar(1, 16, 'C');
	LCD_ShowString(1, 17, "Welcome to China!");

	while (1)
	{
		LCD_WriteCommand(0x18);
		Delay(750);
	}
}
