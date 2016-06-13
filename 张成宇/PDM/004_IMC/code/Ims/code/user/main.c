#include "Test.h"
#include "Serial.h" 
#include "Pwc.h" 
#include "Adc.h"
#include "timer.h"
#include "flash.h"
STATIC VOID BoardInit(VOID)
{
	USART_InitTypeDef Usart_InitStruct;
	
	UartInit(&Usart_InitStruct, 115200);
	
	UartCreate(USART2, &Usart_InitStruct, FALSE, TRUE);
	
	UartOpen(USART2);
	
	PWCInit();
	
	AdcInit();
	
	TIM_Create();
	
	TIM_Open();
	
	SetTimer(0);

}

STATIC VOID TestProc(VOID)
{

//	TestUart1();
//	TestAdc();
}



#define UART_TIMEOUT  20

#define ARRAY_SIZEOF(s)		(sizeof(s)-1)
	
CONST U8 szInfo1[] = "#IMS SUCCESS\r\n";

CONST U8 szInfo2[] = "#IMS ERROR\r\n";

CONST U8 szCmd1[] = "DT IMS INFO\r\n";

CONST U8 szCmd2[] = "DT IMS RESET\r\n";

CONST U8 szCmd3[] = "DT IMS OK\r\n";

CONST U8 szCmd4[] = "DT IMS LOGGIN W";

CONST U8 szCmd5[] = "DT IMS LOGGIN R\r\n";

CONST U8 szCmd6[] = "DT IMS LOGGIN S";

U16 g_u16IpcWatchCount = 0;
STATIC U16 g_u16IpcToatlCount = 1200;

STATIC VOID ResetIpcWatch(VOID)
{
	g_u16IpcWatchCount = 0;
	
	SetTimer(0);
	
}


STATIC VOID IpcWatchThread(VOID)
{
	U16 u16Value;
	u16Value = GetTimer();
	if(u16Value > 1000)
	{
		g_u16IpcWatchCount++;
		
		SetTimer(u16Value - 1000);
		
//		printf("%d\r\n", g_u16IpcWatchCount);
	}
	
	if(g_u16IpcWatchCount > g_u16IpcToatlCount)
	{
		
		ResetIpc();
	}
}


STATIC VOID HandleDataPackage(U8 *pBuf, U16 u16Length)
{
	UsartSend(USART2, pBuf, u16Length);
}


STATIC VOID HandleImsinfo(VOID)
{
	
	U16 u16Value;
	
	U8 szData[200] = {0};
		
	U32 szId[3];
	
	float Val;
	
	ReadLockId(szId);
	
	
    u16Value = GetAdc(ADC_CHANNEL);
    Val=(float)u16Value*(3.105/4096);//实际参考电压
    Val = 4*Val;
	
	sprintf((char *)szData, "#IMS=0x%08x%08x%08x V:%.2f\r\n", szId[2], szId[1], szId[0], Val);
	
	HandleDataPackage(szData, strlen((char *)szData));
	
}

STATIC VOID HandleImsReset(VOID)
{
	U8 szData[200] = {0};
	sprintf((char *)szData, "%s", szInfo1);
	HandleDataPackage(szData, strlen((char *)szData));
	ResetIpc();
}



STATIC VOID HandleImsIdle(VOID)
{
	U8 szData[200] = {0};
	sprintf((char *)szData, "%s", szInfo1);
	HandleDataPackage(szData, strlen((char *)szData));
	ResetIpcWatch();
}

STATIC VOID HandleImsError(VOID)
{
	U8 szData[200] = {0};
	sprintf((char *)szData, "%s", szInfo2);
	HandleDataPackage(szData, strlen((char *)szData));
	ResetIpcWatch();
}

STATIC VOID HandleImsLogginWrite(U8 *pBuf, U16 u16Length)
{
	U8 szData[200] = {0};
	U8 *pLength;
	
	
	FlashInit(LOGGIN_INFOR_ADDRESS);
	FlashInit(LOGGIN_LENGTH_INFOR_ADDRESS);
	
	FLASH_error   FLASH_value;	
	FLASH_value = FlashWriteSTM32(LOGGIN_INFOR_ADDRESS, u16Length, pBuf);
	pLength = (U8 *)&u16Length;
	FLASH_value = FlashWriteSTM32(LOGGIN_LENGTH_INFOR_ADDRESS, 2, pLength);
	
	if(FLASH_value != RES_OK)
	{
		sprintf((char *)szData, "#IMS WRITE ERROR\r\n");
		HandleDataPackage(szData, strlen((char *)szData));
	}
	else
	{
		sprintf((char *)szData, "%s", szInfo1);
		HandleDataPackage(szData, strlen((char *)szData));
	}
}

