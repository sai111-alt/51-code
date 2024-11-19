#include "Delay.h"

unsigned char KeyNum = 0;
unsigned char MODE = 0;
unsigned char TimeSetSelect = 0;
unsigned char TimeSetFlashFlag = 0;

void TimeShow(void)
{
	DS1302_ReadTime();
	LCD_ShowNum(1, 1, DS1302_Time[0], 2);
	LCD_ShowNum(1, 4, DS1302_Time[1], 2);
	LCD_ShowNum(1, 7, DS1302_Time[2], 2);
	LCD_ShowNum(2, 1, DS1302_Time[3], 2);
	LCD_ShowNum(2, 4, DS1302_Time[4], 2);
	LCD_ShowNum(2, 7, DS1302_Time[5], 2);
}

void TimeSet(void)
{
	if (KeyNum == 2)
	{
		TimeSetSelect++;
		if(TimeSetSelect>5)
		{
			TimeSetSelect = 0;
		}
	}
	if (KeyNum == 3)
	{
		DS1302_Time[TimeSetSelect]++;
		//年月日时分秒的加加越界判断
		if(DS1302_Time[0]>99) {DS1302_Time[0] = 0;}
		if(DS1302_Time[1]>12) {DS1302_Time[1] = 1;}

		if (DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time[1] == 5 ||
			DS1302_Time[1] == 7 || DS1302_Time[1] == 8 || DS1302_Time[1] == 10 ||
			DS1302_Time[1] == 12)
		{
			if(DS1302_Time[2]>31) {DS1302_Time[2] = 1;}
		}
		else if (DS1302_Time[1] == 4 || DS1302_Time[1] == 6 || DS1302_Time[1] == 9 ||
				 DS1302_Time[1] == 11)
		{
			if(DS1302_Time[2]>30) {DS1302_Time[2] = 1;}
		}
		else if (DS1302_Time[1] == 2)
		{
			if ((DS1302_Time[0] % 4 == 0) && (DS1302_Time[0] % 100 != 0) || (DS1302_Time[0] % 400 == 0)) // 判断是否是闰年
			{
				if (DS1302_Time[2] > 29) {DS1302_Time[2] = 1;}
			}
			else
			{
				if (DS1302_Time[2] > 28) {DS1302_Time[2] = 1;}
			}
			
		}

		if(DS1302_Time[3]>23) {DS1302_Time[3] = 0;}
		if(DS1302_Time[4]>59) {DS1302_Time[4] = 0;}
		if(DS1302_Time[5]>59) {DS1302_Time[5] = 0;}
	}
	if (KeyNum == 4)
	{
		DS1302_Time[TimeSetSelect]--;
		//年月日时分秒的减减越界判断
		if(DS1302_Time[0]<0) {DS1302_Time[0] = 99;}
		if(DS1302_Time[1]<1) {DS1302_Time[1] = 12;}

		if (DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time[1] == 5 ||
			DS1302_Time[1] == 7 || DS1302_Time[1] == 8 || DS1302_Time[1] == 10 ||
			DS1302_Time[1] == 12)
		{
			if(DS1302_Time[2]<1) {DS1302_Time[2] = 31;}
			if(DS1302_Time[2]>31) {DS1302_Time[2] = 1;}

		}
		else if (DS1302_Time[1] == 4 || DS1302_Time[1] == 6 || DS1302_Time[1] == 9 ||
				 DS1302_Time[1] == 11)
		{
			if(DS1302_Time[2]<1) {DS1302_Time[2] = 30;}
			if(DS1302_Time[2]>30) {DS1302_Time[2] = 1;}

		}
		else if (DS1302_Time[1] == 2)
		{
			if ((DS1302_Time[0] % 4 == 0) && (DS1302_Time[0] % 100 != 0) || (DS1302_Time[0] % 400 == 0)) // 判断是否是闰年
			{
				if (DS1302_Time[2] < 1) {DS1302_Time[2] = 29;}
				if (DS1302_Time[2] > 29) {DS1302_Time[2] = 1;}

			}
			else
			{
				if (DS1302_Time[2] < 1) {DS1302_Time[2] = 28;}
				if (DS1302_Time[2] > 28) {DS1302_Time[2] = 1;}

			}
			
		}

		if( DS1302_Time[3]<0) {DS1302_Time[3] = 23;}
		if(DS1302_Time[4]<0) {DS1302_Time[4] = 59;}
		if(DS1302_Time[5]<0) {DS1302_Time[5] = 59;}
	}
	if(TimeSetSelect==0 && TimeSetFlashFlag==1) {LCD_ShowString(1, 1, "  ");}
	else {LCD_ShowNum(1, 1, DS1302_Time[0], 2);}
	if(TimeSetSelect==1 && TimeSetFlashFlag==1) {LCD_ShowString(1, 4, "  ");}
	else {LCD_ShowNum(1, 4, DS1302_Time[1], 2);}
	if(TimeSetSelect==2 && TimeSetFlashFlag==1) {LCD_ShowString(1, 7, "  ");}
	else {LCD_ShowNum(1, 7, DS1302_Time[2], 2);}
	if(TimeSetSelect==3 && TimeSetFlashFlag==1) {LCD_ShowString(2, 1, "  ");}
	else {LCD_ShowNum(2, 1, DS1302_Time[3], 2);}
	if(TimeSetSelect==4 && TimeSetFlashFlag==1) {LCD_ShowString(2, 4, "  ");}
	else {LCD_ShowNum(2, 4, DS1302_Time[4], 2);}
	if(TimeSetSelect==5 && TimeSetFlashFlag==1) {LCD_ShowString(2, 7, "  ");}
	else {LCD_ShowNum(2, 7, DS1302_Time[5], 2);}
	
	//LCD_ShowNum(2, 10, TimeSetSelect, 2);
	//LCD_ShowNum(2, 13, TimeSetFlashFlag, 2);
}

void main()
{
	LCD_Init();
	DS1302_Init();
	Timer0Init();

	LCD_ShowString(1, 1, "  -  -");
	LCD_ShowString(2, 1, "  :  :");

	DS1302_WriteByte(DS1302_WP, 0X00); // 关闭写保护，以使函数DS1302_WriteByte能成功写入数据

	DS1302_SetTime();

	while (1)
	{
		KeyNum = IndependentKey();
		if(KeyNum==1)//按键1负责对MODE进行模式翻转，0变1，或1变0
		{
			if (MODE==0)
			{
				MODE = 1;
				TimeSetSelect = 0;//每次重新进入时间设置都是从年开始
			}
			else if(MODE==1)
			{
				MODE = 0;
				DS1302_SetTime();//这里模式1设置好后，切换到0时需将数组数据重新写入DS1302
			}
			
		}
		switch (MODE)
		{
		case 0:
			TimeShow();
			break;
		case 1:
			TimeSet();
			break;
		}

		
	}
}

void Timer0_Routine() interrupt 1 // 定时器T0的中断程序函数命名随意，interrupt 1用于将此函数定义为定时器0的中断程序
{
	static unsigned int T0Count; // 静态变量使得该变量出了此函数仍然不会被销毁
	TH0 = 0xFE;					 // 每次计时计完后需要重新赋初值，若
	TL0 = 0x0C;	 				 // 不赋初值，它会默认重0开始计时,这里设置的时每隔0.5ms执行一次中断
	T0Count++;
	if (T0Count >= 1000)
	{
		T0Count = 0;
		TimeSetFlashFlag = !TimeSetFlashFlag;//这里是逻辑取反，非0即1
	}
}