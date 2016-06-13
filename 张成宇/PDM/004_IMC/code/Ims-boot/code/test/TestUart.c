#include "Serial.h" 



VOID TestUart1(VOID)
{
	U8 szData[MAXSIZE_A];
	U16 u16Length;
	S32 s32Count;
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
		DelayMs(100);
	}

}
