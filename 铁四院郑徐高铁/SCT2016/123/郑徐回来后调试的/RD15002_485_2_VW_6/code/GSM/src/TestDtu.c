#include "Serial.h"
#include "Dtu.h" 



#ifdef _SCT001_
STATIC U8 g_szMachineType[] = "SCT001";
#endif
#ifdef _SCT002_
STATIC U8 g_szMachineType[] = "SCT002";
#endif
#ifdef _SCT003_
STATIC U8 g_szMachineType[] = "SCT003";
#endif
#ifdef _SCT004_
STATIC U8 g_szMachineType[] = "SCT004";
#endif
#ifdef _SCT005_
STATIC U8 g_szMachineType[] = "SCT005";
#endif
#ifdef _SCT006_
STATIC U8 g_szMachineType[] = "SCT006";
#endif
#ifdef _SCT007_
STATIC U8 g_szMachineType[] = "SCT007";
#endif



STATIC BOOL g_bUpdate = FALSE;

STATIC BOOL g_bUpdateCmd = FALSE;

STATIC BOOL g_bProtocolMode = TRUE;			//Ĭ��ΪЭ��ģʽ
//STATIC BOOL g_bProtocolMode = FALSE;

BOOL g_bLastDtuWork = FALSE;

STATIC U32 g_u32TimeOut = 50;

STATIC U32 g_u32WriteOffset = 0;

STATIC U8 g_u8DtuRetry = 0;

STATIC U32 g_u32TimeInternal = 60000;

STATIC U32 g_u32AppAddress = STM32_FLASH_APP_ADDR;
STATIC U32 g_u32HardEdition = HARDWARE_EDITION;
STATIC U32 g_u32SoftEdition = SOFTWARE_EDITION;

#define START_SYMBOL		0XFE
#define PROTOCOL_EDITION	0X01
#define DATA_DIRECTION		0X01
#define	MAINCMD_INTERNET 	0X06		//����������
#define	SUBCMD_SENSOR	 	0X0001		//RD15002������
#define	FIRST_END_SYMBOL	 		0X0D
#define	SECOND_END_SYMBOL	 		0X0A

enum
{
	NENCRYPTION_NCOMPRESSION = 0X00,
	ENCRYPTION_NCOMPRESSION,
	NENCRYPTION_COMPRESSION,
	ENCRYPTION_COMPRESSION,
	
};

STATIC VOID DtuConfigure(VOID);

unsigned int SCT_WakeUpTime = 0;





void LowPowerEntry(void)
{
	/*-----------------------------�������---------------------------------------*/
			SCT_WakeUpTime = *(unsigned int*)0x0800c000;//��ȡflash�Ķ�ʱʱ�䳤��
			printf("SCT_WakeUpTime:%d\r\n",SCT_WakeUpTime);
			if(SCT_WakeUpTime < DEFAULT_WKP_TIME || SCT_WakeUpTime > 172800)
				{
					SCT_WakeUpTime = DEFAULT_WKP_TIME;
					FLASH_Unlock();
					while(MCUFlashErase(FLASH_Sector_3) != 1);//��Ŷ�ʱʱ��
					FLASH_ProgramWord(0x0800c000,SCT_WakeUpTime);
					FLASH_Lock();
				}
			set_alarm((SCT_WakeUpTime/3600), (SCT_WakeUpTime%3600)/60, (SCT_WakeUpTime%3600)%60 );
				
				
			SW_12V(0);//��Դ
			SW_5V(0);//������Դ�����ڼ��ز�
			DtuPwrOff();
			UartDeinit(USART1);
			UartDeinit(USART2);
			UartDeinit(USART3);
			//GPIOLowperMode();
			SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;//��Ҫ�ر�SYSTICK
				
				
			PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);	//ֹͣģʽ���Ѻ��������Ĺ���
			/*----------------------------���ѻ���--------------------------------------*/
			SetClock();//���ø���CPUʱ��
			OsInit();
//			bsp_io_init();
//			SW_12V(1);
//			SW_5V(1);
//			DtuInit();
//			UartInit(USART1);
//			UartInit(USART2);
//			UartInit(USART3);
//			voltage_adc_init();
//			get_dev_voltage(get_adc_value());
//			FreqModuleInit();
//			LTC2402Init();
//			get_time();
//			RTC_AlarmCmd(RTC_Alarm_A, DISABLE);	
//			GetFreq(1);
}


