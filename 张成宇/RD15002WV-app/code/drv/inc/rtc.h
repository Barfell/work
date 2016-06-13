#ifndef __RTC_H
#define __RTC_H	 
#include "kernal.h" 	
U8 RtcInit(VOID);													//RTC��ʼ��
VOID RtcSetAlarmA(u8 week,u8 hour,u8 min,u8 sec);					//��������ʱ��(����������,24Сʱ��)
VOID RtcSetWakeUp(u32 wksel,u16 cnt);								//�����Ի��Ѷ�ʱ������
ErrorStatus RtcSetTime(U8 u8hour,U8 u8min,U8 u8sec,U8 u8ampm);	//RTCʱ������
ErrorStatus RtcSetDate(u8 year,u8 month,u8 date,u8 week); 		//RTC��������
#endif

















