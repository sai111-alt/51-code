#include "Delay.h"

// 引脚配置：
sbit LCD_RS = P2 ^ 6;
sbit LCD_RW = P2 ^ 5;
sbit LCD_EN = P2 ^ 7;
#define LCD_DataPort P0

// 函数定义：
/**
 * @brief  LCD1602延时函数，12MHz调用可延时1ms
 * @param  无
 * @retval 无
 */
void LCD_Delay()
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j)
			;
	} while (--i);
}

/**
 * @brief  LCD1602写命令
 * @param  Command 要写入的命令
 * @retval 无
 */
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DataPort = Command;
	LCD_EN = 1;
	LCD_Delay();
	LCD_EN = 0;
	LCD_Delay();
}

/**
 * @brief  LCD1602写数据
 * @param  Data 要写入的数据
 * @retval 无
 */
void LCD_WriteData(unsigned char Data)
{
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_DataPort = Data;
	LCD_EN = 1;
	LCD_Delay();
	LCD_EN = 0;
	LCD_Delay();
}

/**
 * @brief  LCD1602设置光标位置
 * @param  Line 行位置，范围：1~2
 * @param  Column 列位置，范围：1~16
 * @retval 无
 */
void LCD_SetCursor(unsigned char Line, unsigned char Column)
{
	if (Line == 1)
	{
		LCD_WriteCommand(0x80 | (Column - 1));
	}
	else if (Line == 2)
	{
		LCD_WriteCommand(0x80 | (Column - 1 + 0x40));
	}
}

/**
 * @brief  LCD1602初始化函数
 * @param  无
 * @retval 无
 */
void LCD_Init()
{
	LCD_WriteCommand(0x38); // 八位数据接口，两行显示，5*7点阵
	LCD_WriteCommand(0x0c); // 显示开，光标关，闪烁关
	LCD_WriteCommand(0x06); // 数据读写操作后，光标自动加一，画面不动
	LCD_WriteCommand(0x01); // 光标复位，清屏
}

/**
 * @brief  在LCD1602指定位置上显示一个字符
 * @param  Line 行位置，范围：1~2
 * @param  Column 列位置，范围：1~16
 * @param  Char 要显示的字符
 * @retval 无
 */
void LCD_ShowChar(unsigned char Line, unsigned char Column, char Char)
{
	LCD_SetCursor(Line, Column);
	LCD_WriteData(Char);
}

/**
 * @brief  在LCD1602指定位置开始显示所给字符串
 * @param  Line 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  String 要显示的字符串
 * @retval 无
 */
void LCD_ShowString(unsigned char Line, unsigned char Column, char *String)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for (i = 0; String[i] != '\0'; i++)
	{
		LCD_WriteData(String[i]);
	}
}

/**
 * @brief  返回值=X的Y次方
 */
int LCD_Pow(int X, int Y)
{
	unsigned char i;
	int Result = 1;
	for (i = 0; i < Y; i++)
	{
		Result *= X;
	}
	return Result;
}

/**
 * @brief  在LCD1602指定位置开始显示所给数字
 * @param  Line 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~65535
 * @param  Length 要显示数字的长度，范围：1~5
 * @retval 无
 */
void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for (i = Length; i > 0; i--)
	{
		LCD_WriteData(Number / LCD_Pow(10, i - 1) % 10 + '0');
	}
}

/**
 * @brief  在LCD1602指定位置开始以有符号十进制显示所给数字
 * @param  Line 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：-32768~32767
 * @param  Length 要显示数字的长度，范围：1~5
 * @retval 无
 */
void LCD_ShowSignedNum(unsigned char Line, unsigned char Column, int Number, unsigned char Length)
{
	unsigned char i;
	unsigned int Number1;
	LCD_SetCursor(Line, Column);
	if (Number >= 0)
	{
		LCD_WriteData('+');
		Number1 = Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1 = -Number;
	}
	for (i = Length; i > 0; i--)
	{
		LCD_WriteData(Number1 / LCD_Pow(10, i - 1) % 10 + '0');
	}
}

/**
 * @brief  在LCD1602指定位置开始以十六进制显示所给数字
 * @param  Line 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~0xFFFF
 * @param  Length 要显示数字的长度，范围：1~4
 * @retval 无
 */
void LCD_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i, SingleNumber;
	LCD_SetCursor(Line, Column);
	for (i = Length; i > 0; i--)
	{
		SingleNumber = Number / LCD_Pow(16, i - 1) % 16;
		if (SingleNumber < 10)
		{
			LCD_WriteData(SingleNumber + '0');
		}
		else
		{
			LCD_WriteData(SingleNumber - 10 + 'A');
		}
	}
}

/**
 * @brief  在LCD1602指定位置开始以二进制显示所给数字
 * @param  Line 起始行位置，范围：1~2
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
 * @param  Length 要显示数字的长度，范围：1~16
 * @retval 无
 */
void LCD_ShowBinNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for (i = Length; i > 0; i--)
	{
		LCD_WriteData(Number / LCD_Pow(2, i - 1) % 2 + '0');
	}
}

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

