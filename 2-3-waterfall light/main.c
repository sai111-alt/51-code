#include <REGX52.H>
#include <INTRINS.H>//头文件对字母大小写不敏感

void Delay500ms()	//此函数用stc-isp自动生成
{
	unsigned char data i, j, k;

	_nop_();//nop表示空语句，使用该函数需要引用<INTRINS.H>
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void main()
{
	while(1)
	{
		P2=0xFE;
		Delay500ms();
		P2=0xFD;
		Delay500ms();
		P2=0xFB;
		Delay500ms();
		P2=0xF7;
		Delay500ms();
		P2=0xEF;
		Delay500ms();
		P2=0xDF;
		Delay500ms();
		P2=0xBF;
		Delay500ms();
		P2=0x7F;
		Delay500ms();
	}
}