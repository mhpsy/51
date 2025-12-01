#ifndef _LED_H__
#define _LED_H_

void MxLED_Init(void);
void MxLED_SendByte(unsigned char byte);
void MxLED_ShowColumn(unsigned char column, unsigned char data);

#endif