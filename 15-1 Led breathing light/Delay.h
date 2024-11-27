#ifndef __DELAY_H__
#define __DELAY_H__

#include <REGX52.H>
#include <INTRINS.H>

// 引脚配置：
sbit LCD_RS = P2 ^ 6;
sbit LCD_RW = P2 ^ 5;
sbit LCD_EN = P2 ^ 7;
#define LCD_DataPort P0

// 这里用位声明，作用于#define类似，注意P3^5就是P3_5,^不是异或操作，这是写法规范，其他同理
sbit RCK = P3 ^ 5; // RCK即74HC595的RCLK
sbit SCK = P3 ^ 6; // 同理，即SRCLK
sbit SER = P3 ^ 4;

// 蜂鸣器定义
sbit Buzzer = P2 ^ 5;

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

// I2C定义
sbit I2C_SCL = P2 ^ 1;
sbit I2C_SDA = P2 ^ 0;
#define AT24C02_ADDRESS 0xA0

// 用户调用函数：
void LCD_Init();
void LCD_ShowChar(unsigned char Line, unsigned char Column, char Char);
void LCD_ShowString(unsigned char Line, unsigned char Column, char *String);
void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length);
void LCD_ShowSignedNum(unsigned char Line, unsigned char Column, int Number, unsigned char Length);
void LCD_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length);
void LCD_ShowBinNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length);

void Delay(unsigned int xms);

void Nixie_SetBuf(unsigned char Location, unsigned char Number);
void NixieTube_Scan(unsigned char Location, unsigned char Number);
void NixieTube_Loop(void);

unsigned char MatrixKeyboard();

void Timer0_Init();

unsigned char Key(void);
unsigned char IndependentKey_Getstate();
void IndependentKey_Loop(void);

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

void Buzzer_Time(unsigned int ms);

void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(unsigned char Byte);
unsigned char I2C_ReceiveByte(void);
void I2C_SendAck(unsigned char AckBit);
unsigned char I2C_ReciveAck(void);
void AT24C02_WriterByte(unsigned char WordAddress, unsigned char Data);
unsigned char AT24C02_ReadByte(unsigned char WordAddress);

#endif