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

// DS1302引脚配置和其他定义
sbit DS1302_SCLK = P3 ^ 6;
sbit DS1302_IO = P3 ^ 4;
sbit DS1302_CE = P3 ^ 5;
extern char DS1302_Time[7]; // 年月日时分秒星期,extrn的作用是方便其他c文件引用此全局变量
#define DS1302_SECOND 0x80  // 这里只定义WRITE的地址，而READ的地址只是对应比它多1
#define DS1302_MINUTE 0x82  // 也就是说每一行都比它多1就是READ的地址，刚好就是最后一位置1就是
#define DS1302_HOUR 0x84    // READ地址，而最后一位置0就是WRITE的地址
#define DS1302_DATE 0x86
#define DS1302_MONTH 0x88
#define DS1302_DAY 0x8A
#define DS1302_YEAR 0x8C
#define DS1302_WP 0x8E

// XPT2046引脚配置和其他定义
sbit XPT2046_DIN = P3 ^ 4;
sbit XPT2046_CS = P3 ^ 5;
sbit XPT2046_DCLK = P3 ^ 6;
sbit XPT2046_DOUT = P3 ^ 7;
#define XPT2046_VBAT_8 0xAC
#define XPT2046_AUX_8 0xEC
#define XPT2046_XP_8 0x9C // 0xBC
#define XPT2046_YP_8 0xDC

#define XPT2046_VBAT_12 0xA4
#define XPT2046_AUX_12 0xE4
#define XPT2046_XP_12 0x94 // 0xBC
#define XPT2046_YP_12 0xD4

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

void DS1302_Init(void);
void DS1302_WriteByte(unsigned char command, unsigned char Date);
unsigned char DS1302_ReadByte(unsigned char command);
void DS1302_SetTime(void);
void DS1302_ReadTime(void);

unsigned int XPT2046_ReadAD(unsigned char Command);

#endif