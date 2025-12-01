#include <mcs51/8052.h>
#include <utils/delay.h>
#include <utils/button.h>
#include <utils/nixie.h>
#include <utils/LCD1602.h>
#include <utils/matrix_keypad.h>
#include <utils/timer.h>
#include <utils/UART.h>
#include <utils/LED.h>
#include <utils/ratate.h>

// LED 状态变量
volatile unsigned char led_state = 0xFE; // 初始状态：0b11111110，P2.0 点亮

void button_handle_p30(void)
{
}

void button_handle_p31(void)
{
}

void button_handle_p32(void)
{
}

void button_handle_p33(void)
{
}

unsigned char counter = 0;

// 定时器回调函数，每1ms调用一次
void Timer0_Callback(void)
{
    // 注意：不要在这里重置 P2，否则会覆盖下面的逻辑

    // 使用 timer.c 中的计数器
    if (Timer0_GetOverflowCount() >= 500) // 0.5秒钟
    {
        Timer0_ResetOverflowCount();
        // 切换LED状态
        // led_state = (led_state << 1) | 0x01; // 左移并补1
        // if (led_state == 0xFF)               // 如果全灭，重置为 P2.0 点亮
        // {
        //     led_state = 0xFE;
        // }
        // P2 = led_state;

        // 发送计数器值通过 UART
        UartSendByte(counter++);
    }
}

// 显式定义中断服务函数，确保链接器能正确生成中断向量
void Timer0_ISR(void) __interrupt(1)
{
    Timer0_HandleISR();
}

void Uart_receive_ISR(void) __interrupt(4)
{
    if (RI == 0)
        return; // 如果不是接收中断，直接返回
    P2 = ~SBUF; // 接收到的数据取反后显示在 P2 口
    RI = 0;     // 清除接收中断标志
}

void main(void)

{
    P2 = 0x0E; // 证明程序跑起来了
    Timer0_SetCallback(Timer0_Callback);
    Timer0_Init();
    Uart_Init();
    MxLED_Init();

    int showNum = 0;
    unsigned int speed_count = 0;

    while (1)
    {
        // 1. 扫描显示 (必须不断循环扫描)
        for (int i = 7; i >= 0; i--)
        {
            MxLED_ShowColumn(i, ROL8(0x10, i + showNum));
            // 关键点：每列显示后必须保持一段时间，否则亮度极低
            Delay(1); 
        }

        // 2. 动画更新逻辑 (通过计数器降速)
        speed_count++;
        if (speed_count > 20) // 每扫描 20 轮更新一次动画 (约 20 * 8ms = 160ms)
        {
            speed_count = 0;
            showNum++;
            if(showNum > 7){
                showNum = 0;
            }
        }
    }

}