STATIC VOID HandleDataPackage(U8 *pBuf, U16 u16Length)
{
	if(g_bUpdateCmd == FALSE)	
	{
		if(g_bProtocolMode == TRUE)
		{
			U32 *pData;
			U32 u32Length;
			U32 u32TotalPackageNumber = 0;//�ܵİ���
			U32 u32CurrentPackageNumber = 0;//��ǰ����
			U32 u32CrcValue;
			U16 u16Loop;
			U8 *szData;
			u32Length = u16Length + 19;
			
			pData = malloc(u32Length*4);
			
			if(pData != NULL)
			{
				for(u16Loop = 0; u16Loop < u32Length; u16Loop++)
				{
					pData[u16Loop] = pBuf[u16Loop];
				}
				//u32CrcValue = HardGenCrc32(pData, u16Length);
				
				u32CrcValue = SoftGenCrc32(pData, u16Length);
				free(pData);
			}
			else
			{
				EnterException(ERR_MALLOC_FAIL);
			}
			//���ϲ�����������CRCУ��ֵ
			
			
			
			szData = malloc(u16Length + 25);
			if(szData == NULL)
			{
				EnterException(ERR_MALLOC_FAIL);
			}
			szData[0] = START_SYMBOL;					//FE
			szData[1] = PROTOCOL_EDITION;				//01
			szData[2] = HIBYTE(HIWORD(u32Length));		//����
			szData[3] = LOBYTE(HIWORD(u32Length));		//����
			szData[4] = HIBYTE(LOWORD(u32Length));		//����
			szData[5] = LOBYTE(LOWORD(u32Length));		//����
			szData[6] = DATA_DIRECTION;					//����
			szData[7] = MAINCMD_INTERNET;				//������
			szData[8] = HIBYTE(SUBCMD_SENSOR);			//������
			szData[9] = LOBYTE(SUBCMD_SENSOR);			//������
			szData[10] = NENCRYPTION_NCOMPRESSION;		//�������
			szData[11] = HIBYTE(HIWORD(u32TotalPackageNumber));//�������
			szData[12] = LOBYTE(HIWORD(u32TotalPackageNumber));//�������
			szData[13] = HIBYTE(LOWORD(u32TotalPackageNumber));//�������
			szData[14] = LOBYTE(LOWORD(u32TotalPackageNumber));//�������
			szData[15] = HIBYTE(HIWORD(u32CurrentPackageNumber));//��ǰ�����
			szData[16] = LOBYTE(HIWORD(u32CurrentPackageNumber));//��ǰ�����
			szData[17] = HIBYTE(LOWORD(u32CurrentPackageNumber));//��ǰ�����
			szData[18] = LOBYTE(LOWORD(u32CurrentPackageNumber));//��ǰ�����
			memcpy(szData + 19, pBuf, u16Length);
			
			szData[19 + u16Length] = HIBYTE(HIWORD(u32CrcValue));
			szData[20 + u16Length] = LOBYTE(HIWORD(u32CrcValue));
			szData[21 + u16Length] = HIBYTE(LOWORD(u32CrcValue));
			szData[22 + u16Length] = LOBYTE(LOWORD(u32CrcValue));
			
			szData[23 + u16Length] = FIRST_END_SYMBOL;			//��������
			
			szData[24 + u16Length] = SECOND_END_SYMBOL;			//��������
			
			UsartSend(USART2, szData, u32Length + 6);
		
			UsartSend(USART1, szData, u32Length + 6);

			free(szData);
		}
		else
		{
			UsartSend(USART2, pBuf, u16Length);

			UsartSend(USART1, pBuf, u16Length);
		}
	}
	else
	{

		UsartSend(USART2, pBuf, u16Length);
		
		UsartSend(USART1, pBuf, u16Length);
		
		g_bUpdateCmd = FALSE;
	
	}
}


STATIC BOOL SendAndWaitDtuDataProc(U8 *pBuf, U16 u16Length)
{
	U32 u32Tick=0;
	
	U32 u32Count=0;
	
	S32 s32Count=0;
	
	U8 szData[100]={'\0'};
	
	BOOL bRet = FALSE;
	
	Init(pUart2QueueInfo);
	
	UsartSend(USART2, pBuf, u16Length);
	
	u32Tick = GetTickCount();
	
	if(memcmp(pBuf, "AT+SAVEPARAM", 12) == 0)
	{
		u32Count = 5000;
	}
	else
	{
		u32Count = 1000;
	}
	
	do
	{
		if(GetQueueLength(pUart2QueueInfo))
		{
			s32Count = GetTickCount() - GetUartReceiveTime(USART2);
			if(s32Count > 40)
			{
				ReadUsartData(USART2, szData, &u16Length);
				if(strstr((char *)szData, "OK") != FALSE)
				{
					bRet = TRUE;
					g_u8DtuRetry = 0;
					break;
				}
			}
		}
	}while( (GetTickCount() - u32Tick) < u32Count );
	
	DelayMs(500);
	
	if(bRet == FALSE)
	{
		g_u8DtuRetry++;
		if(g_u8DtuRetry > 45)
		{
			g_u8DtuRetry = 0;
			UartDeinit(USART1);
			UartDeinit(USART2);
			UartDeinit(USART3);
			NVIC_SystemReset();
		}
	}
	
	return bRet;
}



void SendAndWait485DataProc(U8 *pBuf, U16 u16Length, U8 *pData)
{
	U32 u32Tick=0;
	U32 u32Count=400;
	S32 s32Count=0;
	
	U8 szData[100]={'\0'};
	
	
	Init(pUart3QueueInfo);
	UsartSend(USART3, pBuf, u16Length);
	u32Tick = GetTickCount();
	do
	{
		if(GetQueueLength(pUart3QueueInfo))
		{
			s32Count = GetTickCount() - GetUartReceiveTime(USART3);
			if(s32Count > 40)
			{
				ReadUsartData(USART3, szData, &u16Length);
				memcpy(pData,szData,sizeof(szData));
			}
		}
	}while( (GetTickCount() - u32Tick) < u32Count );
		
}







