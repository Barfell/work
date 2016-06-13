#include "board.h"

VOID TestUsart1(VOID)
{
    printf("\r\n´®¿Ú1²âÊÔ\r\n");
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
    
    printf("\r\n´®¿Ú2²âÊÔ\r\n");
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
    
    printf("\r\n´®¿Ú2²âÊÔ\r\n");
    while(1)
    {
        if(GetUsartCurrentLength(USART3_TYPE) != 0)
        {
            Usart3_DMA_Send(g_pUsart3_rx_buf, GetUsartCurrentLength(USART3_TYPE));
            ClearUsartCurrentLength(USART3_TYPE);
        }
        
    }
}

VOID Test3Usart(VOID)
{

    printf("\r\n3´®¿Ú²âÊÔ\r\n");
    uart1_init(115200, 256, 256);
    uart2_init(115200, 256, 256);
    uart3_init(115200, 256, 256);
    
    while(1)
    {
        Usart1_DMA_Send("test usart1...", 15);
        Usart2_DMA_Send("test usart2...", 15);
        Usart3_DMA_Send("test usart3...", 15);
        DelayMs(100);
        
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
    
    DelayMs(8000);
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

        if((u32CurrentTick - u32Tick)%1000 < 20)
        {
            u16Cnt = 200;
            USART1_Send(pBuf, &u16Cnt);
            u32Cnt++;
           
        }
        
        
    }
    
}
