#ifndef __DELAY_H__
#define __DELAY_H__

#include <REGX52.H>

// 引脚配置：
sbit LCD_RS = P2 ^ 6;
sbit LCD_RW = P2 ^ 5;
sbit LCD_EN = P2 ^ 7;
#define LCD_DataPort P0

// 这里用位声明，作用于#define类似，注意P3^5就是P3_5,^不是异或操作，其他同理
sbit RCK = P3 ^ 5; // RCK即74HC595的RCLK
sbit SCK = P3 ^ 6; // 同理，即SRCLK
sbit SER = P3 ^ 4;

// 用户调用函数：
void LCD_Init();
void LCD_ShowChar(unsigned char Line, unsigned char Column, char Char);
void LCD_ShowString(unsigned char Line, unsigned char Column, char *String);
void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length);
void LCD_ShowSignedNum(unsigned char Line, unsigned char Column, int Number, unsigned char Length);
void LCD_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length);
void LCD_ShowBinNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length);

void Delay(unsigned int xms);
void NixieTube(unsigned char Location, unsigned char Number);

unsigned char MatrixKeyboard();

void Timer0Init();

unsigned char IndependentKey();

void UART_Init();
void UART_SendByte(unsigned char Byte);

void MatrixLED_Init();
void _74HC595_WriteByte(unsigned char Byte);
void MatrixLED_Show(unsigned char Column, unsigned char Data);

#endif