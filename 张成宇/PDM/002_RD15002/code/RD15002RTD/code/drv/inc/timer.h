#ifndef _TIMER_H_                           
#define _TIMER_H_

#include "kernal.h"


/***���⺯������***/
VOID TIM_Create(VOID);	//���ö�ʱ��Ϊ1ms�ж�һ��
VOID TIM_Open(VOID);	//�򿪶�ʱ��
VOID TIM_Close(VOID);	//�رն�ʱ��
VOID SetTimer(u16 wTimeOut);
U16 GetTimer(VOID);

#endif
