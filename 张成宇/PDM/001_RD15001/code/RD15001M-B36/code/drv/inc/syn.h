#ifndef __SYN_H
#define __SYN_H	 
#include "kernal.h"

#include "device.h"
//app
#include "app_usb.h"

VOID SynInit(VOID);


U32 GetSynCount(VOID);

VOID TIMER_Init(U16 u16Cnt, U16 u16Predivision);//TIMER_Init(50-1,8400-1);	//��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�����50��Ϊ5ms 


#endif

















