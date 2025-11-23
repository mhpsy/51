#ifndef __MATRIX_KEYPAD_H
#define __MATRIX_KEYPAD_H

/**
 * @brief 获取矩阵键盘按下的键值
 * @return unsigned char 键值 (0: 无按键, 1-16: 对应 S1-S16)
 * 
 * 矩阵键盘连接方式 (P1口):
 * 行: P1.7, P1.6, P1.5, P1.4
 * 列: P1.3, P1.2, P1.1, P1.0
 */
unsigned char MatrixKeypad_GetKey(void);

#endif
