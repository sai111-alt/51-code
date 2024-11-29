#include "Delay.h"

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
	// 要同时显示多个数码管，需要消影
	// 显示多个数码管：是先进行这个数码的位选，再对其段选
	// 然后再对下一个数码管进行位选，再段选，依次类推
	// 逻辑就是：位选 段选 → 下一个数码管位选 段选
	// 这段选到下一个位选之间，因为速度很快，会导致上个段选
	// 的数据会串到下一个位选上，从而产生影子
	// 所以我们在这个逻辑之间加上一个清零就好了，让数码馆不显示
	// 即：位选 段选 清零 下一个数码管位选 段选
	// 以下程序用于数码管消影：
	Delay(1);  // 先延时1ms，如果立马清零，只是会让原来的数码管变暗
	P0 = 0x00; // 清零
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
	TMOD |= 0x01; // 把TMOD的最低位置1，其他7位保持不变，这里即设置了定时器0的模式是工作方式1：16位计数器
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
	SCON = 0x50;  // 其他初始化为0，而选择工作方式为1且REN置为1允许串口接受数据
	PCON |= 0x80; // 使能波特率加倍，从而减少误差
	// 注意51的串口只能配置定时器1
	TMOD &= 0x0F;
	TMOD |= 0x20; // 串口需要定时器1设置为8位自动重装模式
	// 8位自动重装模式就是只赋一次初值，后面自动装载，而无需再中断程序中再装初值

	// 这里无需设置溢出标志位，因为只要定时器1在计数有溢出就会生成波特率
	TR1 = 1; // 即启动定时器1开始计时

	TH1 = 0xF4; // 设置定时器1初值
	TL1 = 0xF4; // 设置定时器1的自动重载值

	ET1 = 0; // 禁止定时器中断,这里不需要定时器中断

	EA = 1; // 总中断开关闭合
	ES = 1; // 串口中断开关闭合，当发送/接受数据时，则触发中断
}

void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;	// SBUF负责接收/发送数据
	while (TI == 0) // TI是发送控制器，当发送完成后TI=0，否则为1，
	{				// 这里不可以一直发送，所以需要知道TI发送完后后才能继续发送
		;
	}
	TI = 0; // TI不能自动复位，需程序复位，以便下一次的判断
}

/*中断程序要写到主函数文件与主函数配合,这里的串口中断程序是用于电脑发送给单片机数据，单片机则触发中断来接受数据
void UART_Routine() interrupt 4 // interrupt 4用于将此函数定义为串口中断的程序
{
	if (RI == 1) // 接受中断请求标志位，1即接受，因为发送和接受中断标志位是用的同一个或门，
	{			 // 所以这里我们需要判断究竟是发送还是接受触发的中断
		;
		RI = 0; // RI不能自动复位，需程序复位，以便下一次的判断
	}
}
*/

void MatrixLED_Init()
{
	SCK = 0; // 移位信号初始化为0，方便后续赋1移位
	RCK = 0; // 并行输出信号初试化为0, 方便后续输出
}

void _74HC595_WriteByte(unsigned char Byte) // 注意函数名不能以数字开头
{
	unsigned char i = 0;
	for (i = 0; i < 8; i++)
	{
		SER = Byte & (0x80 >> i);
		// Byte与1000 0000相与确认Byte的最高位(同理，下次循环，Byte与0100 0000相与)
		// 而SER是一个位，给它赋值就是非0即1，
		// 也就是说SER只要接受非零的数值它就是1，否则就是0
		// 所以这样就可以提取出Byte的1位数值
		SCK = 1; // 给SCK赋1移位
		SCK = 0; // 置0方便下次移位
	}
	RCK = 1; // 将此8位数据输出出去
	RCK = 0; // 置0以便下次输出
}

// Column 即矩阵的列，Data 即列显示的数据，高位在上，1亮0灭
void MatrixLED_Show(unsigned char Column, unsigned char Data)
{
	_74HC595_WriteByte(Data);
	P0 = ~(0x80 >> Column);
	Delay(1); // 与数码管一样，这里LED点阵也要消影
	P0 = 0xFF;
}

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
					 // 最后一位置1就是对应读的地址

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
	DS1302_WriteByte(DS1302_WP, 0x00); // 关闭写保护

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
	unsigned char Temp; // 中间变量

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

void I2C_Start(void) // I2C开始
{
	I2C_SCL = 1;
	I2C_SDA = 1;
	I2C_SDA = 0;
	I2C_SCL = 0;
}

void I2C_Stop(void) // I2C停止
{
	I2C_SDA = 0;
	I2C_SCL = 1;
	I2C_SDA = 1;
}

