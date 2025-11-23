#include "nixie.h"
#include <mcs51/8052.h>

// 数码管段码表 0-9 (共阴极)
// P0.0~P0.7 对应 a~dp
static unsigned char NixieTable[] = {
    0x3F, // 0: 0011 1111
    0x06, // 1: 0000 0110
    0x5B, // 2: 0101 1011
    0x4F, // 3: 0100 1111
    0x66, // 4: 0110 0110
    0x6D, // 5: 0110 1101
    0x7D, // 6: 0111 1101
    0x07, // 7: 0000 0111
    0x7F, // 8: 0111 1111
    0x6F  // 9: 0110 1111
};

/**
 * @brief 在指定位置显示数字
 * @param location 数码管位置 (1-8)
 * @param number 要显示的数字 (0-9)
 */
void Nixie_Show(unsigned char location, unsigned char number)
{
    unsigned char index;

    // 参数检查
    if (location < 1 || location > 8) return;
    if (number > 9) return; // 暂时只支持0-9

    // 消影：先将段选清零，防止切换位选时出现重影
    P0 = 0x00;

    // 计算位选索引 (0-7)
    // 映射关系：location 1 -> index 7 (LED8), location 8 -> index 0 (LED1)
    index = 8 - location;

    // 设置位选 P2_2, P2_3, P2_4
    // 对应 3-8 译码器输入
    // location 1 -> 000
    // location 8 -> 111
    
    if (index & 0b00000001) P2_2 = 1; else P2_2 = 0;
    if (index & 0b00000010) P2_3 = 1; else P2_3 = 0;
    if (index & 0b00000100) P2_4 = 1; else P2_4 = 0;

    // 发送段码
    P0 = NixieTable[number];
}
