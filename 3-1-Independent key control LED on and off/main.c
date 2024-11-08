#include <REGX52.H>

void main()
{
	//P2_0=0;//表示直接给p2.0口低电平

	while(1)
	{
			if(P3_1==0 || P3_0==0)
		{
			P2_0=0;
		}
		else
		{
			P2_0=1;
		}
	}
}

