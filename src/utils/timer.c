#include <mcs51/8052.h>
#include "timer.h"

// 回调函数指针
static void (*timer0_callback)(void) = 0;
// 溢出计数器，必须是 volatile，因为它在中断中被修改
static volatile unsigned int timer0_overflow_count = 0;

void Timer0_Init(void)
{
    // 1. 设置定时器模式
    TMOD &= 0xF0;      // 清除 Timer0 控制位
    TMOD |= 0x01;      // 设置 Timer0 为模式 1 (16位定时器)
    
    // 2. 设置定时器初值 (1ms @ 12MHz)
    // 65536 - 1000 = 64536 = 0xFC18
    TH0 = 0xFC;
    TL0 = 0x18;
    
    // 3. 清除溢出标志
    TF0 = 0;
    
    // 4. 开启中断
    ET0 = 1;           // 允许定时器0中断
    EA = 1;            // 允许总中断
    
    // 5. 启动定时器
    TR0 = 1;
}

void Timer0_SetCallback(void (*callback)(void))
{
    timer0_callback = callback;
}

unsigned int Timer0_GetOverflowCount(void)
{
    return timer0_overflow_count;
}

void Timer0_ResetOverflowCount(void)
{
    timer0_overflow_count = 0;
}

// 定时器0中断处理逻辑
// 去掉 __interrupt(1)，改为普通函数，由 main.c 中的 ISR 调用
void Timer0_HandleISR(void)
{
    // 重新加载初值
    TH0 = 0xFC;
    TL0 = 0x18;
    
    timer0_overflow_count++;
    
    if (timer0_callback)
    {
        timer0_callback();
    }
}
