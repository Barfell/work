#ifndef _TIMER_H_                           
#define _TIMER_H_

#include "kernal.h"


/***对外函数声明***/
VOID TIM_Create(VOID);	//配置定时器为1ms中断一次
VOID TIM_Open(VOID);	//打开定时器
VOID TIM_Close(VOID);	//关闭定时器
VOID SetTimer(u16 wTimeOut);
U16 GetTimer(VOID);

#endif
