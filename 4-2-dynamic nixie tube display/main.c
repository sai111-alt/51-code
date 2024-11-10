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
	//要同时显示多个数码管，需要消影
	//显示多个数码管：是先进行这个数码的位选，再对其段选
	//然后再对下一个数码管进行位选，再段选，依次类推
	//逻辑就是：位选 段选 → 下一个数码管位选 段选
	//这段选到下一个位选之间，因为速度很快，会导致上个段选
	//的数据会串到下一个位选上，从而产生影子
	//所以我们在这个逻辑之间加上一个清零就好了，让数码馆不显示
	//即：位选 段选 清零 下一个数码管位选 段选
	//以下程序用于数码管消影：
	Delay(1);//先延时1ms，如果立马清零，只是会让原来的数码管变暗
	P0=0x00;//清零
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

