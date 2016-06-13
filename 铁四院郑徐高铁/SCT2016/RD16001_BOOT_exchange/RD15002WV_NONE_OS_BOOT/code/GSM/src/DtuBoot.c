#include "includes.h"


STATIC U8 g_u8FlashType = STM_FLASH;

STATIC BOOL g_bUpdate = FALSE;

STATIC U32 g_u32TimeOut = DTUTIMEOUT1;

STATIC U32 g_u32WriteOffset = 0;

STATIC U32 g_u32AppAddress  = STM32_FLASH_APP_ADDR;
STATIC U32 g_u32HardEdition = HARDWARE_EDITION;
STATIC U32 g_u32SoftEdition = SOFTWARE_EDITION;

STATIC U16 u16PackageNumber = 1;

PQueueInfo pDtuQueueInfo;

U8 *pDtuQueue;
#define START_SYMBOL		0XFE
#define PROTOCOL_EDITION	0X01
#define DATA_DIRECTION		0X01
#define	MAINCMD_INTERNET 	0X06
#define	SUBCMD_SENSOR	 	0X0001
#define	FIRST_END_SYMBOL	 		0X0D
#define	SECOND_END_SYMBOL	 		0X0A

enum
{
	NENCRYPTION_NCOMPRESSION = 0X00,
	ENCRYPTION_NCOMPRESSION,
	NENCRYPTION_COMPRESSION,
	ENCRYPTION_COMPRESSION,
};

VOID WriteFlashFlag(VOID)
{
	FLASH_Status FLASHStatus = FLASH_COMPLETE;
	FLASH_Unlock();///Flash解锁
	while(MCUFlashErase(FLASH_Sector_11) != 1);
	
	FLASH_ProgramWord(UPDATE_FLAG_ADDRESS, 0x55AA55AA);//写入成功标记
	FLASH_ProgramWord(UPDATE_FLAG_ADDRESS + 4, g_u32AppAddress);//写入应用地址标记
	FLASH_ProgramWord(UPDATE_FLAG_ADDRESS + 8, g_u32HardEdition);//写入硬件版本
	FLASH_ProgramWord(UPDATE_FLAG_ADDRESS + 12, g_u32SoftEdition);//写入软件版本
     
	FLASH_Lock();
	
}
STATIC VOID HandleDataPackage(U8 *pBuf, U16 u16Length)
{
	
#ifdef __RD15002_PROTOCOL_
	
	U8 szData[100];
	U32 *pData;
	U32 u32Length;
	U32 u32TotalPackageNumber = 0;//总的包数
	U32 u32CurrentPackageNumber = 0;//当前包数
	U32 u32CrcValue;
	U16 u16Loop;
	
	u32Length = u16Length + 19;
	
	pData = malloc(u32Length*4);
	
	if(pData != NULL)
	{
		for(u16Loop = 0; u16Loop < u32Length; u16Loop++)
		{
			pData[u16Loop] = pBuf[u16Loop];
		}
		u32CrcValue = HardGenCrc32(pData, u16Length);
		free(pData);
	}
	else
	{
		EnterException(ERR_MALLOC_FAIL);
	}
	
	szData[0] = START_SYMBOL;
	szData[1] = PROTOCOL_EDITION;
	szData[2] = HIBYTE(HIWORD(u32Length));
	szData[3] = LOBYTE(HIWORD(u32Length));
	szData[4] = HIBYTE(LOWORD(u32Length));
	szData[5] = LOBYTE(LOWORD(u32Length));
	szData[6] = DATA_DIRECTION;
	szData[7] = MAINCMD_INTERNET;
	szData[8] = HIBYTE(SUBCMD_SENSOR);
	szData[9] = LOBYTE(SUBCMD_SENSOR);
	szData[10] = NENCRYPTION_NCOMPRESSION;
	szData[11] = HIBYTE(HIWORD(u32TotalPackageNumber));
	szData[12] = LOBYTE(HIWORD(u32TotalPackageNumber));
	szData[13] = HIBYTE(LOWORD(u32TotalPackageNumber));
	szData[14] = LOBYTE(LOWORD(u32TotalPackageNumber));
	szData[15] = HIBYTE(HIWORD(u32CurrentPackageNumber));
	szData[16] = LOBYTE(HIWORD(u32CurrentPackageNumber));
	szData[17] = HIBYTE(LOWORD(u32CurrentPackageNumber));
	szData[18] = LOBYTE(LOWORD(u32CurrentPackageNumber));
	memcpy(szData + 19, pBuf, u16Length);
	
	szData[19 + u16Length] = HIBYTE(HIWORD(u32CrcValue));
	szData[20 + u16Length] = LOBYTE(HIWORD(u32CrcValue));
	szData[21 + u16Length] = HIBYTE(LOWORD(u32CrcValue));
	szData[22 + u16Length] = LOBYTE(LOWORD(u32CrcValue));
	
	szData[23 + u16Length] = FIRST_END_SYMBOL;
	
	szData[24 + u16Length] = SECOND_END_SYMBOL;
	
	UsartSend(USART2, szData, u32Length + 6);
	
	
#else

	UsartSend(USART2, pBuf, u16Length);
	
	UsartSend(USART1, pBuf, u16Length);
	
	DelayMs_Sft(50);
#endif

}