STATIC VOID DtuConfigure(VOID)
{
	U8 szData[100] = {'\0'};
	
	memset(szData, 0, sizeof(szData));
	memcpy((char *)szData, "+++", 3);//enter AT mode
	while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
	printf("+++ ok\r\n");
	memset(szData, 0, sizeof(szData));
	sprintf((char *)szData, "AT+LOGIN=admin\r\n");//login
	while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
	printf("AT+LOGIN=admin ok\r\n");
	memset(szData, 0, sizeof(szData));
	sprintf((char *)szData, "AT+SETPARAM=RTUPMPL,1024\r\n");
	while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
	printf("AT+SETPARAM=RTUPMPL,1024 ok\r\n");
	memset(szData, 0, sizeof(szData));
	sprintf((char *)szData,"AT+SETPARAM=OPPDIO,OFF\r\n");
	while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
	printf("AT+SETPARAM=OPPDIO,OFF\r\n");
	memset(szData, 0, sizeof(szData));
	sprintf((char *)szData, "AT+SETPARAM=RTUPDPTI,50\r\n");
	while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
	printf("AT+SETPARAM=RTUPDPTI,50 ok\r\n");
		

	
	memset(szData, 0, sizeof(szData));
	sprintf((char *)szData, "AT+SETCHL=1\r\n");//set channel
	while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
	printf("AT+SETCHL=1\r\n");
	memset(szData, 0, sizeof(szData));
	sprintf((char *)szData,"AT+SETPARAM=CHPCT,TCP\r\n");
	while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
	printf("AT+SETPARAM=CHPCT,TCP ok\r\n");
	memset(szData, 0, sizeof(szData));
	sprintf((char *)szData, "AT+SETPARAM=CHPDTUP,4003\r\n");//dtu port

	while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
	printf("AT+SETPARAM=CHPDTUP,4003 ok\r\n");
	
#ifdef IP_INTERVIEW
		memset(szData, 0, sizeof(szData));
		sprintf((char *)szData, TEST_IP);//dsc ip
		while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
		printf("AT+SETPARAM=CHPDSCIP,TEST_IP ok\r\n");
		memset(szData, 0, sizeof(szData));
		sprintf((char *)szData,"AT+SETPARAM=CHPDSCD,\r\n");//dsc domain  14g542w137.iok.la
		while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
		printf("AT+SETPARAM=CHPDSCD, ok\r\n");
		memset(szData, 0, sizeof(szData));
		sprintf((char *)szData, TEST_PORT);//dsc port
		while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
		printf("AT+SETPARAM=CHPDSCP,PORT ok\r\n");
#endif

#ifdef DOMAIN_INTERVIEW
		memset(szData, 0, sizeof(szData));
		sprintf((char *)szData, "%s\r\n", "AT+SETPARAM=CHPDSCIP,0.0.0.0");//dsc ip
		while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
		memset(szData, 0, sizeof(szData));
		sprintf((char *)szData, "%s\r\n", DOMAIN);//dsc domain
		while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
		memset(szData, 0, sizeof(szData));
		sprintf((char *)szData, "%s\r\n", DOMAIN_PORT);//dsc port
		while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
#endif

	
	memset(szData, 0, sizeof(szData));
	sprintf((char *)szData,"AT+SAVEPARAM\r\n");
	while(SendAndWaitDtuDataProc(szData, strlen((char *)szData)) == FALSE);
	printf("AT+SAVEPARAM ok\r\n");
	
	
	memset(szData, 0, sizeof(szData));
	sprintf((char *)szData,"AT+RESET\r\n");
	UsartSend(USART2, szData, strlen((char *)szData));
}






