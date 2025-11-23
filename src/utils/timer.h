#ifndef __TIMER_H__
#define __TIMER_H__

/**
 * @brief 初始化定时器0
 * 
 * @param us 定时时间，单位微秒(us)。注意：基于12MHz晶振，最大约为65ms。
 *           如果传入0，则使用默认1ms (1000us)。
 */
void Timer0_Init(void);

/**
 * @brief 定时器0中断回调函数注册
 * 
 * @param callback 回调函数指针
 */
void Timer0_SetCallback(void (*callback)(void));

/**
 * @brief 获取定时器0溢出计数
 * 
 * @return unsigned int 
 */
unsigned int Timer0_GetOverflowCount(void);

/**
 * @brief 重置定时器0溢出计数
 * 
 */
void Timer0_ResetOverflowCount(void);

/**
 * @brief 定时器0中断处理函数 (供 ISR 调用)
 * 
 */
void Timer0_HandleISR(void);

#endif
