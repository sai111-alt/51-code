#include "Delay.h"

void Delay(unsigned int xms) //@12MHz
{
	unsigned char data i, j;

	while (xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j)
				;
		} while (--i);
	}
}


void Timer0Init() // 1ms@12MHz
{
	TMOD &= 0xF0; // 把TMOD的低四位清零，高四位保持不变
	TMOD |= 0x01; // 把TMOD的最低位置1，其他7位保持不变，这里即设置了定时器0的模式是工作方式1：16为计数器
	// 这样做的好处就在于可以只操作TMOD的其中某些位而不影响其他位

	TF0 = 0; // 设置T0定时器溢出标志位为0
	TR0 = 1; // 即启动定时器0开始计时

	TH0 = 0xFC; // 设置定时初始值为64535+1
	TL0 = 0x18;
	// 另一写法
	//	TH0=64535/256;//作用即得到64535转16进制后的高8位，这里除的结果只取整数，不取小数
	//								（结果即十进制的252，转16进制就是FC，刚好就是64535的十六进制高8位）
	//	TL0=64535%256+1;//结果即64535转16进制后的低8位（同理，自己计算），+1是因为定时器
	// 最大定时为65535，而定时器要到65536才溢出，所以64535到65536是1001，多了1微秒，这样定时就是1.001ms

	ET0 = 1; // T0对应的中断开关闭合
	EA = 1;	 // 中断总开关闭合
	PT0 = 0; // 设置中断优先级为低级
}

/*上面的的定时器初始化程序要配合下面的定时器中断程序模板，只不过中断程序要写到主函数文件与主函数配合
void Timer0_Routine() interrupt 1 //定时器T0的中断程序函数命名随意，interrupt 1用于将此函数定义为定时器0的中断程序
{
	static unsigned int T0Count;//静态变量使得该变量出了此函数仍然不会被销毁
	TH0=0xFC;//每次计时计完后需要重新赋初值，若
	TL0=0x18;//不赋初值，它会默认重0开始计时,这里设置的时每隔1ms执行一次中断
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;

	}
}
*/


void DS1302_Init(void)
{
	DS1302_SCLK = 0;
	DS1302_CE = 0;
}

void DS1302_WriteByte(unsigned char command, unsigned char Date)
{
	unsigned char i;
	DS1302_CE = 1;

	for (i = 0; i < 8; i++)
	{
		DS1302_IO = command & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}

	for (i = 0; i < 8; i++)
	{
		DS1302_IO = Date & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	DS1302_CE = 0;
}

unsigned char DS1302_ReadByte(unsigned char command)
{
	unsigned char i;
	unsigned char Data = 0x00;
	command |= 0x01; // 这一句的作用就在于，给函数DS1302_ReadByte写的地址，然后
					//最后一位置1就是对应读的地址

	DS1302_CE = 1;
	for (i = 0; i < 8; i++)
	{
		DS1302_IO = command & (0x01 << i);
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}

	for (i = 0; i < 8; i++)
	{
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		if (DS1302_IO)
		{
			Data |= (0x01 << i);
		}
	}
	DS1302_CE = 0;
	DS1302_IO = 0;

	return Data;
}

char DS1302_Time[7] = {23, 11, 19, 15, 41, 0, 6};

void DS1302_SetTime(void)
{
	DS1302_WriteByte(DS1302_WP, 0x00);// 关闭写保护

	DS1302_WriteByte(DS1302_YEAR, DS1302_Time[0] / 10 * 16 + DS1302_Time[0] % 10);
	DS1302_WriteByte(DS1302_MONTH, DS1302_Time[1] / 10 * 16 + DS1302_Time[1] % 10);
	DS1302_WriteByte(DS1302_DATE, DS1302_Time[2] / 10 * 16 + DS1302_Time[2] % 10);
	DS1302_WriteByte(DS1302_HOUR, DS1302_Time[3] / 10 * 16 + DS1302_Time[3] % 10);
	DS1302_WriteByte(DS1302_MINUTE, DS1302_Time[4] / 10 * 16 + DS1302_Time[4] % 10);
	DS1302_WriteByte(DS1302_SECOND, DS1302_Time[5] / 10 * 16 + DS1302_Time[5] % 10);
	DS1302_WriteByte(DS1302_DAY, DS1302_Time[6] / 10 * 16 + DS1302_Time[6] % 10);

	DS1302_WriteByte(DS1302_WP, 0x80); // 打开写保护
}

void DS1302_ReadTime(void)
{
	unsigned char Temp;//中间变量

	Temp = DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0] = Temp / 16 * 10 + Temp % 16;
	Temp = DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1] = Temp / 16 * 10 + Temp % 16;
	Temp = DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2] = Temp / 16 * 10 + Temp % 16;
	Temp = DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3] = Temp / 16 * 10 + Temp % 16;
	Temp = DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4] = Temp / 16 * 10 + Temp % 16;
	Temp = DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5] = Temp / 16 * 10 + Temp % 16;
	Temp = DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6] = Temp / 16 * 10 + Temp % 16;
}

void Buzzer_Delay500us(void) //@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 227;
	while (--i)
		;
}

void Buzzer_Time(unsigned int ms)
{
	unsigned int i = 0;
	for (i = 0; i < ms*2; i++)
	{
		Buzzer = !Buzzer;
		Buzzer_Delay500us();
	}
}