void NixieTube(unsigned char Location, unsigned char Number)
{
	unsigned char NixieTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
	switch (Location)
	{
	case 1:
		P2_4 = 1;
		P2_3 = 1;
		P2_2 = 1;
		break;
	case 2:
		P2_4 = 1;
		P2_3 = 1;
		P2_2 = 0;
		break;
	case 3:
		P2_4 = 1;
		P2_3 = 0;
		P2_2 = 1;
		break;
	case 4:
		P2_4 = 1;
		P2_3 = 0;
		P2_2 = 0;
		break;
	case 5:
		P2_4 = 0;
		P2_3 = 1;
		P2_2 = 1;
		break;
	case 6:
		P2_4 = 0;
		P2_3 = 1;
		P2_2 = 0;
		break;
	case 7:
		P2_4 = 0;
		P2_3 = 0;
		P2_2 = 1;
		break;
	case 8:
		P2_4 = 0;
		P2_3 = 0;
		P2_2 = 0;
		break;
	}
	P0 = NixieTable[Number];
	Delay(1);
	P0 = 0x00;
}

// 作用是获取矩阵键盘，范围为0~16，无按键按下返回值为0
unsigned char MatrixKeyboard()
{
	unsigned char KeyNumber = 0;

	P1 = 0xFF;
	P1_3 = 0; /*结合电路原理图，当P1_3=0，其他列为1时，则检测第1列，当有按键按下时，
				   比如S1被按下，那么电路导通，会使得P1_7=0;反之，若P1_7=0,则S1被按下，
				   所以我们依次判断对应4个IO口是否为0就可以知道哪个按键被按下了，
				   然后依次切换对应列，逐个扫描就能识别整个矩阵键盘哪个按键被按下了。*/
	if (P1_7 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 1;
	}
	if (P1_6 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 5;
	}
	if (P1_5 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 9;
	}
	if (P1_4 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 13;
	}

	P1 = 0xFF;
	P1_2 = 0;
	if (P1_7 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 2;
	}
	if (P1_6 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 6;
	}
	if (P1_5 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 10;
	}
	if (P1_4 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 14;
	}

	P1 = 0xFF;
	P1_1 = 0;
	if (P1_7 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 3;
	}
	if (P1_6 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 7;
	}
	if (P1_5 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 11;
	}
	if (P1_4 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 15;
	}

	P1 = 0xFF;
	P1_0 = 0;
	if (P1_7 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 4;
	}
	if (P1_6 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 8;
	}
	if (P1_5 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 12;
	}
	if (P1_4 == 0)
	{
		Delay(100);
		while (P1_7 == 0)
			;
		Delay(100);
		KeyNumber = 16;
	}

	return KeyNumber;
}

void Timer0Init() // 1ms@12MHz
{
	TMOD &= 0xF0; // 把TMOD的低四位清零，高四位保持不变
	TMOD |= 0x01; // 把TMOD的最低位置1，其他7位保持不变
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

/*上面的的定时器初值程序要配合下面的定时器中断程序模板，只不过中断程序要写到主函数文件与主函数配合
void Timer0_Routine() interrupt 1 //定时器T0的中断程序命名，这是标准定义，不能随意更改
{
	static unsigned int T0Count;//静态变量使得该变量出了此函数仍然不会被销毁
	TH0=0xFC;//每次计时计完后需要重新赋初值，若
	TL0=0x18;//不赋初值，它会默认重0开始计时
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;

	}
}
*/

// 作用是获取独立按键，范围为0~4，无按键按下返回值为0
unsigned char IndependentKey()
{
	unsigned char KeyNumber = 0;

	if (P3_1 == 0)
	{
		Delay(100);
		while (P3_1 == 0)
			;
		Delay(100);
		KeyNumber = 1;
	}
	if (P3_0 == 0)
	{
		Delay(100);
		while (P3_0 == 0)
			;
		Delay(100);
		KeyNumber = 2;
	}
	if (P3_2 == 0)
	{
		Delay(100);
		while (P3_2 == 0)
			;
		Delay(100);
		KeyNumber = 3;
	}
	if (P3_3 == 0)
	{
		Delay(100);
		while (P3_3 == 0)
			;
		Delay(100);
		KeyNumber = 4;
	}

	return KeyNumber;
}

void UART_Init() // 波特率4800
{
	SCON = 0x50;  // 其他初始化为0，而选择工作方式为1
	PCON |= 0x80; // 使能波特率加倍，从而减少误差
	// 注意51的串口只能配置定时器1
	TMOD &= 0x0F;
	TMOD |= 0x20; // 串口需要定时器1设置为8位自动重装模式
	// 8位自动重装模式就是只赋一次初值，后面自动装载，而无需再中断程序中再装

	// 这里无需设置溢出标志位，因为只要定时器1在计数有溢出就会生成波特率
	TR1 = 1; // 即启动定时器1开始计时

	TH1 = 0xF4; // 设置定时器1初值
	TL1 = 0xF4;

	ET1 = 0; // 禁止定时器中断,这里不需要定时器中断
}

void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;	// SBUF负责接收/发送数据
	while (TI == 0) // TI是发送控制器，当发送完成后TI=0，否则为1，
	{				// 这里不可以一直发送，所以需要知道TI发送完后后才能继续发送
		;
	}
	TI = 0; // 当TI=1后，必须用软件复位，即TI=0;
}
