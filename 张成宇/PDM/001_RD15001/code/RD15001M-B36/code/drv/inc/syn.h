#ifndef __SYN_H
#define __SYN_H	 
#include "kernal.h"

#include "device.h"
//app
#include "app_usb.h"

VOID SynInit(VOID);


U32 GetSynCount(VOID);

VOID TIMER_Init(U16 u16Cnt, U16 u16Predivision);//TIMER_Init(50-1,8400-1);	//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数50次为5ms 


#endif

















