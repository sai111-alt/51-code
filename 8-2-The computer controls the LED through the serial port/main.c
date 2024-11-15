#include "Delay.h"

unsigned char Sec;

void main()
{
	UART_Init();
	while(1)
	{
		;
	}
}

void UART_Routine() interrupt 4 //interrupt 4用于将此函数定义为串口中断的程序
{
	if(RI==1)//接受中断请求标志位，1即接受，因为发送和接受中断标志位是用的同一个或门，
	{		 // 所以这里我们需要判断究竟是发送还是接受触发的中断
		P2 = ~SBUF;
		UART_SendByte(SBUF);
		RI = 0; // RI不能自动复位，需程序复位，以便下一次的判断
	}
}
