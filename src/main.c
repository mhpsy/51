#include <mcs51/8052.h>
#include <utils/delay.h>
#include <utils/button.h>
#include <utils/nixie.h>
#include <utils/LCD1602.h>
#include <utils/matrix_keypad.h>

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

unsigned int count = 0;

void button_handle_p31(void)
{
    count += 1;
    LCD_ShowNum(2, 1, count, 3);
    LCD_ShowString(1, 1, "mhpsy");
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
    unsigned char key_num = 0;
    P2 = led_state; // 初始化 LED 状态

    LCD_Init();
    LCD_ShowString(1, 1, "Matrix Key:");

    while (1)
    {
        key_num = MatrixKeypad_GetKey();
        if (key_num)
        {
            LCD_ShowNum(2, 1, key_num, 2);
        }

        // button_scan(); // 扫描按键

        // // 示例：静态显示，如果需要动态显示多个数字，需要在这里快速循环扫描
        // Nixie_Show(1, 1);
        // Nixie_Show(2, 2);
        // Nixie_Show(3, 3);

        // LCD_ShowString(1, 1, "Hello, World!");
        // LCD_ShowString(1, 14, "mmm");
        // LCD_ShowNum(2, 1, 1234, 4);
    }
}