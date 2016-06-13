#include "Serial.h" 
#include "flash.h" 
VOID TestCrc(VOID)
{
	U32 u32Value;
	S32 s32Count;
	U8 szData[50];
	U16 u16Length, u16Loop;
	U32 u32szData[50];
	USART_InitTypeDef Usart_InitStruct;
	
	UartInit(&Usart_InitStruct, 115200);

	UartCreate(USART1, &Usart_InitStruct, FALSE, TRUE);
	
	UartOpen(USART1);
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	
	while(1)
	{
		if(GetQueueLength(pUart1QueueInfo))
		{
			s32Count = GetTickCount() - GetUartReceiveTime(USART1);
			if(s32Count > 10)
			{
				ReadUsartData(USART1, szData, &u16Length);

				for(u16Loop = 0; u16Loop < u16Length; u16Loop++)
				{
					u32szData[u16Loop] = szData[u16Loop];
				}
				u32Value = HardGenCrc32(u32szData, (U32)u16Length);
				
				printf("hard crc = 0x%x\r\n", u32Value);
				
				u32Value = SoftGenCrc32(u32szData, (U32)u16Length);
				
				printf("soft crc = 0x%x\r\n", u32Value);
//				u32Value = HardGenCrc32((U32 *)szData, (U32)u16Length);
//				
//				printf("hard crc = 0x%x\r\n", u32Value);
//				
//				u32Value = SoftGenCrc32((U32 *)szData, (U32)u16Length);
//				
//				printf("soft crc = 0x%x\r\n", u32Value);
			}
		}
	}
}


VOID TestUart1Ex(VOID)
{
	S32 s32Count;
	U8 szData[50];
	U16 u16Length;
	USART_InitTypeDef Usart_InitStruct;
	
	UartInit(&Usart_InitStruct, 57600);
	UartCreate(USART2, &Usart_InitStruct, FALSE, TRUE);
	UartOpen(USART2);
	
	
	while(1)
	{
		if(GetQueueLength(pUart1QueueInfo))
		{
			s32Count = GetTickCount() - GetUartReceiveTime(USART1);
			if(s32Count > 10)
			{
				ReadUsartData(USART1, szData, &u16Length);
				UsartSend(USART2, szData, u16Length);
			}
		}
		if(GetQueueLength(pUart2QueueInfo))
		{
			s32Count = GetTickCount() - GetUartReceiveTime(USART2);
			if(s32Count > 10)
			{
				ReadUsartData(USART2, szData, &u16Length);
				UsartSend(USART1, szData, u16Length);
			}
		}
	}

}
      

VOID TestUartFlash(VOID)
{

	U8 szData[50] = {0};
	U8 szDataEx[50] = {0};
	FLASH_Status FLASHStatus = FLASH_COMPLETE;

	memset(szData, 0, sizeof(szData));
	sprintf((char *)szData, "Internet update");
	
	FLASH_Unlock();///Flash解锁
	while(FLASHStatus ==FLASH_ErasePage(BOOTINFOR_ADDRESS))
	{
		DelayMs(2);
		FLASH_ProgramWord(UPDATE_FLAG_ADDRESS, 0x55AA55AA);//写入成功标记
		FLASH_ProgramWord(UPDATE_FLAG_ADDRESS + 4, STM32_FLASH_APP_ADDR);//写入应用地址标记
		FLASH_ProgramWord(UPDATE_FLAG_ADDRESS + 8, HARDWARE_EDITION);//写入硬件版本
		FLASH_ProgramWord(UPDATE_FLAG_ADDRESS + 12, SOFTWARE_EDITION);//写入软件版本
		break;///跳出循环,写入成功
	}        
	FLASH_Lock();
	
	
	FlashReadSTM32(UPDATE_FLAG_ADDRESS,4, szDataEx);
	printf("%s", szDataEx);
	printf("%s", szDataEx+1);
	printf("%s", szDataEx+2);
	printf("%s", szDataEx+3);
	
	FlashReadSTM32(UPDATE_FLAG_ADDRESS+4,4, szDataEx);
	printf("%s", szDataEx);
	printf("%s", szDataEx+1);
	printf("%s", szDataEx+2);
	printf("%s", szDataEx+3);
	
	FlashReadSTM32(UPDATE_FLAG_ADDRESS+8,4, szDataEx);
	printf("%s", szDataEx);
	printf("%s", szDataEx+1);
	printf("%s", szDataEx+2);
	printf("%s", szDataEx+3);
	
	FlashReadSTM32(UPDATE_FLAG_ADDRESS+12,4, szDataEx);
	printf("%s", szDataEx);
	printf("%s", szDataEx+1);
	printf("%s", szDataEx+2);
	printf("%s", szDataEx+3);
	
	while(1);
}

