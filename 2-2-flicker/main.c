#include <REGX52.H>
#include <INTRINS.H>

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
		P2=0xFF;
		Delay500ms();
	}
}

