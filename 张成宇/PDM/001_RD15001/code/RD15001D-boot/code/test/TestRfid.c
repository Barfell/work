#include "board.h"
#define TIMELENGTH  11
#define TAGLENGTH  4
extern const U8 g_szGetCurrentProgram[];
extern const U8 g_szBootFirmware[];
extern const U8 g_szSetFrequencyChannel[];
extern const U8 g_szSetProtocol[];
extern const U8 g_szSetAntenna[];
extern const U8 g_szClearBuffer[];
extern const U8 g_szSearchTag[];
extern const U8 g_szGetTagdata[];

extern const U8 g_szGetTagIddata[];
extern const U8 g_szPrimeContinueReading[];
extern const U8 g_szContinueReading[];
extern const U8 g_szEnhanceDistance[];
extern const U8 g_szEnhanceSpeed1[];
extern const U8 g_szEnhanceSpeed2[];
extern const U8 g_szEnhanceSpeed3[];
extern const U8 g_szEnhanceSpeed4[];
extern const U8 g_szEnhanceSpeed5[];
extern const U8 g_szEnhanceSpeed6[];
extern const U8 g_szContinueReadingEx[];
extern const U8 g_szStopReading[];

STATIC BOOL AnalyzeCmd(P_U8 pBuf, U16 u16Count)
{
    BOOL bRet = FALSE;
    U8 szResponse[3] = {0x00, 0x90, 0x00};
    if(u16Count == 3)
    {
        if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x01) && (*(pBuf + 2) == 0xAA))//关机指令
        {
            bRet = TRUE;
            RFID_SHUTDOWN();
            szResponse[0] = 1;
            Usart1_DMA_Send(szResponse, 3);
            
        }       
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x02) && (*(pBuf + 2) == 0xAA))//开机指令
        {
            bRet = TRUE;
            RFID_UNSHUTDOWN();
            szResponse[0] = 2;
            Usart1_DMA_Send(szResponse, 3);
            
        }
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x03) && (*(pBuf + 2) == 0xAA))//读取系统状态
        {
            bRet = TRUE;
            szResponse[0] = 3;
            Usart1_DMA_Send(szResponse, 3);
        }
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x04) && (*(pBuf + 2) == 0xAA))//测试指令
        {
            bRet = TRUE;
            szResponse[0] = 4;
            Usart1_DMA_Send(szResponse, 3);
        }
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x05) && (*(pBuf + 2) == 0xAA))//自动指令
        {
            bRet = TRUE;
            szResponse[0] = 5;
            Usart1_DMA_Send(szResponse, 3);
                       
            while(SendAndWaitRfidDataProc(PRIMECONTINUEREADING) == FALSE);
            
            while(SendAndWaitRfidDataProc(CONTINUEREADING) == FALSE);
            
        }
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x06) && (*(pBuf + 2) == 0xAA))//自动唯一ID指令
        {
            bRet = TRUE;
            
            szResponse[0] = 6;
            
            Usart1_DMA_Send(szResponse, 3);
            
            while(SendAndWaitRfidDataProc(PRIMECONTINUEREADING) == FALSE);
            
            while(SendAndWaitRfidDataProc(CONTINUEREADING) == FALSE);
        }
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x07) && (*(pBuf + 2) == 0xAA))//增强速度指令
        {
            bRet = TRUE;
            
            szResponse[0] = 7;
            
            Usart1_DMA_Send(szResponse, 3);
            
            while(SendAndWaitRfidDataProc(ENHANCESPEED1) == FALSE);
            
            while(SendAndWaitRfidDataProc(ENHANCESPEED2) == FALSE);
            
            while(SendAndWaitRfidDataProc(ENHANCESPEED3) == FALSE);
            
            while(SendAndWaitRfidDataProc(ENHANCESPEED4) == FALSE);
            
            while(SendAndWaitRfidDataProc(ENHANCESPEED5) == FALSE);
            
            while(SendAndWaitRfidDataProc(ENHANCESPEED6) == FALSE);
            
            while(SendAndWaitRfidDataProc(PRIMECONTINUEREADING) == FALSE);
            
            while(SendAndWaitRfidDataProc(CONTINUEREADING) == FALSE);
        }
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x08) && (*(pBuf + 2) == 0xAA))//增强距离指令 
        {
            bRet = TRUE;
            
            szResponse[0] = 8;
            
            Usart1_DMA_Send(szResponse, 3);
            
            while(SendAndWaitRfidDataProc(ENHANCEDISTANCE) == FALSE);
            
            while(SendAndWaitRfidDataProc(PRIMECONTINUEREADING) == FALSE);
            
            while(SendAndWaitRfidDataProc(CONTINUEREADING) == FALSE);
        }
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x09) && (*(pBuf + 2) == 0xAA))//检索特定标签
        {
            bRet = TRUE;
            
            szResponse[0] = 9;
            
            Usart1_DMA_Send(szResponse, 3);
            
            while(SendAndWaitRfidDataProc(PRIMECONTINUEREADING) == FALSE);
            
            while(SendAndWaitRfidDataProc(CONTINUEREADING) == FALSE);
        }
    }
    return bRet;
    
}


STATIC VOID GetCurrentTimeString(U8 *g_pData)
{
    U32 u32Tick100us;
    u32Tick100us = GetTickCount();
    *(g_pData) = '#';
    *(g_pData + 1) = (u32Tick100us/1000000000)+'0' ;
    *(g_pData + 2) = ((u32Tick100us/100000000)%10)+'0' ;
    *(g_pData + 3) = ((u32Tick100us/10000000)%10)+'0' ;
    *(g_pData + 4) = ((u32Tick100us/1000000)%10)+'0' ;
    *(g_pData + 5) = ((u32Tick100us/100000)%10)+'0' ;
    *(g_pData + 6) = ((u32Tick100us/10000)%10)+'0' ;
    *(g_pData + 7) = ((u32Tick100us/1000)%10)+'0' ;
    *(g_pData + 8) = ((u32Tick100us/100)%10)+'0' ;
    *(g_pData + 9) = ((u32Tick100us/10)%10)+'0' ;
    *(g_pData + 10) = (u32Tick100us%10)+'0' ;

}

