#include "Delay.h"

void main()
{
	MatrixLED_Init();
	while (1)
	{
		MatrixLED_Show(0, 0x3C);
		MatrixLED_Show(1, 0x42);
		MatrixLED_Show(2, 0xA9);
		MatrixLED_Show(3, 0x85);
		MatrixLED_Show(4, 0x85);
		MatrixLED_Show(5, 0xA9);
		MatrixLED_Show(6, 0x42);
		MatrixLED_Show(7, 0x3C);
	}
}