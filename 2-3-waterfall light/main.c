#include <REGX52.H>
#include <INTRINS.H>//ͷ�ļ�����ĸ��Сд������

void Delay500ms()	//�˺�����stc-isp�Զ�����
{
	unsigned char data i, j, k;

	_nop_();//nop��ʾ����䣬ʹ�øú�����Ҫ����<INTRINS.H>
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