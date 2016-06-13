#include <includes.h>

extern unsigned int SCT_WakeUpTime;
#define BKP_RES_KEY  0X5533

//��ȡʱ��
char* get_time(void)
{  
	char stringyear[3]     ={'\0'};
	char stringmounth[3]   ={'\0'};
	char stringdate[3]     ={'\0'};
	char stringhour[3]     ={'\0'};
	char stringmin[3]      ={'\0'};
	char stringsec[3]      ={'\0'};
	char time[100]         ={'\0'};
	RTC_TimeTypeDef   	RTC_GetTimeStructure;
	RTC_DateTypeDef 	RTC_GetDateStructure;

			RTC_GetTime(RTC_Format_BCD, &RTC_GetTimeStructure);
			RTC_GetDate(RTC_Format_BCD, &RTC_GetDateStructure);

			hextostr(stringyear,  RTC_GetDateStructure.RTC_Year);
			hextostr(stringmounth,RTC_GetDateStructure.RTC_Month);
			hextostr(stringdate,  RTC_GetDateStructure.RTC_Date);
			hextostr(stringhour,  RTC_GetTimeStructure.RTC_Hours);
			hextostr(stringmin,   RTC_GetTimeStructure.RTC_Minutes);
			hextostr(stringsec,   RTC_GetTimeStructure.RTC_Seconds);

	sprintf(time,"20%s-%s-%s-%s:%s:%s",stringyear, stringmounth, stringdate, stringhour, stringmin, stringsec);//һ��20���ֽ�
	return time;
}







//RTC���ó��ڲ������ⲿʱ��
unsigned char RTC_Config(rtc_clk rtcclk)
{
  RTC_InitTypeDef RTC_InitStructure;
	u16 retry=0X1FFF; 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  PWR_BackupAccessCmd(ENABLE);

	
	if(RTC_ReadBackupRegister(RTC_BKP_DR0) != BKP_RES_KEY)//�����޸��ˣ����ٴν�������
		{
			if(rtcclk == extrnal)
			{
				/* Enable the LSE OSC */
				RCC_LSEConfig(RCC_LSE_ON);
				/* Wait till LSE is ready */  
				while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
				{
				retry++;
				DelayMs_Sft(10);
				}
				if(retry==0)return 1;

				RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
				RCC_RTCCLKCmd(ENABLE);
				RTC_WaitForSynchro();
			}
			if(rtcclk == inner)
			{
				RCC_LSICmd(ENABLE); //�����ڲ�����
				while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
				RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
				RCC_RTCCLKCmd(ENABLE);
				RTC_WaitForSynchro();
			}
			RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
			RTC_InitStructure.RTC_SynchPrediv = 0xFF;
			RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
			RTC_Init(&RTC_InitStructure);
			set_time(0x10,0x03,0x04,0x0E,0x0F,0x15,0x01,RTC_H12_PM);
		}	
		return 0;
}

//����ʱ��
// RTC_H12_AM                     ((uint8_t)0x00)
// RTC_H12_PM                     ((uint8_t)0x40)
void set_time(	unsigned char year,
				unsigned char mounth,
				unsigned char day,
				unsigned char hour,
				unsigned char min,
				unsigned char sec,
				unsigned char week,
				unsigned char ampm)
{
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	
	RTC_DateStructure.RTC_Year = year;
	RTC_DateStructure.RTC_Month = mounth;
	RTC_DateStructure.RTC_Date = day;
	RTC_DateStructure.RTC_WeekDay = week;
	//����ʱ��
	RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure);
	
	
	if(ampm == 1)
	{
		RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
	}
	else
	{
		RTC_TimeStructure.RTC_H12     = RTC_H12_PM;
	}
	RTC_TimeStructure.RTC_Hours   = hour;
	RTC_TimeStructure.RTC_Minutes = min;
	RTC_TimeStructure.RTC_Seconds = sec; 
	RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);   

	RTC_WriteBackupRegister(RTC_BKP_DR0, BKP_RES_KEY);
}








