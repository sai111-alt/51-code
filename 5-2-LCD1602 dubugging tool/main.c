#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

void main()
{
  int x;
	
	LCD_Init();
	
//	x=1+1;
//	LCD_ShowNum(1,1,x,4);
	
	//��ʽ
//	LCD_ShowChar(1,1,'A');//��ʾ�ڵ�һ�е�һ��Ϊ��ʼλ�ÿ�ʼ��ʾA
//	LCD_ShowString(1,3,"Hello");//��ʾ�ڵ�һ�е�һ��Ϊ��ʼλ�ÿ�ʼ��ʾhello
//	LCD_ShowNum(1,9,123,4);//123����ʾ�����֣����һ��3����ʾλ������Ϊ4�����λ��0����ʾΪ0123
//	LCD_ShowSignedNum(1,14,-66,2);//2Ҳ�Ǳ�ʾλ��������������
//	LCD_ShowHexNum(2,1,0xA8,2);
//	LCD_ShowBinNum(2,4,0xAA,8);

	
	while(1)
	{
		x++;
		Delay(1000);
		LCD_ShowNum(1,1,x,3);
	}
}