#include "Delay.h"

void main()
{
	int KeyNum = 0;
	unsigned int Password = 0;
	unsigned int Count = 0;
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	while(1)
	{
		KeyNum = MatrixKeyboard();
		if(KeyNum)
		{
			if(KeyNum <= 10)//按s1-s10，输入密码
			{
				if(Count < 4)
				{
					Password*=10;//每次密码左移1位
					Password+=KeyNum%10;//每次获取1位密码
					Count++;//计数，只能按4次
				}
				LCD_ShowNum(2,1,Password,4);//输出显示
			}
			if(KeyNum == 11)//进行密码确定
			{
				if(Password == 2345)
				{
					LCD_ShowString(1,14,"OK ");
					Password = 0;
					Count = 0;//两者清零以重新输入密码
					LCD_ShowNum(2,1,Password,4);//输出显示
				}
				else
				{
					LCD_ShowString(1,14,"ERR");
					Password = 0;
					Count = 0;
					LCD_ShowNum(2,1,Password,4);
				}
			} 
			if(KeyNum == 12)//取消输入
			{
				Password = 0;
				Count = 0;
				LCD_ShowNum(2,1,Password,4);
			}
		}
	}
}


