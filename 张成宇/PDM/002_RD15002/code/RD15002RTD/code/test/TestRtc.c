#include "Rtc.h"  

VOID TestRtc(VOID)
{
	u8 t=0;	
	RTC_Init();
	
	RTC_Set(2015,7,8,15,36,0);//设置时间
	
	while(1)
	{								    
		if(t!=g_CalendarInfo.sec)
		{
			t=g_CalendarInfo.sec;
			printf("%d年", g_CalendarInfo.w_year);
			printf("%d月", g_CalendarInfo.w_month);
			printf("%d日", g_CalendarInfo.w_date);
	 
			switch(g_CalendarInfo.week)
			{
				case 0:
					printf("Sunday");
					break;
				case 1:
					printf("Monday");
					break;
				case 2:
					printf("Tuesday");
					break;
				case 3:
					printf("Wednesday");
					break;
				case 4:
					printf("Thursday");
					break;
				case 5:
					printf("Friday");
					break;
				case 6:
					printf("Saturday");
					break;  
			}
			printf("-%2d时", g_CalendarInfo.hour);
			printf("-%2d分", g_CalendarInfo.min);
			printf("-%2d秒", g_CalendarInfo.sec);

		}	
		DelayMs(10);								  
	}; 

	
}

