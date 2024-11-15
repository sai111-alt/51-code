#include "Delay.h"

unsigned char Sec;

void main()
{
	UART_Init();
	while(1)
	{
		UART_SendByte(Sec);
		Sec++;
		Delay(1000);
	}
}

 