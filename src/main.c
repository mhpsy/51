#include <mcs51/8052.h>
#include <utils/delay.h>
#include <utils/button.h>
#include <utils/nixie.h>

// LED 状态变量
unsigned char led_state = 0xFE; // 初始状态：0b11111110，P2.0 点亮

void button_handle_p30(void)
{
    // P3.0 按下：LED 左移
    led_state = (led_state << 1) | 0x01; // 左移并补1
    if (led_state == 0xFF)               // 如果全灭，重置为 P2.0 点亮
    {
        led_state = 0xFE;
    }
    P2 = led_state;
}

void button_handle_p31(void)
{
    // 测试数码管：在第1位显示1
    Nixie_Show(1, 1);
}

void button_handle_p32(void)
{
    // 测试数码管：在第8位显示8
    Nixie_Show(8, 8);
}

void button_handle_p33(void)
{
    // 其他按键功能可在此实现
    Nixie_Show(4, 4); // 在第4位显示4作为示例
}

void main()
{
    P2 = led_state; // 初始化 LED 状态

    while (1)
    {
        // button_scan(); // 扫描按键

        // 示例：静态显示，如果需要动态显示多个数字，需要在这里快速循环扫描
        Nixie_Show(1, 1);
        Nixie_Show(2, 2);
        Nixie_Show(3, 3);
    }
}