STATIC VOID GetCurrentTagString(U8 *g_pData, U8 u8Value)
{
    *(g_pData) = '#';
    *(g_pData + 1) = ((u8Value/100)%10)+'0' ;
    *(g_pData + 2) = ((u8Value/10)%10)+'0' ;
    *(g_pData + 3) = (u8Value%10)+'0' ;

}

STATIC RunRfidProc(VOID)
{
    while(SendAndWaitRfidDataProc(PRIMECONTINUEREADING) == FALSE);

    while(SendAndWaitRfidDataProc(CONTINUEREADING) == FALSE);
}

STATIC StopRfidProc(VOID)
{
    U8 u8Cnt = 0;
    BOOL bRet;
    do
    {
        bRet = SendAndWaitRfidDataProc(STOPREADING);
        u8Cnt++;
    }while((bRet == FALSE) && (u8Cnt < 10));
    if(u8Cnt == 10)
    {
        EnterException(ERR_RFID_STOP);
    }


}

VOID TestRFID(VOID)
{
    U8 u8type;
    
    U16 u16Count, u16Cnt;
    
    U8 *szTestTest, *szTimeBuf, *szTagBuf, *szOutputBuf;
    
    szTestTest = mymalloc(SRAMIN, RFIDDATACOUNT);
    
    szTimeBuf = mymalloc(SRAMIN, TIMELENGTH);
    
    szTagBuf = mymalloc(SRAMIN, TAGLENGTH);
    
    szOutputBuf = mymalloc(SRAMIN, TIMELENGTH + TAGLENGTH + 2);
    
    if((szTestTest == NULL) || (szTimeBuf == NULL) || (szTagBuf == NULL) || (szOutputBuf == NULL))
    {
        EnterException(ERR_TEST_MALLOC_FAIL);
    }
    
    
    RfidInitProc(); 
    
    printf("RFID test...\r\n");
    
    printf("Please input Cmd or SubCmd\r\n");
    
    while(1)
	{
        u16Count = GetCommDataLength();
        if(u16Count == 10)
        {
            ReadCommData(szTestTest, u16Count);
            HandleCommCmdProc(szTestTest, &u8type);
            switch(u8type)
            {
                case COMM_CMD_START:
                    RunRfidProc();//开启RFID设备 
                    break;
                case COMM_CMD_STOP:                     
                    StopRfidProc();//关掉RFID设备
                    break;
                case COMM_CMD_CLRMILEAGE:
                    mileage_init();         //清除里程数据
                    break;
                case COMM_CMD_SAVEDATA:                  
                    break;
                default:
                    break;
            }
            
        }        

       if(GetUsartCurrentLength(USART1_TYPE) != 0)
       {
            u16Count = GetUsartCurrentLength(USART1_TYPE);
            ClearUsartCurrentLength(USART1_TYPE);
            memcpy(szTestTest, g_pUsart1_rx_buf, u16Count);
            if(AnalyzeCmd(szTestTest, u16Count) == FALSE)
                Usart3_DMA_Send(szTestTest, u16Count);
        }
        else if(GetUsartCurrentLength(USART3_TYPE) != 0)
        {
            u16Count = GetUsartCurrentLength(USART3_TYPE);
            ClearUsartCurrentLength(USART3_TYPE);
            memcpy(szTestTest, g_pUsart3_rx_buf, u16Count);
           // Usart1_DMA_Send(szTestTest, u16Count);
            for(u16Cnt = 0; u16Cnt < u16Count; u16Cnt++)
            {
                if((szTestTest[u16Cnt] == 0xff) && (szTestTest[u16Cnt + 1] == 0x18) && (szTestTest[u16Cnt + 2] == 0x22))
                {
                    if(CompareTag(szTestTest + u16Cnt + 15) == TRUE)
                    {
                        GetCurrentTagString(szTagBuf, g_cRfidVar.u8Tag);
                        GetCurrentTimeString(szTimeBuf);
                        memcpy(szOutputBuf, szTimeBuf, TIMELENGTH);
                        memcpy(szOutputBuf + TIMELENGTH, szTagBuf, TAGLENGTH);
                        szOutputBuf[TIMELENGTH + TAGLENGTH] = '\r';
                        szOutputBuf[TIMELENGTH + TAGLENGTH + 1] = '\n';
                        Usart1_DMA_Send(szOutputBuf, TIMELENGTH + TAGLENGTH + 2);
                        DisplayRfidNum(g_cRfidVar.u8Tag/10, g_cRfidVar.u8Tag%10);
                        break;
                    }
                }
                
            }
            
        }
                                    
    }
          
}

VOID TestCalcuate(VOID)
{
    U16 u16Count, u16Value;
    U8 szTestTest[RFIDDATACOUNT] = {0};
    printf("RFID CRC Please input :\r\n");
    while(1)
	{
        if(GetUsartCurrentLength(USART1_TYPE) != 0)
        {
            u16Count = GetUsartCurrentLength(USART1_TYPE);
            ClearUsartCurrentLength(USART1_TYPE);
            memcpy(szTestTest, g_pUsart1_rx_buf, u16Count);
            u16Value = CalculateRfidCrc(szTestTest, u16Count);
            printf("CRC = %x\r\n", u16Value);
        }
    }        
		
}
