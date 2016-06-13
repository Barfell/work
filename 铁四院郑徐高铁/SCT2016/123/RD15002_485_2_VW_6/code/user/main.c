#include  <includes.h>
extern unsigned int SCT_WakeUpTime;
int main(void)
{
	char DEVICE_ID[50];
	int ResetTimes = 0;//������������5��
	
	SetClock();//���ø���CPUʱ��
	OsInit();
	bsp_io_init();//IO��
	SW_12V(1);//��Դ
	SW_5V(1);//������Դ�����ڼ��ز�
	DtuInit();//dtu��Դ��ʼ��
	UartInit(USART1);
	UartInit(USART2);
	UartInit(USART3);
	printf("Log Usart Init OK.\r\n");
/*********************************************************/
	FreqModuleInit();
	GetFreq(1);
	LTC2402Init();
	LTC2402_GetResistance(1);
	read_dev_id(DEVICE_ID);
	printf("Dev-ID :%s \r\n",DEVICE_ID);
	voltage_adc_init();
	printf("Inner Voltage :%.3f v\r\n",get_dev_voltage(get_adc_value()));
	while(RTC_Config(extrnal) != 0 );
	printf("RTC time :%s \r\n",get_time());
	
	
	
/***********************Ĭ�϶�ʱʱ��************************/
	SCT_WakeUpTime = *(unsigned int*)0x0800c000;
	if(SCT_WakeUpTime < 10 || SCT_WakeUpTime > 216000 )
		{
			SCT_WakeUpTime = DEFAULT_WKP_TIME;
			FLASH_Unlock();
					while(MCUFlashErase(FLASH_Sector_3) != 1);//��Ŷ�ʱʱ��
					FLASH_ProgramWord(0x0800c000,SCT_WakeUpTime);
			FLASH_Lock();
		}
/***********************����5��ʧ�ܺ��������***************/
//	ResetTimes = *(unsigned char*)(0x08010001);
//	printf("Reset Times:%d\r\n",ResetTimes);
//	if(ResetTimes >8 || ResetTimes < 0)
//		{ResetTimes=0;}
//	ResetTimes += 1;
//	if(ResetTimes == 8)
//		{
//			printf("ResetTimes=8, enter LowPower\r\n");
//			ResetTimes = 0;
//			LowPowerEntry(); 
//		}
//	//�����������
//	FLASH_Unlock();
//				while(MCUFlashErase(FLASH_Sector_4) != 1);
//				FLASH_ProgramByte(0x08010001,ResetTimes);
//	FLASH_Lock();
/********************************************************/
		
		
		
		
	
	while(1)
	{
		TestDtu();
	}
}