/************************************************************************************************/
STATIC VOID HandleCmdProc(U8 *pBuf, U16 u16Length)
{
	U8 szData[50];
	U8 szBuf[4] = {0};
	//FLASH_Status FLASHStatus = FLASH_COMPLETE;
	if(u16Length == 7)//-------------------------��������
	{
		g_bUpdateCmd = TRUE;
		
		if((pBuf[0] == 0xfe) && (pBuf[1] == 0x00) && (pBuf[6] == 0xfe))//���������������
		{
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "app erase exflash over\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x01) && (pBuf[6] == 0xfe))//��������ģʽ
		{
			g_bUpdate = TRUE;
			g_u32TimeOut = 200;
			g_u32WriteOffset = 0;
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "app enter update mode\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x02) && (pBuf[6] == 0xfe))//�˳�����ģʽ
		{
			g_bUpdate = FALSE;
			g_u32TimeOut = 20;
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "app exit update mode\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x03) && (pBuf[6] == 0xfe))//д�����ɹ���־
		{
			FLASH_Unlock();///Flash����
			while(MCUFlashErase(FLASH_Sector_6) != 1);//ֱ������
			DelayMs(2);
			FLASH_ProgramWord(UPDATE_FLAG_ADDRESS, 0x55AA55AA);//д��ɹ����
			FLASH_ProgramWord(UPDATE_FLAG_ADDRESS + 4, g_u32AppAddress);//д��Ӧ�õ�ַ���
			FLASH_ProgramWord(UPDATE_FLAG_ADDRESS + 8, g_u32HardEdition);//д��Ӳ���汾
			FLASH_ProgramWord(UPDATE_FLAG_ADDRESS + 12, g_u32SoftEdition);//д������汾
			FLASH_Lock();	
			
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "app set flag ok\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x04) && (pBuf[6] == 0xfe))//Ӧ�õ�ַ
		{
			g_u32AppAddress = MAKELONG(MAKEWORD(pBuf[2], pBuf[3]), MAKEWORD(pBuf[4], pBuf[5]));
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "app set app address ok\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x05) && (pBuf[6] == 0xfe))//Ӳ���汾
		{
			g_u32HardEdition = MAKELONG(MAKEWORD(pBuf[2], pBuf[3]), MAKEWORD(pBuf[4], pBuf[5]));
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "app set hard edition ok\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x06) && (pBuf[6] == 0xfe))//����汾
		{
			g_u32SoftEdition = MAKELONG(MAKEWORD(pBuf[2], pBuf[3]), MAKEWORD(pBuf[4], pBuf[5]));
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "app set soft edition ok\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x07) && (pBuf[6] == 0xfe))//����
		{	
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "app restart\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
			DelayMs(1000);
			UartDeinit(USART1);
			UartDeinit(USART2);
			UartDeinit(USART3);
			GPIOLowperMode();
			NVIC_SystemReset();
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x08) && (pBuf[6] == 0xfe))//��ȡ�������ݳ���
		{
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "app update = %d Bytes\r\n", g_u32WriteOffset);
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x09) && (pBuf[6] == 0xfe))//����������־
		{
			FLASH_Unlock();///Flash����
			while(MCUFlashErase(FLASH_Sector_11) != 1);//����
			DelayMs(2);
			FLASH_Lock();	
			
			memset(szData, 0, sizeof(szData));
			
			if((szBuf[0] == 0xAA) && (szBuf[1] == 0x55) && (szBuf[2] == 0xAA) && (szBuf[3] == 0x55))
			{
				sprintf((char *)szData, "app erase flag error\r\n");
			}
			else
			{
				sprintf((char *)szData, "app erase flag ok\r\n");
			}
			HandleDataPackage(szData, strlen((char *)szData));
		}	
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0xf1) && (pBuf[6] == 0xfe))//����ʱ����ģʽ
		{
			g_u32TimeInternal = MAKELONG(MAKEWORD(pBuf[5], pBuf[4]), MAKEWORD(pBuf[3], pBuf[2]));
			
			SCT_WakeUpTime = g_u32TimeInternal;
			
			FLASH_Unlock();///Flash����
				while(MCUFlashErase(FLASH_Sector_3) != 1);//��Ŷ�ʱʱ��
				FLASH_ProgramWord(0x0800c000,SCT_WakeUpTime);
			FLASH_Lock();
			
			g_bLastDtuWork = FALSE;//������֮��ǿ�Ʒ�����������
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "Set Interval mode success, Interval:%d s",SCT_WakeUpTime);
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x0B) && (pBuf[6] == 0xfe))//��ȡ��ǰģʽ
		{
			memset(szData, 0, sizeof(szData));
			
			if(g_bProtocolMode == TRUE)
			{
				sprintf((char *)szData, "App Protocol Mode\r\n");
			}
			else
			{
				sprintf((char *)szData, "App Un-Protocol Mode\r\n");
			}
			
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x0C) && (pBuf[6] == 0xfe))//���÷�Э��ģʽ
		{
			g_bProtocolMode = FALSE;
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "Un-Protocol Mode\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x0D) && (pBuf[6] == 0xfe))//����Э��ģʽ
		{
			g_bProtocolMode = TRUE;
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "Protocol Mode\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
//		
		else
		{
			if(g_bUpdate == TRUE) 
			{		
				Flash_w_Length(g_u32WriteOffset, (char *)szData, u16Length);
				g_u32WriteOffset = g_u32WriteOffset + u16Length;
				memset(szData, 0, sizeof(szData));
				sprintf((char *)szData, "app receive = %d\r\n",u16Length);
				HandleDataPackage(szData, strlen((char *)szData));			
			}
			else
			{
				g_bUpdateCmd = FALSE;
			}
		}
	}
	else if(u16Length == 10)//����ʱ������
	{
		g_bUpdateCmd = TRUE;
		
		if((pBuf[0] == 0xfe) && (pBuf[1] == 0xf2) && (pBuf[9] == 0xfe))//����ʱ��
		{
			U16 u16year;
			U8 u8month, u8day, u8hour, u8minute, u8second;
			u16year = MAKEWORD(pBuf[3], pBuf[2]);
			u16year = u16year - 2000;//2015 - 2000
			u8month = pBuf[4];
			u8day   = pBuf[5];
			u8hour  = pBuf[6];
			u8minute = pBuf[7];
			u8second = pBuf[8];
			set_time(u16year,u8month,u8day,u8hour,u8minute,u8second,1,1);
			g_bLastDtuWork = FALSE;//������֮��ǿ�Ʒ�����������
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "Set time success,time:%s",get_time());
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else
		{
			if(g_bUpdate == TRUE) 
			{
				
				Flash_w_Length(g_u32WriteOffset, (char *)szData, u16Length);
				g_u32WriteOffset = g_u32WriteOffset + u16Length;
				memset(szData, 0, sizeof(szData));
				sprintf((char *)szData, "app receive = %d\r\n",u16Length);
				HandleDataPackage(szData, strlen((char *)szData));
				
			}
			else
			{
				g_bUpdateCmd = FALSE;
			}
		}
	}
	else
	{
		if(g_bUpdate == TRUE) 
		{
			Flash_w_Length(g_u32WriteOffset, (char *)szData, u16Length);
			g_u32WriteOffset = g_u32WriteOffset + u16Length;
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "app receive = %d\r\n",u16Length);
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else
		{
			g_bUpdateCmd = FALSE;
		}
	}
}

VOID ReadLockId(U32 *pData)
{
	//��ȡCPUΨһID
	pData[0]=*(vu32*)(0x1fff7a10);
	pData[1]=*(vu32*)(0x1fff7a14);
	pData[2]=*(vu32*)(0x1fff7a18);
}

















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HandleBoardInfo(U8 *pBuf)
{
	U32 szId[3];
	U8 szData[50] = {0};
	ReadLockId(szId);
	sprintf((char *)szData, "#%s-ID=0x%x%x%x\r\n", g_szMachineType, szId[2], szId[1], szId[0]);
	memcpy(pBuf, szData, strlen((char *)szData));
	memset(szData,0,50);
}

void HandleADCProc(U8 *pBuf)
{
    U8 szData[50] = {0};
    sprintf((char *)szData, "#%s-Inner Voltage=%.3fV\r\n", g_szMachineType, get_dev_voltage(get_adc_value()));
		memcpy(pBuf, szData, strlen((char *)szData));
		memset(szData,0,50);
}

void HandleModeProc(U8 *pBuf)
{
		U8 szData[50] = {0};
		SCT_WakeUpTime = *(unsigned int*)0x0800c000;//��ȡflash�Ķ�ʱʱ�䳤��
		sprintf((char *)szData, "#%s-Interval Mode=%d sec\r\n", g_szMachineType, SCT_WakeUpTime);
		memcpy(pBuf, szData, strlen((char *)szData));
		memset(szData,0,50);
}

void HandleRTCProc(U8 *pBuf)
{
    U8 szData[50];
    sprintf((char *)szData, "#%s\r\n",get_time());
    memcpy(pBuf, szData, strlen((char *)szData));
	memset(szData,0,50);
}


void HandleTemperatureProc(U8 *pBuf)
{
	U8 u8Channel;
	unsigned char temp[100] ={0};
	unsigned char szData[800] ={0};
	unsigned char i = 0;
	float Temperature = 0;
	for(u8Channel = 1; u8Channel < 9; u8Channel++)
	{
		while(Temperature == 0)
		{
			Temperature = GetTemperature(LTC2402_GetResistance(u8Channel));//��ȡ��ͨ�����¶�
			i++;
			if(i > 3) //���Զ�ȡ5���¶ȣ��Է�ֹ��ȡ����
				{i = 0;break;}
			else
				{DelayMs_Sft(100);}
		}
		sprintf((char *)temp, "#%s-CH%d:T-%.3f\r\n",g_szMachineType, u8Channel, Temperature);
		Temperature = 0;
		strcat((char *)szData, (char *)temp);
		memset(temp,0,100);
		Temperature = 0;
		DelayMs(150);
	}
	
	memcpy(pBuf, szData, strlen((char *)szData));
	memset(szData,0,800);
	memset(temp,0,100);
}


void HandleVWProc(U8 *pBuf)
{
	unsigned char temp[60]   = {0};
	unsigned char szData[500] = {0};
	unsigned char i =0;

	float VM_Value=0;
	float T_Value =0;
	memset(szData,0,500);
	memset(temp, 0, 60);

	
	
	
	
#ifdef S485_2_VW_6
		VM_Value = GetFreq(1);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(1));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,1, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)szData, (char *)temp);
		memset(temp,0,60);
	/*-----------------------------------*/
		VM_Value = GetFreq(2);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(2));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,2, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)szData, (char *)temp);
		memset(temp,0,60);
	/*-----------------------------------*/
		VM_Value = GetFreq(3);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(3));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,3, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)szData, (char *)temp);
		memset(temp,0,60);
	/*-----------------------------------*/
		VM_Value = GetFreq(4);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(4));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,4, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)szData, (char *)temp);
		memset(temp,0,60);
	/*-----------------------------------*/
		VM_Value = GetFreq(5);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(5));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,5, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)szData, (char *)temp);
		memset(temp,0,60);
	/*-----------------------------------*/
		VM_Value = GetFreq(6);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(6));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,6, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)szData, (char *)temp);
		memset(temp,0,60);