STATIC VOID HandleImsSet(U8 *pBuf, U16 u16Length)
{
	U8 szData[50] = {0};
	if((u16Length < 3) && (u16Length > 0))
	{
		if(u16Length == 1)
		{
			g_u16IpcToatlCount = (pBuf[0] - 0x30) * 60;
		}
		else
		{
			g_u16IpcToatlCount = (pBuf[0] - 0x30) * 600 + (pBuf[1] - 0x30) * 60;
		}
		
		sprintf((char *)szData, "%s", szInfo1);
		HandleDataPackage(szData, strlen((char *)szData));
			
	}
	else
	{
		sprintf((char *)szData, "%s", szInfo2);
		HandleDataPackage(szData, strlen((char *)szData));
	}
	
}
STATIC VOID HandleImsLogginRead()
{
	U8 szData[200] = {0};
	U8 szLength[2] = {0};
	U16 u16Value;
	
	FlashReadSTM32(LOGGIN_LENGTH_INFOR_ADDRESS, 2, szLength);
	u16Value = MAKEWORD(szLength[0], szLength[1]);
	if(u16Value >= 0xffff)
	{
		sprintf((char *)szData, "%s", szInfo2);
		HandleDataPackage(szData, strlen((char *)szData));
	}
	else
	{
		FlashReadSTM32(LOGGIN_INFOR_ADDRESS, u16Value, szData);
		
		HandleDataPackage(szData, strlen((char *)szData));
	}
}

STATIC VOID HandleCmdProc(U8 *pBuf, U16 u16Length)
{
	if((pBuf[0] == 0xFE) && (pBuf[2] == 0x4D))
	{
		if(pBuf[3] == 0x00)
		{
			NVIC_SystemReset();
		}
	}
	if((memcmp(pBuf, szCmd1, ARRAY_SIZEOF(szCmd1)) == 0) && (u16Length == ARRAY_SIZEOF(szCmd1)))
	{
		HandleImsinfo();
	}
	else if((memcmp(pBuf, szCmd2, ARRAY_SIZEOF(szCmd2)) == 0) && (u16Length == ARRAY_SIZEOF(szCmd2)))
	{
		HandleImsReset();
	}
	else if((memcmp(pBuf, szCmd3, ARRAY_SIZEOF(szCmd3)) == 0) && (u16Length == ARRAY_SIZEOF(szCmd3)))
	{
		HandleImsIdle();
	}
	else if(memcmp(pBuf, szCmd4, ARRAY_SIZEOF(szCmd4)) == 0)
	{
		HandleImsLogginWrite(pBuf + ARRAY_SIZEOF(szCmd4) + 1, u16Length - ARRAY_SIZEOF(szCmd4) - 1);
	}
	else if((memcmp(pBuf, szCmd5, ARRAY_SIZEOF(szCmd5)) == 0) && (u16Length == ARRAY_SIZEOF(szCmd5)))
	{
		HandleImsLogginRead();
	}
	else if(memcmp(pBuf, szCmd6, ARRAY_SIZEOF(szCmd6)) == 0)
	{
		HandleImsSet(pBuf + ARRAY_SIZEOF(szCmd6) + 1, u16Length - ARRAY_SIZEOF(szCmd6) - 1);
	}
	else
	{
		HandleImsError();
	}
	
}



STATIC VOID AppProc(VOID)
{
	
	U8 *szData;
	U16 u16Length;
    S32 s32Count;
	
	szData = malloc(100);
	if(szData == NULL)
	{
		EnterException(ERR_MALLOC_FAIL);
	}
	
	while(1)
	{
        
		if(GetQueueLength(pUart2QueueInfo))
		{
			s32Count = GetTickCount() - GetUartReceiveTime(USART2);
			if(s32Count > UART_TIMEOUT)
			{
				ReadUsartData(USART2, szData, &u16Length);
				HandleCmdProc(szData, u16Length);
			}
		}
		
		IpcWatchThread();
	}
		
}

int main(void)
{	

	OsInit();
	BoardInit();
	TestProc();
	AppProc();
	return 0;
}

