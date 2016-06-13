#include "usart.h"


VOID TestUsart1(VOID)
{
	U16 u16Count;
	u16Count = 13;
	USART1_Send("\r\n´®¿Ú1²âÊÔ\r\n", u16Count);
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
	USART2_Send("\r\n´®¿Ú2²âÊÔ\r\n", u16Count);
	
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
	USART3_Send("\r\n´®¿Ú3²âÊÔ\r\n", u16Count);
	
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
	UART4_Send("\r\n´®¿Ú4²âÊÔ\r\n", u16Count);
	
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
        USART1_Send("test usart1...", u16Count);
        USART2_Send("test usart2...", u16Count);
        USART3_Send("test usart3...", u16Count);
		UART4_Send("test usart4...", u16Count);
        DelayMs(500);
        
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
			Usart1_DMA_Send(g_pUsart4_rx_buf, GetUsartCurrentLength(USART4_TYPE));
			ClearUsartCurrentLength(USART4_TYPE);
		}
        
    }
}


