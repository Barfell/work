#include "usart.h"
#include "comm.h"


VOID TestImu(VOID)
{
	U8 szTestImu[43] = 
	{1,2,3,4,5,6,7,8,9,0x10,
	0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x20,
	0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x30,
	0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x40,
	0x41,0x42,0x43	
	};
    U32 u32Cnt = 0;
	U8 szBuf[30];
    U8 *pBuf = mymalloc(SRAMIN, 43);
    U8 *g_pTestdataCount =  (U8 *)&u32Cnt; 

    U16 u16Cnt;
	
	sprintf((char *)szBuf, "IMU data is preparing");
	DisplayString(0, LINE_6, szBuf);
	memset(szBuf, 0,30);
	DelayMs(6000);
	sprintf((char *)szBuf, "IMU data is sending");
	DisplayString(0, LINE_6, szBuf);

    if(pBuf == NULL)
    {
        EnterException(ERR_USATT1_MALLOC_FAIL);
    }
	
	memcpy(pBuf, szTestImu, 43);
    
    *(pBuf + 0) = 0x55;
    *(pBuf + 1) = 0xAA;

    u32Cnt = 0;
    while(1)
    {

        *(pBuf + 2) = *g_pTestdataCount ;
        *(pBuf + 3) = *(g_pTestdataCount + 1) ;
        *(pBuf + 4) = *(g_pTestdataCount + 2) ;
        *(pBuf + 5) = *(g_pTestdataCount + 3) ;
		
		u16Cnt = 43;
		USART1_Send(pBuf, &u16Cnt);
		u32Cnt++;

		DelayMs(1);
        
    }
}
    
VOID TestGps(VOID)
{
    U32 u32Cnt = 0;
    U32 u32Tick, u32CurrentTick;
    U8 *pBuf = mymalloc(SRAMIN, 200);
    U8 *g_pTestdataCount =  (U8 *)&u32Cnt; 
    U8 u8Cnt;
    U16 u16Cnt;
	U8 szBuf[20];
    
	sprintf((char *)szBuf, "GPS data is preparing");
	DisplayString(0, LINE_6, szBuf);
	memset(szBuf, 0,30);
	DelayMs(6000);
	sprintf((char *)szBuf, "GPS data is sending");
	DisplayString(0, LINE_6, szBuf);
	u16Cnt = 1; 
	USART1_Send("A", &u16Cnt);
    if(pBuf == NULL)
    {
        EnterException(ERR_USATT1_MALLOC_FAIL);
    }
    for(u8Cnt = 0; u8Cnt < 200; u8Cnt++)
    {
        *(pBuf + u8Cnt) = u8Cnt;
    }
    
    *(pBuf + 0) = 0x55;
    *(pBuf + 1) = 0xAA;
    u32Tick = GetTickCount();
    u32Cnt = 0;
    while(1)
    {

        *(pBuf + 2) = *g_pTestdataCount ;
        *(pBuf + 3) = *(g_pTestdataCount + 1) ;
        *(pBuf + 4) = *(g_pTestdataCount + 2) ;
        *(pBuf + 5) = *(g_pTestdataCount + 3) ;

        u32CurrentTick = GetTickCount();

        if((u32CurrentTick - u32Tick) > 1000)
        {

            u16Cnt = 200;
            USART1_Send(pBuf, &u16Cnt);
            u32Cnt++;
           
        }
        
    }
    
}
VOID TestUsart1(VOID)
{
	U16 u16Count;
	u16Count = 13;
	USART1_Send("\r\n´®¿Ú1²âÊÔ\r\n", &u16Count);
    while(1)
    {
        if(GetUsartCurrentLength(USART1_TYPE) != 0)
        {
            Usart1_DMA_Send(g_pUsart1_rx_buf, GetUsartCurrentLength(USART1_TYPE));
            ClearUsartCurrentLength(USART1_TYPE);
        }
        
    }
}

VOID TestUsart2(VOID)
{
    uart2_init(115200, 256, 256);
    
    U16 u16Count;
	u16Count = 13;
	USART2_Send("\r\n´®¿Ú2²âÊÔ\r\n", &u16Count);
	
    while(1)
    {
        if(GetUsartCurrentLength(USART2_TYPE) != 0)
        {
            Usart2_DMA_Send(g_pUsart2_rx_buf, GetUsartCurrentLength(USART2_TYPE));
            ClearUsartCurrentLength(USART2_TYPE);
        }
        
    }
}


VOID TestUsart3(VOID)
{
    uart3_init(115200, 256, 256);
    
    U16 u16Count;
	u16Count = 13;
	USART3_Send("\r\n´®¿Ú3²âÊÔ\r\n", &u16Count);
	
    while(1)
    {
        if(GetUsartCurrentLength(USART3_TYPE) != 0)
        {
            Usart3_DMA_Send(g_pUsart3_rx_buf, GetUsartCurrentLength(USART3_TYPE));
            ClearUsartCurrentLength(USART3_TYPE);
        }
        
    }
}

VOID TestUsart4(VOID)
{
    uart4_init(115200, 256, 256);
    
    U16 u16Count;
	u16Count = 13;
	UART4_Send("\r\n´®¿Ú4²âÊÔ\r\n", &u16Count);
	
    while(1)
    {
        if(GetUsartCurrentLength(USART4_TYPE) != 0)
        {
            Uart4_DMA_Send(g_pUsart4_rx_buf, GetUsartCurrentLength(USART4_TYPE));
            ClearUsartCurrentLength(USART4_TYPE);
        }
        
    }
}

VOID TestUsartSend(VOID)
{
	U16 u16Count;
    uart1_init(115200, 256, 256);
    uart2_init(115200, 256, 256);
    uart3_init(115200, 256, 256);
	uart4_init(115200, 256, 256);
    
    while(1)
    {
		u16Count = 15;
        USART1_Send("test usart1...", &u16Count);
		u16Count = 15;
        USART2_Send("test usart2...", &u16Count);
		u16Count = 15;
        USART3_Send("test usart3...", &u16Count);
		u16Count = 15;
		UART4_Send("test usart4...", &u16Count);
        DelayMs(100);
        
    }
}

VOID TestUsart(VOID)
{
    uart1_init(115200, 256, 256);
    uart2_init(115200, 256, 256);
    uart3_init(115200, 256, 256);
	uart4_init(115200, 256, 256);
    
    while(1)
    {
		if(GetUsartCurrentLength(USART1_TYPE) != 0)
        {
			
			Usart1_DMA_Send(g_pUsart1_rx_buf, GetUsartCurrentLength(USART1_TYPE));
			
            ClearUsartCurrentLength(USART1_TYPE);
        }
		if(GetUsartCurrentLength(USART2_TYPE) != 0)
        {
            Usart2_DMA_Send(g_pUsart2_rx_buf, GetUsartCurrentLength(USART2_TYPE));
            ClearUsartCurrentLength(USART2_TYPE);
        }
		if(GetUsartCurrentLength(USART3_TYPE) != 0)
        {
            Usart3_DMA_Send(g_pUsart3_rx_buf, GetUsartCurrentLength(USART3_TYPE));
            ClearUsartCurrentLength(USART3_TYPE);
        }
		if(GetUsartCurrentLength(USART4_TYPE) != 0)
		{
//			Uart4_DMA_Send(g_pUsart4_rx_buf, GetUsartCurrentLength(USART4_TYPE));
//			UART4_Send(g_pUsart4_rx_buf);
			Usart1_DMA_Send(g_pUsart4_rx_buf, GetUsartCurrentLength(USART4_TYPE));
			ClearUsartCurrentLength(USART4_TYPE);
		}
        
    }
}