#endif

#ifdef S485_6_VW_2
		VM_Value = GetFreq(1);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(1));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,1, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)szData, (char *)temp);
		memset(temp,0,60);
	/*-----------------------------------*/
		VM_Value = GetFreq(2);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(2));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,2, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)szData, (char *)temp);
		memset(temp,0,60);

#endif

#ifdef S485_4_VW_4
		VM_Value = GetFreq(2);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(2));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,2, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)szData, (char *)temp);
		memset(temp,0,60);
	/*-----------------------------------*/
		VM_Value = GetFreq(4);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(4));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,4, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)szData, (char *)temp);
		memset(temp,0,60);
	/*-----------------------------------*/
		VM_Value = GetFreq(6);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(6));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,6, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)szData, (char *)temp);
		memset(temp,0,60);
	/*-----------------------------------*/
		VM_Value = GetFreq(8);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(8));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,8, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)szData, (char *)temp);
		memset(temp,0,60);
#endif
	
	memcpy(pBuf, szData, strlen((char *)szData));
	memset(szData,0,500);
	memset(temp,0,60);
	
}


void Handle485Proc(U8 *pBuf)
{
	unsigned char temp[60]   = {0};
	unsigned char szData[500] = {0};
	unsigned char i =0;

	float VM_Value=0;
	float T_Value =0;
	
	
	
	
	
	unsigned char Temp485Str[50] = {0};
	unsigned char ExTempStr[100] = {0};
	U16 Temp485Strlength = 0;
	unsigned char RetryTimes = 0;
	unsigned char RecivedData[400] = {0};
	
	memset(szData,0,500);
	memset(temp, 0, 60);
	
#ifdef S485_6_VW_2
	while(Temp485Str[0] != '$' && RetryTimes < 4)
	{
		memset(Temp485Str,0,50);
		DT485_Get((unsigned char *)SENSOR_TYPE,(unsigned char *)DT_SENSOR_ADDR1,(unsigned char *)Temp485Str,&Temp485Strlength);
		RetryTimes++;
	}
	sprintf((char *)ExTempStr, "#%s-CH%d:%s\r\n", (char *)g_szMachineType, 3, (char *)Temp485Str);
	//printf("times:%d-485:%s\r\n",RetryTimes,ExTempStr);
	Temp485Strlength = 0;
	RetryTimes = 0;
	strcat((char *)RecivedData,(char *)ExTempStr);
	memset(Temp485Str,0,50);
	memset(ExTempStr,0,100);		
		
	
	while(Temp485Str[0] != '$' && RetryTimes < 4)
	{
		memset(Temp485Str,0,50);
		DT485_Get((unsigned char *)SENSOR_TYPE,(unsigned char *)DT_SENSOR_ADDR2,(unsigned char *)Temp485Str,&Temp485Strlength);
		RetryTimes++;
	}
	sprintf((char *)ExTempStr, "#%s-CH%d:%s\r\n", (char *)g_szMachineType, 4, (char *)Temp485Str);
	//printf("times:%d-485:%s\r\n",RetryTimes,ExTempStr);
	Temp485Strlength = 0;
	RetryTimes = 0;
	strcat((char *)RecivedData,(char *)ExTempStr);
	memset(Temp485Str,0,50);
	memset(ExTempStr,0,100);
	
	
	while(Temp485Str[0] != '$' && RetryTimes < 4)
	{
		memset(Temp485Str,0,50);
		DT485_Get((unsigned char *)SENSOR_TYPE,(unsigned char *)DT_SENSOR_ADDR3,(unsigned char *)Temp485Str,&Temp485Strlength);
		RetryTimes++;
	}
	sprintf((char *)ExTempStr, "#%s-CH%d:%s\r\n", (char *)g_szMachineType, 5, (char *)Temp485Str);
	//printf("times:%d-485:%s\r\n",RetryTimes,ExTempStr);
	Temp485Strlength = 0;
	RetryTimes = 0;
	strcat((char *)RecivedData,(char *)ExTempStr);
	memset(Temp485Str,0,50);
	memset(ExTempStr,0,100);
	
	
	while(Temp485Str[0] != '$' && RetryTimes < 4)
	{
		memset(Temp485Str,0,50);
		DT485_Get((unsigned char *)SENSOR_TYPE,(unsigned char *)DT_SENSOR_ADDR4,(unsigned char *)Temp485Str,&Temp485Strlength);
		RetryTimes++;
	}
	sprintf((char *)ExTempStr, "#%s-CH%d:%s\r\n", (char *)g_szMachineType, 6, (char *)Temp485Str);
	//printf("times:%d-485:%s\r\n",RetryTimes,ExTempStr);
	Temp485Strlength = 0;
	RetryTimes = 0;
	strcat((char *)RecivedData,(char *)ExTempStr);
	memset(Temp485Str,0,50);
	memset(ExTempStr,0,100);
	
	
	while(Temp485Str[0] != '$' && RetryTimes < 4)
	{
		memset(Temp485Str,0,50);
		DT485_Get((unsigned char *)SENSOR_TYPE,(unsigned char *)DT_SENSOR_ADDR5,(unsigned char *)Temp485Str,&Temp485Strlength);
		RetryTimes++;
	}
	sprintf((char *)ExTempStr, "#%s-CH%d:%s\r\n", (char *)g_szMachineType, 7, (char *)Temp485Str);
	//printf("times:%d-485:%s\r\n",RetryTimes,ExTempStr);
	Temp485Strlength = 0;
	RetryTimes = 0;
	strcat((char *)RecivedData,(char *)ExTempStr);
	memset(Temp485Str,0,50);
	memset(ExTempStr,0,100);
	
	
	while(Temp485Str[0] != '$' && RetryTimes < 4)
	{
		memset(Temp485Str,0,50);
		DT485_Get((unsigned char *)SENSOR_TYPE,(unsigned char *)DT_SENSOR_ADDR6,(unsigned char *)Temp485Str,&Temp485Strlength);
		RetryTimes++;
	}
	sprintf((char *)ExTempStr, "#%s-CH%d:%s\r\n", (char *)g_szMachineType, 8, (char *)Temp485Str);
	//printf("times:%d-485:%s\r\n",RetryTimes,ExTempStr);
	Temp485Strlength = 0;
	RetryTimes = 0;
	strcat((char *)RecivedData,(char *)ExTempStr);
	memset(Temp485Str,0,50);
	memset(ExTempStr,0,100);
#endif
	
#ifdef S485_4_VW_4
	while(Temp485Str[0] != '$' && RetryTimes < 4)
	{
		memset(Temp485Str,0,50);
		DT485_Get((unsigned char *)SENSOR_TYPE,(unsigned char *)DT_SENSOR_ADDR1,(unsigned char *)Temp485Str,&Temp485Strlength);
		RetryTimes++;
	}
	sprintf((char *)ExTempStr, "#%s-CH%d:%s\r\n", (char *)g_szMachineType, 1, (char *)Temp485Str);
	//printf("times:%d-485:%s\r\n",RetryTimes,ExTempStr);
	Temp485Strlength = 0;
	RetryTimes = 0;
	strcat((char *)RecivedData,(char *)ExTempStr);
	memset(Temp485Str,0,50);
	memset(ExTempStr,0,100);
	/*------vw-----*/
	VM_Value = GetFreq(2);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(2));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,2, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)RecivedData, (char *)temp);
		memset(temp,0,60);
	
	
	
	
	while(Temp485Str[0] != '$' && RetryTimes < 4)
	{
		memset(Temp485Str,0,50);
		DT485_Get((unsigned char *)SENSOR_TYPE,(unsigned char *)DT_SENSOR_ADDR2,(unsigned char *)Temp485Str,&Temp485Strlength);
		RetryTimes++;
	}
	sprintf((char *)ExTempStr, "#%s-CH%d:%s\r\n", (char *)g_szMachineType, 3, (char *)Temp485Str);
	//printf("times:%d-485:%s\r\n",RetryTimes,ExTempStr);
	Temp485Strlength = 0;
	RetryTimes = 0;
	strcat((char *)RecivedData,(char *)ExTempStr);
	memset(Temp485Str,0,50);
	memset(ExTempStr,0,100);
	/*------vw-----*/
	VM_Value = GetFreq(4);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(4));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,4, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)RecivedData, (char *)temp);
		memset(temp,0,60);
		
		
	
	while(Temp485Str[0] != '$' && RetryTimes < 4)
	{
		memset(Temp485Str,0,50);
		DT485_Get((unsigned char *)SENSOR_TYPE,(unsigned char *)DT_SENSOR_ADDR3,(unsigned char *)Temp485Str,&Temp485Strlength);
		RetryTimes++;
	}
	sprintf((char *)ExTempStr, "#%s-CH%d:%s\r\n", (char *)g_szMachineType, 5, (char *)Temp485Str);
	//printf("times:%d-485:%s\r\n",RetryTimes,ExTempStr);
	Temp485Strlength = 0;
	RetryTimes = 0;
	strcat((char *)RecivedData,(char *)ExTempStr);
	memset(Temp485Str,0,50);
	memset(ExTempStr,0,100);
	/*------vw-----*/
	VM_Value = GetFreq(6);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(6));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,6, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)RecivedData, (char *)temp);
		memset(temp,0,60);
		
		
		
	
	while(Temp485Str[0] != '$' && RetryTimes < 4)
	{
		memset(Temp485Str,0,50);
		DT485_Get((unsigned char *)SENSOR_TYPE,(unsigned char *)DT_SENSOR_ADDR4,(unsigned char *)Temp485Str,&Temp485Strlength);
		RetryTimes++;
	}
	sprintf((char *)ExTempStr, "#%s-CH%d:%s\r\n", (char *)g_szMachineType, 7, (char *)Temp485Str);
	//printf("times:%d-485:%s\r\n",RetryTimes,ExTempStr);
	Temp485Strlength = 0;
	RetryTimes = 0;
	strcat((char *)RecivedData,(char *)ExTempStr);
	memset(Temp485Str,0,50);
	memset(ExTempStr,0,100);
	/*------vw-----*/
	VM_Value = GetFreq(8);
		while(T_Value == 0)
		{
			T_Value = GetTemperature(LTC2402_GetResistance(8));//��ȡ��ͨ�����¶�
			i++;
			if(i>3)
				{i = 0;break;}
			else
				{DelayMs_Sft(300);}
		}
		memset(temp, 0, 60);
		sprintf((char *)temp, "#%s-CH%d:F-%.3f T-%.3f \r\n",g_szMachineType,8, VM_Value, T_Value);
		VM_Value = 0;
		T_Value=0;
		strcat((char *)RecivedData, (char *)temp);
		memset(temp,0,60);
