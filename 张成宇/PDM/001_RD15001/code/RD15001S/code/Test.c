#include <c8051f340.h>
#include <intrins.h>   
#include "stdio.h"
#include "uart.h"
#include "hum_tem.h"
#include "Init.h"	 
extern unsigned char Am2305_Read();
extern unsigned char Sensor_Data[5];
extern void DelayUs(unsigned int t);
extern void DelayMs(unsigned int t);

void TestUart1(void)
{
	U16 xdata u16Length;
	U8 xdata szData[20];
	while(1)
	{
		ReceiveUsart1Data(szData, &u16Length);
		if(u16Length)
		{
			Uart1_Tx(szData, u16Length);
		}
		
	}

}

void TestUart2(void)
{
	U16 xdata u16Length;
	U8 xdata szData[20];
	while(1)
	{
		ReceiveUsart2Data(szData, &u16Length);
		if(u16Length)
		{
			Uart2_Tx(szData, u16Length);
		}
	}
}
#define TIMELENGTH  11
#define TAGLENGTH  4
void TestUartRfid(void)
{
    U16 xdata u16Cnt, xdata u16Length;
    
    U8 xdata szData[RFIDDATACOUNT], xdata szTestTest[RFIDDATACOUNT], xdata szTimeBuf[TIMELENGTH], xdata szTagBuf[TAGLENGTH], xdata szOutputBuf[TIMELENGTH + TAGLENGTH + 2];
  

	while(1)
	{

		ReceiveUsart1Data(szData, &u16Length);
		if(u16Length)
		{
			memcpy(szTestTest, szData, u16Length);
//	            if(AnalyzeCmd(szTestTest, u16Length) == FALSE)
                Uart2_Tx(szTestTest, u16Length);
		}

		ReceiveUsart2Data(szData, &u16Length);
		if(u16Length)
		{
			memcpy(szTestTest, szData, u16Length);
			Uart1_Tx(szTestTest, u16Length);
	            for(u16Cnt = 0; u16Cnt < u16Length; u16Cnt++)
	            {
	                if((szTestTest[u16Cnt] == 0xff) && (szTestTest[u16Cnt + 1] == 0x18) && (szTestTest[u16Cnt + 2] == 0x22))
	                {
	                    if(HandleTag(szTestTest + u16Cnt + 15) == TRUE)
	                    {
//	                        GetCurrentTagString(szTagBuf, g_cRfidVar.u8Tag);
//	                        GetCurrentTimeString(szTimeBuf);
	                        memcpy(szOutputBuf, szTimeBuf, TIMELENGTH);
	                        memcpy(szOutputBuf + TIMELENGTH, szTagBuf, TAGLENGTH);
	                        szOutputBuf[TIMELENGTH + TAGLENGTH] = '\r';
	                        szOutputBuf[TIMELENGTH + TAGLENGTH + 1] = '\n';
	                        Uart1_Tx(szOutputBuf, TIMELENGTH + TAGLENGTH + 2);
	                        break;
	                    }
	                }
	                
	            }
		}


	}

}

void TestUartTimer(void)
{
	U32 xdata u32Count, xdata u32CurrentCount;
	U8 xdata szData[20] = {"test timer uart"};
	u32Count = GetTickCount();
	while(1)
	{
		 u32CurrentCount = GetTickCount();
		 if((u32CurrentCount - u32Count) > 500)
		 {
			  Uart1_Tx(szData, 15);
			  u32Count = GetTickCount();
		 }
	}

}
 
void TestTemperature(void)
{
	int xdata i;
	while(1)
	{
		Am2305_Read();
		for(i=0;i<5;i++)
		{
			Uart1_Tx(Sensor_Data + i, 1);
		}
	
		for(i = 0; i< 30; i++)	  //
		{		
			DelayMs(100);
		}
	}
}


 