STATIC VOID HandleCmdProc(U8 *pBuf, U16 u16Length)
{
	unsigned int copy_i = 0;
	
	U8 szData[70];
	U8 szBuf[4] = {0};
	U8 u8Value;
	U16 u16Loop;
	U32 u32ReadOffset, u32ByteSum;

	U8 *szQueue = malloc(1031);
	if(szQueue == NULL)
	{
		EnterException(ERR_DTU3_MALLOC_FAIL);
	}
	if(u16Length == 7)
	{
		if((pBuf[0] == 0xfe) && (pBuf[1] == 0x00) && (pBuf[6] == 0xfe))//进入擦掉升级区域
		{
			FlashInit();
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "boot erase exflash over\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x01) && (pBuf[6] == 0xfe))//进入升级模式
		{
			FlashInit();
			FlashInit();
			printf("erase flash done.\r\n");
			
			
			
			g_bUpdate = TRUE;
			g_u32TimeOut = DTUTIMEOUT2;
			g_u32WriteOffset = 0;
			u16PackageNumber = 1;
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "boot enter update mode,please send 1 package\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x02) && (pBuf[6] == 0xfe))//退出升级模式
		{
			g_bUpdate = FALSE;
			g_u32TimeOut = DTUTIMEOUT1;
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "boot exit update mode\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x03) && (pBuf[6] == 0xfe))//写升级成功标志
		{
			WriteFlashFlag();
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "boot set flag ok\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x04) && (pBuf[6] == 0xfe))//应用地址
		{
			g_u32AppAddress = MAKELONG(MAKEWORD(pBuf[2], pBuf[3]), MAKEWORD(pBuf[4], pBuf[5]));
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "boot set app address ok\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x05) && (pBuf[6] == 0xfe))//硬件版本
		{
			g_u32HardEdition = MAKELONG(MAKEWORD(pBuf[2], pBuf[3]), MAKEWORD(pBuf[4], pBuf[5]));
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "boot set hard edition ok\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x06) && (pBuf[6] == 0xfe))//软件版本
		{
			g_u32SoftEdition = MAKELONG(MAKEWORD(pBuf[2], pBuf[3]), MAKEWORD(pBuf[4], pBuf[5]));
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "boot set soft edition ok\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}

		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x07) && (pBuf[6] == 0xfe))//重启
		{
			
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "boot restart\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
			DelayMs(1500);
			NVIC_SystemReset();
		}
		
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x08) && (pBuf[6] == 0xfe))//获取升级数据长度
		{
			u16Loop = 0;
			while((DeleteQueue(pDtuQueueInfo, &u8Value, pDtuQueue) == TRUE) && (u16Loop < STM_PAGE_SIZE))
			{
				*(szQueue + u16Loop) = u8Value;
				u16Loop++;	
			}
			if(u16Loop != 0)
			{
				if(g_u8FlashType == SST25VF0_FLASH)
				{
					u32ReadOffset = 0;
					while(u32ReadOffset < u16Loop)
					{
					}
				}
				else
				{
					FlashWriteSTM32(STM_APP_ADDRESS + g_u32WriteOffset, u16Loop, szQueue);
				}
				g_u32WriteOffset = u16Loop + g_u32WriteOffset;
			}
			
			u32ByteSum = 0;
			for(u32ReadOffset = 0; u32ReadOffset < g_u32WriteOffset; u32ReadOffset++)
			{

					FlashReadSTM32(STM_APP_ADDRESS + u32ReadOffset,1, &u8Value);

					u32ByteSum = u32ByteSum + u8Value;
			}
			
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "boot update = %d Bytes, Sum = 0x%x\r\n", g_u32WriteOffset, u32ByteSum);
			HandleDataPackage(szData, strlen((char *)szData));
		}
		
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x09) && (pBuf[6] == 0xfe))//清除标志
		{
			while(MCUFlashErase(FLASH_Sector_11) != 1);
			
			FlashReadSTM32(UPDATE_FLAG_ADDRESS, 4, szBuf);
			
			memset(szData, 0, sizeof(szData));
			
			
			if((szBuf[0] == 0xAA) && (szBuf[1] == 0x55) && (szBuf[2] == 0xAA) && (szBuf[3] == 0x55))
			{
				sprintf((char *)szData, "boot erase flag error\r\n");
			}
			else
			{
				
						
					/*sector 8、9、10的数据一并拷贝到sector5、6、7里面*/
					FLASH_Unlock();
					FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
													FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
					while(MCUFlashErase(FLASH_Sector_5) != 1);
					while(MCUFlashErase(FLASH_Sector_6) != 1);
					while(MCUFlashErase(FLASH_Sector_7) != 1);
					FLASH_Lock();
						
					FLASH_Unlock();
					FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
													FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
					while(copy_i <  393200)//393216
						{
							while(  FLASH_ProgramByte(FLASH_APP1_ADDR + copy_i, *(unsigned char *)(STM_APP_ADDRESS + copy_i)) != FLASH_COMPLETE );
							copy_i++;
						}
					FLASH_Lock();
						
						
						
					/*擦除sector 8、9、10的数据*/
		//			FLASH_Unlock();
		//			FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
		//											FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
		//			while(MCUFlashErase(FLASH_Sector_8) != 1);
		//			while(MCUFlashErase(FLASH_Sector_9) != 1);
		//			while(MCUFlashErase(FLASH_Sector_10) != 1);
		//			FLASH_Lock();
						
				
				
				sprintf((char *)szData, "boot erase flag ok\r\n");
			}
			
			HandleDataPackage(szData, strlen((char *)szData));
		}
		
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x0A) && (pBuf[6] == 0xfe))//数据拷贝成功后启动升级  外部flash拷贝至内部flash
		{
			u32ReadOffset = 0;
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "Update success\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else if((pBuf[0] == 0xfe) && (pBuf[1] == 0x0B) && (pBuf[6] == 0xfe))//获取当前模式
		{
			memset(szData, 0, sizeof(szData));
			sprintf((char *)szData, "Boot Mode\r\n");
			HandleDataPackage(szData, strlen((char *)szData));
		}
		else
		{
			if(g_bUpdate == TRUE) 
			{
				u16Loop = 0;
				if(GetQueueLength(pDtuQueueInfo) >= STM_PAGE_SIZE)
				{
					while (u16Loop < STM_PAGE_SIZE)
					{
						if(DeleteQueue(pDtuQueueInfo, &u8Value, pDtuQueue) == TRUE)
						{
							*(szQueue + u16Loop) = u8Value;
							u16Loop++;	
							
						}
					}
//////////////////////////////////////////////////////////////////////////////
						FlashWriteSTM32(STM_APP_ADDRESS + g_u32WriteOffset, STM_PAGE_SIZE, szQueue);

					g_u32WriteOffset = g_u32WriteOffset + STM_PAGE_SIZE;
					u16PackageNumber++;
					memset(szData, 0, sizeof(szData));
					sprintf((char *)szData, "boot receive = %d, write = %d, please send %d package\r\n",u16Length, g_u32WriteOffset, u16PackageNumber);
					HandleDataPackage(szData, strlen((char *)szData));
				}
				
				u16Loop = 0;
				while(u16Loop < u16Length)
				{
					if(AddQueue(pDtuQueueInfo, pBuf[u16Loop], pDtuQueue) == TRUE)
					{
						u16Loop++;
					}
				}
				
				u16Loop = 0;
				if(GetQueueLength(pDtuQueueInfo) >= STM_PAGE_SIZE)
				{
					while (u16Loop < STM_PAGE_SIZE)
					{
						if(DeleteQueue(pDtuQueueInfo, &u8Value, pDtuQueue) == TRUE)
						{
							*(szQueue + u16Loop) = u8Value;
							u16Loop++;	
							
						}
					}
//////////////////////////////////////////////////////////////////////////////
						FlashWriteSTM32(STM_APP_ADDRESS + g_u32WriteOffset, STM_PAGE_SIZE, szQueue);

					g_u32WriteOffset = g_u32WriteOffset + STM_PAGE_SIZE;
					u16PackageNumber++;
					memset(szData, 0, sizeof(szData));
					sprintf((char *)szData, "boot receive = %d, write = %d, please send %d package\r\n",u16Length, g_u32WriteOffset, u16PackageNumber);
					HandleDataPackage(szData, strlen((char *)szData));
				}
				else
				{
				
					memset(szData, 0, sizeof(szData));
					sprintf((char *)szData, "boot receive = %d, write = %d, please wait\r\n",u16Length, g_u32WriteOffset);
					HandleDataPackage(szData, strlen((char *)szData));
				}
				
			}
		}
	}
	else
	{
		if(g_bUpdate == TRUE) 
		{
			u16Loop = 0;
			if(GetQueueLength(pDtuQueueInfo) >= STM_PAGE_SIZE)
			{
				while (u16Loop < STM_PAGE_SIZE)
				{
					if(DeleteQueue(pDtuQueueInfo, &u8Value, pDtuQueue) == TRUE)
					{
						*(szQueue + u16Loop) = u8Value;
						u16Loop++;	
					}
				}
/////////////////////////////////////////////////////////////////////
				FlashWriteSTM32(STM_APP_ADDRESS + g_u32WriteOffset, STM_PAGE_SIZE, szQueue);
				
				g_u32WriteOffset = g_u32WriteOffset + STM_PAGE_SIZE;
				u16PackageNumber++;
				memset(szData, 0, sizeof(szData));
				sprintf((char *)szData, "boot receive = %d, write = %d, please send %d package\r\n",u16Length, g_u32WriteOffset, u16PackageNumber);
				HandleDataPackage(szData, strlen((char *)szData));
			}			
			u16Loop = 0;
			while(u16Loop < u16Length)
			{
				if(AddQueue(pDtuQueueInfo, pBuf[u16Loop], pDtuQueue) == TRUE)
				{
					u16Loop++;
				}
			}
			u16Loop = 0;
			if(GetQueueLength(pDtuQueueInfo) >= STM_PAGE_SIZE)
			{
				while (u16Loop < STM_PAGE_SIZE)
				{
					if(DeleteQueue(pDtuQueueInfo, &u8Value, pDtuQueue) == TRUE)
					{
						*(szQueue + u16Loop) = u8Value;
						u16Loop++;	
						
					}
				}
//////////////////////////////////////////////////////////////////////////////
					FlashWriteSTM32(STM_APP_ADDRESS + g_u32WriteOffset, STM_PAGE_SIZE, szQueue);
				
				g_u32WriteOffset = g_u32WriteOffset + STM_PAGE_SIZE;
				u16PackageNumber++;
				memset(szData, 0, sizeof(szData));
				sprintf((char *)szData, "boot receive = %d, write = %d, please send %d package\r\n",u16Length, g_u32WriteOffset, u16PackageNumber);
				HandleDataPackage(szData, strlen((char *)szData));
			}
			else
			{
				memset(szData, 0, sizeof(szData));
				sprintf((char *)szData, "boot receive = %d, write = %d,please wait\r\n",u16Length, g_u32WriteOffset);
				HandleDataPackage(szData, strlen((char *)szData));
			}
			
		}
	}
	
	free(szQueue);		
}


