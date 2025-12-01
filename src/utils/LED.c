#include <mcs51/8052.h>
#include "LED.h"
#include "delay.h"

// sbit SER = P3 ^ 4;
// sbit RCK = P3 ^ 5;
// sbit SCK = P3 ^ 6;

// SDCC 语法: __sbit __at (位地址) 变量名;
// P3 基地址 0xB0, P3.4 = 0xB4, P3.5 = 0xB5, P3.6 = 0xB6
__sbit __at(0xB4) SER; // P3.4
__sbit __at(0xB5) RCK; // P3.5
__sbit __at(0xB6) SCK; // P3.6

void MxLED_Init(void)
{
    SER = 0;
    RCK = 0;
    SCK = 0;
}

void MxLED_SendByte(unsigned char byte)
{
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        SCK = 0;
        // 依次发送最高位到最低位
        // 必须转换为 0 或 1，否则位变量赋值可能出错
        SER = (byte & (0x80 >> i)) ? 1 : 0;
        SCK = 1;
    }
    RCK = 1;
    RCK = 0;
}

void MxLED_ShowColumn(unsigned char column, unsigned char data)
{
    P0 = 0xFF;              // 1. 消影：先关闭所有列 (假设P0低电平有效)
    MxLED_SendByte(data);   // 2. 发送数据到 74HC595 并锁存 (此时 P0 还是关闭的，不会显示错误数据)
    P0 = ~(0x80 >> column); // 3. 开启目标列
    Delay(1);               // 4. 保持显示一段时间
}