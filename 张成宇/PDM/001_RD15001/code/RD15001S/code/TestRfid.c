#include "app_rfid.h"
#include "uart.h"
#include "Init.h"
#include "stdlib.h"
#define TIMELENGTH  11
#define TAGLENGTH  4
#define ENWIRONMENTLENGTH 35
extern uchar const code g_szGetCurrentProgram[5];
extern uchar const code g_szBootFirmware[5];
extern uchar const code g_szSetFrequencyChannel[6];
extern uchar const code g_szSetProtocol[7];
extern uchar const code g_szSetAntenna[8];
extern uchar const code g_szClearBuffer[5];
extern uchar const code g_szSearchTag[10];
extern uchar const code g_szGetTagdata[8];

extern uchar const code g_szGetTagIddata[8];
extern uchar const code g_szPrimeContinueReading[8];
extern uchar const code g_szContinueReading[21];
extern uchar const code g_szEnhanceDistance[7];
extern uchar const code g_szEnhanceSpeed1[8];
extern uchar const code g_szEnhanceSpeed2[8];
extern uchar const code g_szEnhanceSpeed3[8];
extern uchar const code g_szEnhanceSpeed4[8];
extern uchar const code g_szEnhanceSpeed5[8];
extern uchar const code g_szEnhanceSpeed6[9];
extern uchar const code g_szContinueReadingEx[21];
extern uchar const code g_szStopReading[8];
extern uchar const code g_szOnceMode[8];

extern unsigned char xdata Sensor_Data[5];
STATIC BOOL AnalyzeCmd(P_U8 pBuf, U16 u16Count)
{
    BOOL xdata bRet = FALSE;
    U8 xdata szResponse[3] = {0x00, 0x90, 0x00};

    if(u16Count == 3)
    {
        if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x01) && (*(pBuf + 2) == 0xAA))//关机指令
        {
            bRet = TRUE;
            RFID_SHUTDOWN();
            szResponse[0] = 1;
            Uart1_Tx(szResponse, 3);
            
        }       
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x02) && (*(pBuf + 2) == 0xAA))//开机指令
        {
            bRet = TRUE;
            RFID_UNSHUTDOWN();
            szResponse[0] = 2;
            Uart1_Tx(szResponse, 3);
            
        }
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x03) && (*(pBuf + 2) == 0xAA))//读取系统状态
        {
            bRet = TRUE;
            szResponse[0] = 3;
            Uart1_Tx(szResponse, 3);
        }
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x04) && (*(pBuf + 2) == 0xAA))//测试指令
        {
            bRet = TRUE;
            szResponse[0] = 4;
            Uart1_Tx(szResponse, 3);
        }
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x05) && (*(pBuf + 2) == 0xAA))//自动指令
        {
            bRet = TRUE;
            szResponse[0] = 5;
            Uart1_Tx(szResponse, 3);
                       
            while(SendAndWaitRfidDataProc(PRIMECONTINUEREADING) == FALSE);
            
            while(SendAndWaitRfidDataProc(CONTINUEREADING) == FALSE);
            
        }
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x06) && (*(pBuf + 2) == 0xAA))//自动唯一ID指令
        {
            bRet = TRUE;
            
            szResponse[0] = 6;
            
            Uart1_Tx(szResponse, 3);
            
            while(SendAndWaitRfidDataProc(PRIMECONTINUEREADING) == FALSE);
            
            while(SendAndWaitRfidDataProc(CONTINUEREADING) == FALSE);
        }
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x07) && (*(pBuf + 2) == 0xAA))//增强速度指令
        {
            bRet = TRUE;
            
            szResponse[0] = 7;
            
            Uart1_Tx(szResponse, 3);
            
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
            
            Uart1_Tx(szResponse, 3);
            
            while(SendAndWaitRfidDataProc(ENHANCEDISTANCE) == FALSE);
            
            while(SendAndWaitRfidDataProc(PRIMECONTINUEREADING) == FALSE);
            
            while(SendAndWaitRfidDataProc(CONTINUEREADING) == FALSE);
        }
        else if((*pBuf == 0xAA) && (*(pBuf + 1) == 0x09) && (*(pBuf + 2) == 0xAA))//检索特定标签
        {
            bRet = TRUE;
            
            szResponse[0] = 9;
            
            Uart1_Tx(szResponse, 3);
            
            while(SendAndWaitRfidDataProc(PRIMECONTINUEREADING) == FALSE);
            
            while(SendAndWaitRfidDataProc(CONTINUEREADING) == FALSE);
        }
        else if((*pBuf == 0xfe) && (*(pBuf + 1) == 0xfe) && (*(pBuf + 2)< 35))//开机指令
        {
            bRet = TRUE;

            
            while(SendAndWaitRfidDataProc(STOPREADING) == FALSE);
            
            while(SendAndWaitRfidDataProc(ONCEMODE) == FALSE);

        	while(SendAndWaitRfidDataProcEnhance((*(pBuf + 2) * 100)) == FALSE);	 //调整功率

        	while(SendAndWaitRfidDataProc(PRIMECONTINUEREADING) == FALSE);
        	
        	while(SendAndWaitRfidDataProc(CONTINUEREADING) == FALSE);
            szResponse[0] = 0xef;
            szResponse[1] = 0xfe;
            szResponse[2] = *(pBuf + 2);
            Uart1_Tx(szResponse, 3);
            
        }
    }
    return bRet;
    
}


