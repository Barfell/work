#ifndef __RTC_H
#define __RTC_H	 
#include "kernel.h"

//ʱ��ṹ��
typedef struct _tagCalendarInfo
{
	//������������
	U8 hour;
	U8 min;
	U8 sec;			
	U16 w_year;
	U8  w_month;
	U8  w_date;
	U8  week;		 
}CCalendarInfo;	//�����ṹ��

EXTERN CCalendarInfo g_CalendarInfo;//ʱ�ӽṹ�� 

BOOL RTC_Init(VOID);        //��ʼ��RTC,FALSE,ʧ��;TRUE,�ɹ�;  
U8 RTC_Set(U16 syear,U8 smon,U8 sday,U8 hour,U8 min,U8 sec);//����ʱ��	
U8 RTC_Get(VOID);//����ʱ��

#endif

















