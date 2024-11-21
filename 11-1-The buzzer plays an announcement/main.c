#include "Delay.h"

unsigned char KeyNum = 0;

void main()
{
	NixieTube(1, 0);
	while(1)
	{
		KeyNum=IndependentKey();
		if(KeyNum)
		{
			Buzzer_Time(1000);
			NixieTube(1, KeyNum);
		}
	}
	 
}