void I2C_SendByte(unsigned char Byte) // I2C发送一个字节，Byte即要发送的字节
{
	unsigned char i;
	for (i = 0; i < 8; i++)
	{
		I2C_SDA = Byte & (0x80 >> i); // 依次取出Byte的位
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
}

unsigned char I2C_ReceiveByte(void) // I2C接收一个字节并返回
{
	unsigned char Byte = 0x00;
	unsigned char i = 0;

	I2C_SDA = 1;

	for (i = 0; i < 8; i++)
	{
		I2C_SCL = 1;
		if (I2C_SDA)
		{
			Byte |= (0x80 >> i);
		}
		I2C_SCL = 0;
	}

	return Byte;
}

void I2C_SendAck(unsigned char AckBit) // I2C主机发送应答，AckBit为应答，0应答，1非应答
{
	I2C_SDA = AckBit;
	I2C_SCL = 1;
	I2C_SCL = 0;
}

unsigned char I2C_ReceiveAck(void) // I2C主机接收应答
{
	unsigned char AckBit;
	I2C_SDA = 1;
	I2C_SCL = 1;
	AckBit = I2C_SDA;
	I2C_SCL = 0;
	return AckBit;
}

// 注意输入的WordAddress是8位地址，所以取值应是0~255
void AT24C02_WriterByte(unsigned char WordAddress, unsigned char Data)
{
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
}

// 注意输入的WordAddress是8位地址，所以取值应是0~255
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data = 0;
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS | 0x01);
	I2C_ReceiveAck();
	Data = I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();

	return Data;
}

// 外部中断初始化函数
void Int0_Init(void)
{
	IT0 = 1; // 设置外部中断为下降沿触发
	IE0 = 0; // 设置外部中断标志位为0
	EX0 = 1; // 外部中断对应开关闭合
	EA = 1;	 // 中断总开关闭合
	PX0 = 1; // 设置外部中断的优先级为高级，这样当红外信号来时，外部中断可以打断其他信号以即时处理红外信号
}

/*外部中断函数模板
void Int0_Routine(void) interrupt 0
{

}
*/

void Timer0_Init(void)
{
	TMOD &= 0xF0;
	TMOD |= 0x01;

	TF0 = 0;
	TR0 = 0; // 即初始化关闭定时器0计时

	TH0 = 0;
	TL0 = 0;
}

// 此函数用于设置定时器的定时时间
void Timer0_SetCounter(unsigned int Value)
{
	TH0 = Value / 256;
	TL0 = Value % 256;
}

// 此函数用于得到定时器计时当前的时间
unsigned int Timer0_GetCounter(void)
{
	return (TH0 << 8) | TL0;
}

// 此函数负责开启和关闭定时器
void Timer0_Run(unsigned char Flag)
{
	TR0 = Flag;
}

unsigned int IR_Time;
unsigned char IR_State;

unsigned char IR_Data[4];
unsigned char IR_pData; // 记录Data存到了第几位

unsigned char IR_DataFlag;	 // Data数据收到的标志位
unsigned char IR_RepeatFlag; // 重发标志位

unsigned char IR_Address;
unsigned char IR_Command;

void IR_Init(void)
{
	Timer0_Init();
	Int0_Init();
}

unsigned char IR_GetDataFlag(void)
{
	if (IR_DataFlag)
	{
		IR_DataFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_GetRepeatFlag(void)
{
	if (IR_RepeatFlag)
	{
		IR_RepeatFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_GetAddress(void)
{
	return IR_Address;
}

unsigned char IR_GetCommand(void)
{
	return IR_Command;
}

// 11.0592MHz： Start信号：12442±1000，Repeat : 10368±1000； 读“0”：1032±1000；读“1”：2074±1000；改好以后就能有现象了。
void Int0_Routine(void) interrupt 0
{
	if (IR_State == 0) // 发送的最初状态0要初始化定时器开始计时
	{
		Timer0_SetCounter(0);
		Timer0_Run(1);
		IR_State = 1;
	}
	else if (IR_State == 1) // 从状态0变到状态1意味着红外信号可能来了
	{
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if (IR_Time > 12442 - 500 && IR_Time < 12442 + 500) // 判断是否时start信号
		{
			IR_State = 2; // 若是start信号则进入状态2接受数据
		}
		else if (IR_Time > 10368 - 500 && IR_Time < 10368 + 500) // 判断是否时repeat信号
		{
			IR_RepeatFlag = 1; // 如果是repeat信号，说明Data已经发完了，开始重复发Data
			Timer0_Run(0);
			IR_State = 0;
		}
		else // 如果既不是satart，也不是repeat，说明信号有问题，则回到1重复判断
		{
			IR_State = 1;
		}
	}
	else if (IR_State == 2)
	{
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if (IR_Time > 1032 - 500 && IR_Time < 1032 + 500)
		{
			IR_Data[IR_pData / 8] &= ~(0x01 << (IR_pData % 8)); // 数据对应位清0
			IR_pData++;											// 数据位置指针自增
		}
		else if (IR_Time > 2074 - 500 && IR_Time < 2074 + 500) // 判断是否是数据1
		{
			IR_Data[IR_pData / 8] |= (0x01 << (IR_pData % 8)); // 若是数据1，则根据pData将1放入相应位
			IR_pData++;
		}
		else // 既不是0也不是1，说明数据有误，则回到状态1重新接受start信号，因为你按遥控板时，按一次没反应，肯定会按第二次
		{
			IR_pData = 0;
			IR_State = 1;
		}
		if (IR_pData >= 32) // 如果接收到了32位数据
		{
			IR_pData = 0;													// 数据位置指针清0
			if ((IR_Data[0] == ~IR_Data[1]) && (IR_Data[2] == ~IR_Data[3])) // 数据验证
			{
				IR_Address = IR_Data[0]; // 转存数据
				IR_Command = IR_Data[2];
				IR_DataFlag = 1; // 置收到连发帧标志位为1
			}
			Timer0_Run(0); // 定时器停止
			IR_State = 0;  // 置状态为0
		}
	}
}
