#ifndef __NIXIE_H__
#define __NIXIE_H__

/**
 * @brief 在指定位置显示数字
 * @param location 数码管位置 (1-8)
 * @param number 要显示的数字 (0-9)
 */
void Nixie_Show(unsigned char location, unsigned char number);

#endif
