#ifndef __RTC_H
#define __RTC_H	 
#include "kernal.h" 	
U8 RtcInit(VOID);													//RTC初始化
VOID RtcSetAlarmA(u8 week,u8 hour,u8 min,u8 sec);					//设置闹钟时间(按星期闹铃,24小时制)
VOID RtcSetWakeUp(u32 wksel,u16 cnt);								//周期性唤醒定时器设置
ErrorStatus RtcSetTime(U8 u8hour,U8 u8min,U8 u8sec,U8 u8ampm);	//RTC时间设置
ErrorStatus RtcSetDate(u8 year,u8 month,u8 date,u8 week); 		//RTC日期设置
#endif

















