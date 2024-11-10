#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

void main()
{
  int x;
	
	LCD_Init();
	
//	x=1+1;
//	LCD_ShowNum(1,1,x,4);
	
	//调式
//	LCD_ShowChar(1,1,'A');//表示在第一行第一列为起始位置开始显示A
//	LCD_ShowString(1,3,"Hello");//表示在第一行第一列为起始位置开始显示hello
//	LCD_ShowNum(1,9,123,4);//123是显示的数字，最后一个3是显示位数，若为4，则高位补0，显示为0123
//	LCD_ShowSignedNum(1,14,-66,2);//2也是表示位数，不包括负号
//	LCD_ShowHexNum(2,1,0xA8,2);
//	LCD_ShowBinNum(2,4,0xAA,8);

	
	while(1)
	{
		x++;
		Delay(1000);
		LCD_ShowNum(1,1,x,3);
	}
}