//��������,�೤ʱ����� 1s-23h
void set_alarm(	unsigned char hour,
				unsigned char min,
				unsigned char sec)
{
	RTC_DateTypeDef 	RTC_GetDateStructure;
	RTC_TimeTypeDef   	RTC_GetTimeStructure;
	RTC_AlarmTypeDef    RTC_AlarmStructure;
	RTC_TimeTypeDef     RTC_TimeStructure;
	NVIC_InitTypeDef    NVIC_InitStructure;
	EXTI_InitTypeDef    EXTI_InitStructure;
	
	RTC_AlarmCmd(RTC_Alarm_A,DISABLE);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line17;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	RTC_ClearITPendingBit(RTC_IT_ALRA);
    EXTI_ClearITPendingBit(EXTI_Line17);
	
	RTC_GetTime(RTC_Format_BIN, &RTC_GetTimeStructure);
	RTC_GetDate(RTC_Format_BIN, &RTC_GetDateStructure);
	//���ӽṹ��
	RTC_AlarmStructure.RTC_AlarmDateWeekDay = RTC_GetDateStructure.RTC_WeekDay;//��������
	RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_WeekDay;//ѡ���������ӻ�����������
	RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_None;//����ĳʱ���ʾ�ıȽϣ����ﲻ���Σ�ȫ���Ƚ�
	//ʱ��ṹ��
	RTC_TimeStructure.RTC_H12 = RTC_GetTimeStructure.RTC_H12;
	/////////////////////////////h/////////////////////////////////////////
	if(RTC_GetTimeStructure.RTC_Hours+hour >= 24)//��һ��ʱ�䳬��24h
	{	RTC_TimeStructure.RTC_Hours = RTC_GetTimeStructure.RTC_Hours+hour-24;
		RTC_AlarmStructure.RTC_AlarmDateWeekDay = RTC_AlarmStructure.RTC_AlarmDateWeekDay+1;//����+1
		if(RTC_AlarmStructure.RTC_AlarmDateWeekDay > 7)
			{
				RTC_AlarmStructure.RTC_AlarmDateWeekDay = RTC_AlarmStructure.RTC_AlarmDateWeekDay-7;
			}
	}
	else
	{RTC_TimeStructure.RTC_Hours = RTC_GetTimeStructure.RTC_Hours+hour;}
	/////////////////////////////m/////////////////////////////////////////
	if(RTC_GetTimeStructure.RTC_Minutes+min >= 60 )//��һ��ʱ����һ��Сʱ
	{	
		RTC_TimeStructure.RTC_Minutes = RTC_GetTimeStructure.RTC_Minutes+min-60;
		RTC_TimeStructure.RTC_Hours = RTC_GetTimeStructure.RTC_Hours+hour+1;//h+1
		if(RTC_TimeStructure.RTC_Hours >= 24)//����24h
			{
				RTC_TimeStructure.RTC_Hours = RTC_GetTimeStructure.RTC_Hours-24;
				RTC_AlarmStructure.RTC_AlarmDateWeekDay = RTC_AlarmStructure.RTC_AlarmDateWeekDay+1;
				if(RTC_AlarmStructure.RTC_AlarmDateWeekDay > 7)
					{
						RTC_AlarmStructure.RTC_AlarmDateWeekDay = RTC_AlarmStructure.RTC_AlarmDateWeekDay-7;
					}
			}
	}
	else
	{RTC_TimeStructure.RTC_Minutes = RTC_GetTimeStructure.RTC_Minutes+min;}
	/////////////////////////////s/////////////////////////////////////////
	if(RTC_GetTimeStructure.RTC_Seconds+sec >= 60)
	{
		RTC_TimeStructure.RTC_Seconds = RTC_GetTimeStructure.RTC_Seconds+sec-60;
		RTC_TimeStructure.RTC_Minutes = RTC_GetTimeStructure.RTC_Minutes+min+1;
		if(RTC_TimeStructure.RTC_Minutes >= 60)
			{
				RTC_TimeStructure.RTC_Minutes = RTC_TimeStructure.RTC_Minutes-60;
				RTC_TimeStructure.RTC_Hours = RTC_GetTimeStructure.RTC_Hours+hour+1;
				if(RTC_TimeStructure.RTC_Hours >= 24)
				{
					RTC_TimeStructure.RTC_Hours = RTC_TimeStructure.RTC_Hours -24;
					RTC_AlarmStructure.RTC_AlarmDateWeekDay = RTC_AlarmStructure.RTC_AlarmDateWeekDay+1;
					if(RTC_AlarmStructure.RTC_AlarmDateWeekDay > 7)
						{
							RTC_AlarmStructure.RTC_AlarmDateWeekDay = RTC_AlarmStructure.RTC_AlarmDateWeekDay-7;
						}
				}
			}
	}
	else
		{RTC_TimeStructure.RTC_Seconds = RTC_GetTimeStructure.RTC_Seconds+sec;}
	RTC_AlarmStructure.RTC_AlarmTime = RTC_TimeStructure;//time
	
	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStructure);
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);
	RTC_AlarmCmd(RTC_Alarm_A, ENABLE);	
}








//�����жϴ�����
void RTC_Alarm_IRQHandler(void)
{
  if(RTC_GetITStatus(RTC_IT_ALRA) != RESET)
  {
//	  SCT_WakeUpTime = *(unsigned int*)0x0800c000;//��ȡflash�Ķ�ʱʱ�䳤��
//		SCT_WakeUpTime -= 120;
//	  set_alarm((SCT_WakeUpTime/3600), (SCT_WakeUpTime%3600)/60, (SCT_WakeUpTime%3600)%60 );

    RTC_ClearITPendingBit(RTC_IT_ALRA);
    EXTI_ClearITPendingBit(EXTI_Line17);
  } 
}


