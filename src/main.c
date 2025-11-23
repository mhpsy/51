#include <mcs51/8052.h>
#include <utils/delay.h>
#include <utils/button.h>

// LED 状态变量
unsigned char led_state = 0xFE; // 初始状态：0b11111110，P2.0 点亮

void button_handle_p30(void)
{
    // P3.0 按下：LED 左移
    led_state = (led_state << 1) | 0x01; // 左移并补1
    if (led_state == 0xFF) // 如果全灭，重置为 P2.0 点亮
    {
        led_state = 0xFE;
    }
    P2 = led_state;
}


void main()
{
    P2 = led_state; // 初始化 LED 状态
    
    while (1)
    {
        button_scan(); // 扫描按键
    }
}


void button_handle_p31(void)
{
    // 其他按键功能可在此实现
}

void button_handle_p32(void)
{
    // 其他按键功能可在此实现
}

void button_handle_p33(void)
{
    // 其他按键功能可在此实现
}