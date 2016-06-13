#ifndef _INIT_H
#define _INIT_H
#include "app_rfid.h"
void Init_Device (void);
U32 GetTickCount(void);
void DelayUs(unsigned int t);
void DelayMs(unsigned int t);
void EnterException(unsigned char ucErrCode);
#endif