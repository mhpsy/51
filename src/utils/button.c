#include "button.h"
#include "delay.h"
#include <mcs51/8052.h>

// 按键消抖延时时间（毫秒）
#ifndef KEY_DEBOUNCE_DELAY
#define KEY_DEBOUNCE_DELAY 20
#endif

/**
 * @brief 按键扫描并处理（带消抖）
 * @param PIN 按键引脚 (e.g. P3_0)
 * @param HANDLER 按键按下时的处理函数
 * 
 * 注意：使用宏定义是因为 8051 的位变量(sbit)不能通过指针或引用传递给普通函数。
 * 如果作为参数传递，传递的是调用时的值（0或1），导致无法在函数内部检测引脚状态变化，
 * 从而在 while(PIN==0) 处陷入死循环。
 */
#define BUTTON_PROCESS(PIN, HANDLER) \
    if (PIN == 0) \
    { \
        Delay(KEY_DEBOUNCE_DELAY); \
        if (PIN == 0) \
        { \
            HANDLER(); \
            while (PIN == 0) \
                ; \
            Delay(KEY_DEBOUNCE_DELAY); \
        } \
    }

/**
 * @brief 按键扫描函数 - 在主循环中调用
 */
void button_scan(void)
{
    BUTTON_PROCESS(P3_0, button_handle_p30);
    BUTTON_PROCESS(P3_1, button_handle_p31);
    BUTTON_PROCESS(P3_2, button_handle_p32);
    BUTTON_PROCESS(P3_3, button_handle_p33);
}