VOID DtuBoot(VOID)
{
	U8 *szData;
	U16 u16Length;
	U32 u32Tick;
    S32 s32Count;
	USART_InitTypeDef Usart_InitStruct;
	szData = malloc(DTUUARTSIZE);
	if(szData == NULL)
	{
		EnterException(ERR_DTU1_MALLOC_FAIL);
	}
	
	pDtuQueueInfo = malloc(sizeof(CQueueInfo));
	pDtuQueue = malloc(MAXSIZE_A);
	
	if((pDtuQueueInfo == NULL) ||(pDtuQueue == NULL))
	{
		EnterException(ERR_DTU2_MALLOC_FAIL);
	}
	pDtuQueueInfo->SizeType = QUEUETYPE_A;
	
	
	
	UartInit(USART1);
	UartOpen(USART1);

		
	g_u8FlashType = STM_FLASH;
		
	DtuInit();
	
	u32Tick = GetTickCount();
	
	g_u32TimeOut = DTUTIMEOUT1;
	
	while(1)
	{
        
		if(GetQueueLength(pUart2QueueInfo))
		{
			s32Count = GetTickCount() - GetUartReceiveTime(USART2);
			if(s32Count > g_u32TimeOut)
			{
				ReadUsartData(USART2, szData, &u16Length);//读出数据
				HandleCmdProc(szData, u16Length);//
			}
		}
		if(GetQueueLength(pUart1QueueInfo))
		{
			s32Count = GetTickCount() - GetUartReceiveTime(USART1);
			if(s32Count > g_u32TimeOut)
			{
				ReadUsartData(USART1, szData, &u16Length);
				if(ParseCmd(szData, u16Length) != SB_NULL)
				{
					break;
				}
			}
		}
		if(DetectOnline() == FALSE)
		{
			s32Count = GetTickCount() - u32Tick;
			if(s32Count > 1000)
			{
				memset(szData, 0, DTUUARTSIZE);
				sprintf((char *)szData, "boot off line");
				UsartSend(USART1, (U8 *)szData, strlen((char *)szData));
				u32Tick = GetTickCount();
			}
		}
	}
	
	free(pDtuQueueInfo);
	free(pDtuQueue);
	
	free(szData);
	
	UartDeinit(USART2);

}


