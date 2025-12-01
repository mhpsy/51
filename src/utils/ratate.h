#include <stdint.h>

#define BITS_IN_BYTE 8


/**
 * @brief 循环左移 (Rotate Left)
 * * @param val 要操作的 8 位值
 * @param shift_amount 移位的位数 (0-7)
 * @return uint8_t 循环左移后的值
 */
#define ROL8(val, shift_amount) \
    ( (uint8_t)(val) << (shift_amount) ) | ( (uint8_t)(val) >> (BITS_IN_BYTE - (shift_amount)) )

/**
 * @brief 循环右移 (Rotate Right)
 * * @param val 要操作的 8 位值
 * @param shift_amount 移位的位数 (0-7)
 * @return uint8_t 循环右移后的值
 */
#define ROR8(val, shift_amount) \
    ( (uint8_t)(val) >> (shift_amount) ) | ( (uint8_t)(val) << (BITS_IN_BYTE - (shift_amount)) )

