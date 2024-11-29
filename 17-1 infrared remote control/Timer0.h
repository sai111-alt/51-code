#ifndef __DELAY_H__
#define __DELAY_H__

void Timer0Init();
void Timer0_SetCounter(unsigned int Value);
unsigned int Timer0_GetCounter(void);
void Timer0_Run(unsigned char Flag);

#endif