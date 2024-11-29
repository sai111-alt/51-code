#include "Delay.h"
#include "Timer0.h"

unsigned char Num = 0;

void main()
{
	LCD_Init();
	Int0_Init();
	LCD_ShowString(1, 1, "A");

	while (1)
	{
		LCD_ShowNum(2, 1, Num, 3);
	}
}

void Int0_Routine(void) interrupt 0
{
	Num--;
}