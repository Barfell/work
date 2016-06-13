#include "board.h"
enum
{
    FRAM_BYTE_MODE = 1,
    FRAM_STRING_MODE
};
STATIC U8 g_u8test = 0;
STATIC U16 g_u16test = 0;
STATIC U8 g_u8CmdType = 0;
STATIC U32 g_u32Tick1,g_u32Tick2,g_u32Tick3 = 0;

#define MAXFRAMADDRESS  131072          //×î´ó128k

VOID TestFramProc(VOID)
{
    U32 u32Count = 0;
    U8 u8Value = 0xaa;
    U32 u32FramSize;
    U16 u16FramSizeSubA, u16FramSizeSubB;
    U8 *pTest1 = (U8 *)mymalloc(SRAMIN, 2048);
    U8 *pTest2 = (U8 *)mymalloc(SRAMIN, 2048);
    U16 u16Count;
    U8 szTestTest[5]={0};
TestFramStart:
	printf("FRAM TEST\r\n");

    printf("Please input Mode:01-Byte;02-String\r\n");
     
    while(1)
	{
        if(GetUsartCurrentLength(USART1_TYPE))
        {
            u16Count = GetUsartCurrentLength(USART1_TYPE);
            ClearUsartCurrentLength(USART1_TYPE);
            memcpy(szTestTest, g_pUsart1_rx_buf, u16Count);
            if(u16Count == 4)
            {
                
                u16FramSizeSubA = MAKEWORD(szTestTest[1], szTestTest[0]);
                u16FramSizeSubB = MAKEWORD(szTestTest[3], szTestTest[2]);
                u32FramSize = MAKELONG(u16FramSizeSubB, u16FramSizeSubA);

                if(u32FramSize <= 0x20000)
                {
                    printf("input OK\r\n");
                    goto TestFramExit;
                }
                else
                    printf("input ERROR\r\n");
            }
            else if(u16Count == 1)
            {
                if(szTestTest[0] == 1)
                {
                    g_u8CmdType = FRAM_BYTE_MODE;
                    printf("FRAM_BYTE_MODE\r\n");
                    printf("Please input Size:Do not over 0x20000(128k)\r\n");
                }
                else if(szTestTest[0] == 2)
                {
                    g_u8CmdType = FRAM_STRING_MODE;
                    
                    memset(pTest1, 0x55, 2048);
                    printf("FRAM_STRING_MODE\r\n");
                    printf("Please input Size:Do not over 0x20000(128k)\r\n");
                }
                else
                {
                    printf("input ERROR\r\n");
                }
                    
            }
                
            else
                printf("input ERROR\r\n");
        }
                      
	}
    
TestFramExit:
    
	FM25V10_Init();
    
    g_u8test = FM25V10_ReadSR();
    
    printf("SR = %x\r\n", g_u8test);
    
    g_u16test = FM25V10_ReadID();
    
    printf("ID = %x\r\n", g_u16test);
    
    g_u32Tick1 = GetTickCount();
    
    printf("Write size = %d\r\n", u32FramSize);
    
    printf("CurrentTick Write Start = %d\r\n", g_u32Tick1);
    
    if(g_u8CmdType == FRAM_BYTE_MODE)
    {
        for(u32Count = 0;u32Count < u32FramSize; u32Count++)
        {
            FramWriteByte(u32Count,u8Value);
        }
    }
    else
    {
        FramWriteInduce(0, u32FramSize, pTest1);
    }
    
    g_u32Tick2 = GetTickCount();
    
    printf("CurrentTick Write End = %d\r\n", g_u32Tick2);
    
    printf("CurrentTick Read Start = %d\r\n", g_u32Tick2);

    if(g_u8CmdType == FRAM_BYTE_MODE)
    {
        for(u32Count = 0;u32Count < u32FramSize; u32Count++)
        {
            g_u8test = FramReadByte(u32Count);
            if(g_u8test != u8Value)
            {
                printf("Handle error\r\n");
                while(1);
            }
        }
    }
    else
    {
        FramReadInduce(0, u32FramSize, pTest2);
        if(memcmp(pTest1, pTest2, u32FramSize) != 0)
        {
            printf("Handle error\r\n");
            while(1);
        }

    }
    g_u32Tick3 = GetTickCount();
    
    printf("CurrentTick Read End = %d\r\n", g_u32Tick3);
    
    goto TestFramStart;
    
    

}
