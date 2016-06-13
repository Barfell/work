#include "rtc.h"


VOID TestRtc(VOID)
{
	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_DateTypeDef RTC_DateStruct;
	U32 u32Tick;
	S32 s32Tick;
	RtcInit();		 		//初始化RTC

	RtcSetWakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);		//配置WAKE UP中断,1秒钟中断一次
	
	u32Tick = GetTickCount();
	
	while(1) 
	{		
		
		s32Tick = GetTickCount() - u32Tick;
	
		if(s32Tick > 1000)
		{
			u32Tick = GetTickCount();
			
			RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);

			printf("Time:%02d:%02d:%02d",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds); 

			RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);

			printf("Date:20%02d-%02d-%02d",RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date); 	
			printf("Week:%d",RTC_DateStruct.RTC_WeekDay);
		}				
	}	
}

