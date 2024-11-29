#include "Delay.h"

unsigned char Num = 0;
unsigned char Address = 0;
unsigned char Command = 0;

void main()
{
	LCD_Init();
	IR_Init();

	LCD_ShowString(1, 1, "ADDR  CMD  NUM");
	LCD_ShowString(2, 1, "00    00   00");

	while (1)
	{
		if (IR_GetDataFlag() || IR_GetRepeatFlag())
		{
			Address = IR_GetAddress();
			Command = IR_GetCommand();
			LCD_ShowHexNum(2, 1, Address, 2);
			LCD_ShowHexNum(2, 7, Command, 2);
			if (Command == IR_VOL_MINUS)
			{
				Num--;
			}
			if (Command == IR_VOL_ADD)
			{
				Num++;
			}
			LCD_ShowNum(2, 12, Num, 3);
		}
	}
}
