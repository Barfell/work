#include <includes.h>



int test(void)
{  
  /* RTC configuration */
  RTC_Config();
  /* Enable WKUP pin  */
  PWR_WakeUpPinCmd(ENABLE);
  while (1);
}




void RTC_Config(void)
{
	
	RTC_InitTypeDef RTC_InitStructure;
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	PWR_ClearFlag(PWR_FLAG_WU);


	/* Check if the StandBy flag is set */
	if (PWR_GetFlagStatus(PWR_FLAG_SB) != RESET)
	{
		PWR_ClearFlag(PWR_FLAG_SB);
		RTC_WaitForSynchro();
	}
	else
	{
		RCC_BackupResetCmd(ENABLE);
		RCC_BackupResetCmd(DISABLE);

	#if defined (RTC_CLOCK_SOURCE_LSI)
		RCC_LSICmd(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	#elif defined (RTC_CLOCK_SOURCE_LSE)
		RCC_LSEConfig(RCC_LSE_ON);
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	#endif
	
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForSynchro();
	/* Set the RTC time base to 1s */
	RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
	RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
	RTC_InitStructure.RTC_SynchPrediv = 0x00FF;
	if (RTC_Init(&RTC_InitStructure) == ERROR)
	{
	  while(1);
	}
	/* Set the time to 01h 00mn 00s AM */
	RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
	RTC_TimeStructure.RTC_Hours   = 0x00;
	RTC_TimeStructure.RTC_Minutes = 0x00;
	RTC_TimeStructure.RTC_Seconds = 0x00;  
	if(RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure) == ERROR)
	{
	  while(1);
	}
//	RTC_DateStructure.RTC_Date    = 0x01;
//	RTC_DateStructure.RTC_Month   = 0x01;
//	RTC_DateStructure.RTC_WeekDay = 0x31;
//	RTC_DateStructure.RTC_Year    = 0x01;
//	if(RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure) == ERROR)
//	{
//	  while(1);
//	}
  }

  /* Clear RTC Alarm Flag */ 
  RTC_ClearFlag(RTC_FLAG_ALRAF);
}

