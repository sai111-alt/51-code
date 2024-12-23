#include "Delay.h"

unsigned char Animation[] = // hello!! 流动显示
	{
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0xFF,
		0x08,
		0x08,
		0x08,
		0xFF,
		0x00,
		0x00,
		0x0E,
		0x15,
		0x15,
		0x15,
		0x09,
		0x00,
		0xFF,
		0x01,
		0x01,
		0x00,
		0xFF,
		0x01,
		0x01,
		0x00,
		0x1E,
		0x21,
		0x21,
		0x1E,
		0x00,
		0xFD,
		0x00,
		0xFD,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
};

unsigned char code Animation_1[] = // 逐帧动画 这里加code是因为RAM空间太小，
	{							   //一旦数组数据过多，就会数据溢出，而加上code，
								   //就可以将数组数据放到更大的flash里面
								   //而一旦放到里面，在main函数里面是不能更改的，因为ROM用的就是flash
		0x78,0x86,0xA1,0x89,0x89,0xA1,0x86,0x78,
		0x78,0x86,0xA9,0x89,0x89,0xA9,0x86,0x78,
		0x78,0x86,0xA9,0x85,0x85,0xA9,0x86,0x78,
		0x78,0x86,0xA9,0x89,0x89,0xA9,0x86,0x78,
		0x78,0x86,0xA1,0x8D,0x8D,0xA1,0x86,0x78,
		0x78,0x86,0xA9,0x8D,0x8D,0xA9,0x86,0x78,

};

void main()
{
	unsigned char i = 0;
	unsigned char offset = 0;
	unsigned char count = 0;

	MatrixLED_Init();
	while (1)
	{
		for (i = 0; i < 8; i++)
		{
			 MatrixLED_Show(i, Animation[i + offset]); // hello!! 流动显示
			//MatrixLED_Show(i, Animation_1[i + offset]); // 逐帧动画
		}
		count++;
		if (count > 10)
		{
			count = 0;
			offset ++;//逐帧动画+=8，流动动画++
			if (offset > 40) // 防止数组溢出，若数组变化要重新计算，这里逐帧的数组是24，流动的数组是40
			{ 
				offset = 0;
			}
		}
	}
}