STATIC VOID GetCurrentTimeString(U8 *g_pData)
{
    U32 xdata u32Tick;
    u32Tick = GetTickCount();
    *(g_pData) = '#';
    *(g_pData + 1) = (u32Tick/1000000000)+'0' ;
    *(g_pData + 2) = ((u32Tick/100000000)%10)+'0' ;
    *(g_pData + 3) = ((u32Tick/10000000)%10)+'0' ;
    *(g_pData + 4) = ((u32Tick/1000000)%10)+'0' ;
    *(g_pData + 5) = ((u32Tick/100000)%10)+'0' ;
    *(g_pData + 6) = ((u32Tick/10000)%10)+'0' ;
    *(g_pData + 7) = ((u32Tick/1000)%10)+'0' ;
    *(g_pData + 8) = ((u32Tick/100)%10)+'0' ;
    *(g_pData + 9) = ((u32Tick/10)%10)+'0' ;
    *(g_pData + 10) = (u32Tick%10)+'0' ;

}

STATIC VOID GetCurrentTagString(U8 *g_pData, U8 u8Value)
{
    *(g_pData) = '#';
    *(g_pData + 1) = ((u8Value/100)%10)+'0' ;
    *(g_pData + 2) = ((u8Value/10)%10)+'0' ;
    *(g_pData + 3) = (u8Value%10)+'0' ;

}

STATIC VOID GetCurrentEnwironment(U8 *g_pData)
{
	float xdata Temperature, xdata Humidity;
	U8 u8AM2305_Check;
	u8AM2305_Check = Sensor_Data[0] + Sensor_Data[1] + Sensor_Data[2] + Sensor_Data[3];
	if(u8AM2305_Check == Sensor_Data[4])
	{
		Humidity = (Sensor_Data[0]*256 + Sensor_Data[1])/10.0;
		Temperature = (Sensor_Data[2]*256 + Sensor_Data[3])/10.0;
	}
	else
	{
		Humidity = 0;
		Temperature = 0;
	}
	sprintf(g_pData, "#Humidity = %3.1f#Temperature = %3.1f",Humidity,Temperature);


}

STATIC VOID RunRfidProc(VOID)
{
    while(SendAndWaitRfidDataProc(PRIMECONTINUEREADING) == FALSE);

    while(SendAndWaitRfidDataProc(CONTINUEREADING) == FALSE);
}

STATIC VOID StopRfidProc(VOID)
{
    U8 xdata u8Cnt = 0;
    BOOL xdata bRet;
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
    U16 xdata u16Cnt, xdata u16Length;
    
    U8 xdata szData[RFIDDATACOUNT], xdata szTestTest[RFIDDATACOUNT], xdata szTimeBuf[TIMELENGTH], xdata szTagBuf[TAGLENGTH], xdata szOutputBuf[TIMELENGTH + TAGLENGTH + ENWIRONMENTLENGTH+ 2], xdata szEnwironmentBuf[ENWIRONMENTLENGTH];
	
    U32 u32Tick;
	RfidInitProc();
	
	while(SendAndWaitRfidDataProc(ONCEMODE) == FALSE);

	while(SendAndWaitRfidDataProcEnhance(2500) == FALSE);	 //调整功率

	while(SendAndWaitRfidDataProc(PRIMECONTINUEREADING) == FALSE);
	
	while(SendAndWaitRfidDataProc(CONTINUEREADING) == FALSE);

    u32Tick = GetTickCount();

	while(1)
	{
        if((GetTickCount() - u32Tick) > 3000)
        {
            u32Tick = GetTickCount();
            Am2305_Read();
        }
        
		ReceiveUsart1Data(szData, &u16Length);
		if(u16Length)
		{
			memcpy(szTestTest, szData, u16Length);
            if(AnalyzeCmd(szTestTest, u16Length) == FALSE)
                Uart2_Tx(szTestTest, u16Length);
		}

		ReceiveUsart2Data(szData, &u16Length);
		if(u16Length)
		{
			memcpy(szTestTest, szData, u16Length);
            for(u16Cnt = 0; u16Cnt < u16Length; u16Cnt++)
            {
                if((szTestTest[u16Cnt] == 0xff) && (szTestTest[u16Cnt + 1] == 0x18) && (szTestTest[u16Cnt + 2] == 0x22) )		
                {
                    if(HandleTag(szTestTest + u16Cnt + 15) == TRUE)
                    {
                        GetCurrentTagString(szTagBuf, g_u8TagOffset);
                        GetCurrentTimeString(szTimeBuf);
						GetCurrentEnwironment(szEnwironmentBuf);
                        memcpy(szOutputBuf, szTimeBuf, TIMELENGTH);
                        memcpy(szOutputBuf + TIMELENGTH, szTagBuf, TAGLENGTH);
						memcpy(szOutputBuf + TIMELENGTH + TAGLENGTH, szEnwironmentBuf, ENWIRONMENTLENGTH);
                        szOutputBuf[TIMELENGTH + TAGLENGTH + ENWIRONMENTLENGTH] = '\r';
                        szOutputBuf[TIMELENGTH + TAGLENGTH + ENWIRONMENTLENGTH+ 1] = '\n';
                        Uart1_Tx(szOutputBuf, TIMELENGTH + TAGLENGTH + ENWIRONMENTLENGTH + 2);
                    }
                    
                }
                
            }
		}


	}
             
}

VOID TestCalcuate(VOID)
{
    U16 xdata u16Count, xdata u16Value;
    U8 xdata szData[RFIDDATACOUNT] = {0};
    Uart1_Tx_End("RFID CRC Please input :\r\n");
    while(1)
	{
		ReceiveUsart1Data(szData, &u16Count);
		if(u16Count)
		{
            u16Value = CalculateRfidCrc(szData, u16Count);
			sprintf(szData, "CRC = %x\r\n", u16Value);
            Uart1_Tx_End(szData);
		}
    }        
		
}



