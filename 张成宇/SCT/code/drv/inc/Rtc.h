#ifndef __RTC_H
#define __RTC_H	 
#include "kernel.h"

//时间结构体
typedef struct _tagCalendarInfo
{
	//公历日月年周
	U8 hour;
	U8 min;
	U8 sec;			
	U16 w_year;
	U8  w_month;
	U8  w_date;
	U8  week;		 
}CCalendarInfo;	//日历结构体

EXTERN CCalendarInfo g_CalendarInfo;//时钟结构体 

BOOL RTC_Init(VOID);        //初始化RTC,FALSE,失败;TRUE,成功;  
U8 RTC_Set(U16 syear,U8 smon,U8 sday,U8 hour,U8 min,U8 sec);//设置时间	
U8 RTC_Get(VOID);//更新时间

#endif

