VOID TestUart1(VOID)
{
	S32 s32Count;
	U8 szData[50];
	U16 u16Length;
	USART_InitTypeDef Usart_InitStruct;
	
	UartInit(&Usart_InitStruct, 115200);

	UartCreate(USART1, &Usart_InitStruct, FALSE, TRUE);
	
	UartOpen(USART1);
	
	while(1)
	{
		if(GetQueueLength(pUart1QueueInfo))
		{
			s32Count = GetTickCount() - GetUartReceiveTime(USART1);
			if(s32Count > 10)
			{
				ReadUsartData(USART1, szData, &u16Length);
				UsartSend(USART1, szData, u16Length);
			}
		}
	}

}

VOID TestUart1Timer(VOID)
{
	USART_InitTypeDef Usart_InitStruct;
	
	UartInit(&Usart_InitStruct, 115200);

	UartCreate(USART1, &Usart_InitStruct, FALSE, TRUE);
	
	UartOpen(USART1);
	
	while(1)
	{
		printf("testuart...");
//		UsartSend(USART1, "test1", 5);
		DelayMs(100);
	}

}
VOID TestUart2(VOID)
{
	S32 s32Count;
	U8 szData[50];
	U16 u16Length;
	USART_InitTypeDef Usart_InitStruct;
	
	UartInit(&Usart_InitStruct, 115200);

	UartCreate(USART2, &Usart_InitStruct, FALSE, TRUE);
	
	UartOpen(USART2);
	
	while(1)
	{
		if(GetQueueLength(pUart2QueueInfo))
		{
			s32Count = GetTickCount() - GetUartReceiveTime(USART2);
			if(s32Count > 10)
			{
				ReadUsartData(USART2, szData, &u16Length);
				UsartSend(USART2, szData, u16Length);
			}
		}
	}

}
VOID TestUart2Timer(VOID)
{
	USART_InitTypeDef Usart_InitStruct;
	
	UartInit(&Usart_InitStruct, 115200);

	UartCreate(USART2, &Usart_InitStruct, FALSE, TRUE);
	
	UartOpen(USART2);
	
	while(1)
	{
		UsartSend(USART2, (unsigned char *)"test1", 5);
		DelayMs(100);
	}

}
VOID TestUart3(VOID)
{
	S32 s32Count;
	U8 szData[50];
	U16 u16Length;
	USART_InitTypeDef Usart_InitStruct;
	
	UartInit(&Usart_InitStruct, 115200);

	UartCreate(USART3, &Usart_InitStruct, FALSE, TRUE);
	
	UartOpen(USART3);
	
	while(1)
	{
		if(GetQueueLength(pUart3QueueInfo))
		{
			s32Count = GetTickCount() - GetUartReceiveTime(USART3);
			if(s32Count > 10)
			{
				ReadUsartData(USART3, szData, &u16Length);
				UsartSend(USART3, szData, u16Length);
			}
		}
	}

}
VOID TestUart3Timer(VOID)
{
	USART_InitTypeDef Usart_InitStruct;
	
	UartInit(&Usart_InitStruct, 115200);

	UartCreate(USART3, &Usart_InitStruct, FALSE, TRUE);
	
	UartOpen(USART3);
	
	while(1)
	{
		UsartSend(USART3, (unsigned char *)"test1", 5);
		DelayMs(100);
	}

}
