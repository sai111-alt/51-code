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
			if(KeyNum <= 10)//��s1-s10����������
			{
				if(Count < 4)
				{
					Password*=10;//ÿ����������1λ
					Password+=KeyNum%10;//ÿ�λ�ȡ1λ����
					Count++;//������ֻ�ܰ�4��
				}
				LCD_ShowNum(2,1,Password,4);//�����ʾ
			}
			if(KeyNum == 11)//��������ȷ��
			{
				if(Password == 2345)
				{
					LCD_ShowString(1,14,"OK ");
					Password = 0;
					Count = 0;//����������������������
					LCD_ShowNum(2,1,Password,4);//�����ʾ
				}
				else
				{
					LCD_ShowString(1,14,"ERR");
					Password = 0;
					Count = 0;
					LCD_ShowNum(2,1,Password,4);
				}
			} 
			if(KeyNum == 12)//ȡ������
			{
				Password = 0;
				Count = 0;
				LCD_ShowNum(2,1,Password,4);
			}
		}
	}
}


