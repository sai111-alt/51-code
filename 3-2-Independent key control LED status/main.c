#include <REGX52.H>

void Delay(int xms)	//@12MHz
{
	unsigned char data i, j;

	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
		}
}


void main()
{
	while(1)
	{
		if(P3_1==0)//�жϰ����Ƿ���
		{
			Delay(20);//�����Ѿ����£��˳�����а����պϵ�����
			while(P3_1==0);
			Delay(20);//����whileѭ���ж�һֱ�������Ͽ��������Ͽ���
								//���ô˳�����а����Ͽ�������,������ɰ���������һ������
			P2_0=~P2_0;
		}
	}
}
