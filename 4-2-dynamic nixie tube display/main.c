#include <REGX52.H>

void NixieTube(unsigned char Location,Number)
{
	unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	switch(Location)
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[Number];
	//Ҫͬʱ��ʾ�������ܣ���Ҫ��Ӱ
	//��ʾ�������ܣ����Ƚ�����������λѡ���ٶ����ѡ
	//Ȼ���ٶ���һ������ܽ���λѡ���ٶ�ѡ����������
	//�߼����ǣ�λѡ ��ѡ �� ��һ�������λѡ ��ѡ
	//���ѡ����һ��λѡ֮�䣬��Ϊ�ٶȺܿ죬�ᵼ���ϸ���ѡ
	//�����ݻᴮ����һ��λѡ�ϣ��Ӷ�����Ӱ��
	//��������������߼�֮�����һ������ͺ��ˣ�������ݲ���ʾ
	//����λѡ ��ѡ ���� ��һ�������λѡ ��ѡ
	//���³��������������Ӱ��
	Delay(1);//����ʱ1ms������������㣬ֻ�ǻ���ԭ��������ܱ䰵
	P0=0x00;//����
}

void main()
{
	while(1)
	{
			NixieTube(1,1);
			NixieTube(2,2);
			NixieTube(3,3);
	}
}

