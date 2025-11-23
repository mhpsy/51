#include "matrix_keypad.h"
#include <mcs51/8052.h>
#include "delay.h"

/**
 * 这里比较难理解的是，要先通过程序给一行通电，才能够获取到那一列的数据
 * 也就是先把某一行拉低，然后读取列引脚的状态
 * eg:
 * 扫描第一行: P1.7=0
 * P1 = 0x7F; // 0111 1111
 * 这个时候第一行的按键如果被按下，那么对应的列引脚就会被拉低，从而可以通过读取P1的值来判断哪个按键被按下
 * 如果不是第一行的按键被按下，那么P1的值还是0x7F，不会通
 * 
 * 8051默认是高电平的
 * 也就是所有都是默认高电平，如果没有赋值为0，那么怎那么读取P1的值都是0xFF
 */

/**
 * @brief 获取矩阵键盘按下的键值
 * @return unsigned char 键值 (0: 无按键, 1-16: 对应 S1-S16)
 */
unsigned char MatrixKeypad_GetKey(void)
{
    unsigned char key_value = 0;

    // 扫描第一行: P1.7=0
    P1 = 0x7F; // 0111 1111
    if (P1 != 0x7F) // 如果有按键按下，P1的值会改变 (列引脚被拉低)
    {
        Delay(20); // 消抖
        if (P1 != 0x7F)
        {
            if (P1_3 == 0) key_value = 1;
            if (P1_2 == 0) key_value = 2;
            if (P1_1 == 0) key_value = 3;
            if (P1_0 == 0) key_value = 4;
            
            // 等待按键释放
            while (P1 != 0x7F);
            Delay(20);
        }
    }

    // 扫描第二行: P1.6=0
    P1 = 0xBF; // 1011 1111
    if (P1 != 0xBF)
    {
        Delay(20);
        if (P1 != 0xBF)
        {
            if (P1_3 == 0) key_value = 5;
            if (P1_2 == 0) key_value = 6;
            if (P1_1 == 0) key_value = 7;
            if (P1_0 == 0) key_value = 8;
            
            while (P1 != 0xBF);
            Delay(20);
        }
    }

    // 扫描第三行: P1.5=0
    P1 = 0xDF; // 1101 1111
    if (P1 != 0xDF)
    {
        Delay(20);
        if (P1 != 0xDF)
        {
            if (P1_3 == 0) key_value = 9;
            if (P1_2 == 0) key_value = 10;
            if (P1_1 == 0) key_value = 11;
            if (P1_0 == 0) key_value = 12;
            
            while (P1 != 0xDF);
            Delay(20);
        }
    }

    // 扫描第四行: P1.4=0
    P1 = 0xEF; // 1110 1111
    if (P1 != 0xEF)
    {
        Delay(20);
        if (P1 != 0xEF)
        {
            if (P1_3 == 0) key_value = 13;
            if (P1_2 == 0) key_value = 14;
            if (P1_1 == 0) key_value = 15;
            if (P1_0 == 0) key_value = 16;
            
            while (P1 != 0xEF);
            Delay(20);
        }
    }

    return key_value;
}