#endif	

	
#ifdef S485_2_VW_6
	while(Temp485Str[0] != '$' && RetryTimes < 4)
	{
		memset(Temp485Str,0,50);
		DT485_Get((unsigned char *)SENSOR_TYPE,(unsigned char *)DT_SENSOR_ADDR1,(unsigned char *)Temp485Str,&Temp485Strlength);
		RetryTimes++;
	}
	sprintf((char *)ExTempStr, "#%s-CH%d:%s\r\n", (char *)g_szMachineType, 7, (char *)Temp485Str);
	//printf("times:%d-485:%s\r\n",RetryTimes,ExTempStr);
	Temp485Strlength = 0;
	RetryTimes = 0;
	strcat((char *)RecivedData,(char *)ExTempStr);
	memset(Temp485Str,0,50);
	memset(ExTempStr,0,100);
	
	
	while(Temp485Str[0] != '$' && RetryTimes < 4)
	{
		memset(Temp485Str,0,50);
		DT485_Get((unsigned char *)SENSOR_TYPE,(unsigned char *)DT_SENSOR_ADDR2,(unsigned char *)Temp485Str,&Temp485Strlength);
		RetryTimes++;
	}
	sprintf((char *)ExTempStr, "#%s-CH%d:%s\r\n", (char *)g_szMachineType, 8, (char *)Temp485Str);
	//printf("times:%d-485:%s\r\n",RetryTimes,ExTempStr);
	Temp485Strlength = 0;
	RetryTimes = 0;
	strcat((char *)RecivedData,(char *)ExTempStr);
	memset(Temp485Str,0,50);
	memset(ExTempStr,0,100);
#endif
	
	
	
	
	
	
	
	memcpy(pBuf,RecivedData,strlen((char *)RecivedData));
	memset(RecivedData,0,400);

}






VOID TestDtu(VOID)
{
	unsigned int CMDTimeTicks  = 0;//��������������ӵ�ʱ��Ƭ
	unsigned int OffLineCounts = 0;//��������˵��˺ܾû�û�����������ٴγ�ʼ��DTU
	
	U8 szData[DTUUARTSIZE]={0};
	unsigned char TemSzData[400];
	U16 u16Length = 0;
	U32 u32Tick = 0;
  S32 s32Count = 0;
	
	DtuConfigure();//����GSM
	u32Tick = GetTickCount();
	g_u32TimeOut = 30;

	
	while(1)
	{
		UsartSend(USART2, "123456\r\n", 8);
		DelayMs(1000);
		
///*-----------------------------------------------------------------------------------------------*/        
//		if(DetectOnline() == TRUE)//������
//		{
//			OffLineCounts = 0;//������߼�ʱ
//			
//			
//			
//			HandleRTCProc(TemSzData);
//			strcat((char *)szData,(char *)TemSzData);
//			memset(TemSzData,0,400);
//			
//			HandleBoardInfo(TemSzData);
//			strcat((char *)szData,(char *)TemSzData);
//			memset(TemSzData,0,400);
//			
//			HandleModeProc(TemSzData);
//			strcat((char *)szData,(char *)TemSzData);
//			memset(TemSzData,0,400);
//			
//			HandleADCProc(TemSzData);
//			strcat((char *)szData,(char *)TemSzData);
//			memset(TemSzData,0,400);
//			
//			
//#ifdef S485_2_VW_6
//			HandleVWProc(TemSzData);
//			strcat((char *)szData,(char *)TemSzData);
//			memset(TemSzData,0,400);
//			Handle485Proc(TemSzData);
//			strcat((char *)szData,(char *)TemSzData);
//			memset(TemSzData,0,400);
//			
//#endif
//			
//			
//#ifdef S485_6_VW_2
//			HandleVWProc(TemSzData);
//			strcat((char *)szData,(char *)TemSzData);
//			memset(TemSzData,0,400);
//			Handle485Proc(TemSzData);
//			strcat((char *)szData,(char *)TemSzData);
//			memset(TemSzData,0,400);
//#endif	
//			
//			
//#ifdef S485_4_VW_4
//			Handle485Proc(TemSzData);
//			strcat((char *)szData,(char *)TemSzData);
//			memset(TemSzData,0,400);
//#endif	

//			
//#ifdef NTC_6
//			HandleTemperatureProc(TemSzData);
//			strcat((char *)szData,(char *)TemSzData);
//			memset(TemSzData,0,400);
//#endif

//			HandleDataPackage(szData,strlen((char *)szData));
//			memset(szData, 0, DTUUARTSIZE);
//			u16Length = 0;
//			DelayMs_Sft(800);

//			
///*---------------------��������ʱ��-------------------------------------*/			
//			CMDTimeTicks = GetTickCount();
//			while(1)
//			{
//				if(   (( GetTickCount() - CMDTimeTicks ) > 1000*DEFAULT_CMD_TIME )  ||   ( DetectOnline() == FALSE )  )//120S�������������״̬
//					{
//						break;
//					}
//				else
//					{
//						if(GetQueueLength(pUart2QueueInfo))//������
//						{
//							CMDTimeTicks = GetTickCount();
//							s32Count = GetTickCount() - GetUartReceiveTime(USART2);
//							if(s32Count > g_u32TimeOut)
//							{
//								ReadUsartData(USART2, szData, &u16Length);
//								HandleCmdProc(szData, u16Length);			//��������
//							}
//						}
//					}
//			}
//			if(DetectOnline() == TRUE)
//			{
///*-----------------------------�������---------------------------------------*/
//				printf("stop mode\r\n");
//				LowPowerEntry();
//				NVIC_SystemReset();
//			}
//		}
///*--------------------------------------offline--------------------------------------------------*/		
//		if(DetectOnline() == FALSE) // ������
//		{
//			s32Count = GetTickCount() - u32Tick;
//			if(s32Count > 1000)
//			{
//				printf("app offline\r\n");
//				memset(szData, 0, DTUUARTSIZE);
//				OffLineCounts ++;
//				if(OffLineCounts > 240)//3����
//					{
//						printf("offline stop mode\r\n");
//						OffLineCounts = 0;								
//								LowPowerEntry();
//								NVIC_SystemReset();
//					}
//				u32Tick = GetTickCount();
//			}
//		}
	}
}


