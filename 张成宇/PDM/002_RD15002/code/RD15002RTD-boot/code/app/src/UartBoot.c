#include "Serial.h"  
#include "flash.h"
#include "Led.h"
#include "UartBoot.h"
//下发进入boot命令
#define SB_FORCE_BOOT_CMD           0x00
// Commands to Bootloader
#define SB_WRITE_CMD                0x01    //写数据到Flash的命令
#define SB_READ_CMD                 0x02    //写完bin文件后，从头开始从flash中回读回来
#define SB_ENABLE_CMD               0x03    
#define SB_HANDSHAKE_CMD            0x04
#define SB_HANDSHAKE_Ex_CMD         0x05

//Start byte
#define SB_SOF                      0xFE

// Bootloader Serial Interface Subsystem
#define SB_RPC_SYS_BOOT             0x4D

// Status codes
#define SB_SUCCESS                  0
#define SB_FAILURE                  1
#define SB_INVALID_FCS              2
#define SB_INVALID_FILE             3
#define SB_FILESYSTEM_ERROR         4
#define SB_ALREADY_STARTED          5
#define SB_NO_RESPOSNE              6
#define SB_VALIDATE_FAILED          7
#define SB_CANCELED                 8  



STATIC U32 g_u32Offset = 0;

//计算数据的校验和
STATIC U8 CalcCheckSum(U8* pSrcData, U16 wDataLen)
{
    U8 bCheckSum;
    int i;
    
    if(pSrcData == NULL)
        return 0;
    
    bCheckSum = pSrcData[0];
    if(wDataLen == 0xFFFF)
       return 0;
    for(i = 1; i <= wDataLen - 1; i++)
    {
        bCheckSum ^= pSrcData[i]; 
    }
    return bCheckSum;    
}

U8 ParseCmd(U8 *pBuf, U16 u16Cnt)
{
    U8 u8Type = SB_NULL;
    U8 u8Value;
    U8 u8Length;
    
	u8Length = pBuf[1];
	if((pBuf[0] == SB_SOF) && (pBuf[2] == SB_RPC_SYS_BOOT))
	{
		u8Value = CalcCheckSum(pBuf + 1, 3 + u8Length);
		if(u8Value == pBuf[4 + u8Length])//校验成功
		{
			switch(pBuf[3])
			{
				case SB_FORCE_BOOT_CMD:
					u8Type = SB_FORCE_BOOT;
					break;
				case SB_ENABLE_CMD:
					u8Type = SB_ENABLE;
					break;
				case SB_HANDSHAKE_CMD:
					u8Type = SB_HANDSHAKE;
					break;
				case SB_HANDSHAKE_Ex_CMD:
					u8Type = SB_HANDSHAKE_Ex;
				default:
					break;
			}
		}
		else if(pBuf[1] == 0xff)//这里特殊处理来兼容上位机软件
		{
			switch(pBuf[3])
			{
				case SB_WRITE_CMD:
					u8Type = SB_WRITE;
					break;
				case SB_READ_CMD:
					u8Type = SB_READ;
					break;
			}
		}
	}
    
    return u8Type;
}

STATIC VOID Response(U8 *pBuf)
{
	U16 u16Cnt;
    pBuf[1] = 0x01;
    pBuf[3] = pBuf[3] | 0x80;
    pBuf[4] = SB_SUCCESS;
    pBuf[5] = CalcCheckSum(pBuf + 1, 4);
	u16Cnt = 6;
	UsartSend(USART1, pBuf, u16Cnt);
}
STATIC VOID EnterBootProc(VOID)
{
    NVIC_SystemReset();
}

STATIC VOID EnterWriteProc(U8 *pBuf, U16 u16Count)
{
	FLASH_error   FLASH_value;	
	FLASH_value = FlashWriteSTM32(STM_APP_ADDRESS + g_u32Offset, u16Count, pBuf+2);
	g_u32Offset = g_u32Offset + 1024;
	if(FLASH_value != RES_OK)
	{
		while(1)
		{
			LedOff();
			DelayMs(500);
			LedOn();
			DelayMs(500);
		}
	}
	FLASH_value = FlashWriteSTM32(STM_APP_ADDRESS + g_u32Offset, u16Count, pBuf+2+1024);
	if(FLASH_value != RES_OK)
	{
		while(1)
		{
			LedOff();
			DelayMs(500);
			LedOn();
			DelayMs(500);
		}
	}
	g_u32Offset = g_u32Offset + 1024;
		
}

STATIC VOID EnterReadProc(VOID)
{
    
}

STATIC VOID EnterAppProc(VOID)
{
	LedOff();
	FlashInit(BOOTINFOR_ADDRESS);
	JumpToApp();

}

VOID UartBoot(VOID)
{
	U32 u32TickCount;
	U16 u16Count;	
    U8 u8Type;
	S32	s32Count;
	U8 *szData = malloc(MAXSIZE_A + 50);
	u32TickCount = GetSecondOfWeek();
	
	if(szData == NULL)
	{
		EnterException(ERR_BOOT_MALLOC_FAIL);
	}		
	while(1)
    {
        if(GetQueueLength(pUart1QueueInfo))
        {
			s32Count = GetTickCount() - GetUartReceiveTime(USART1);

			if(s32Count > 20)
			{
				
				ReadUsartData(USART1, szData, &u16Count);
				u8Type = ParseCmd(szData, u16Count);
				if(u8Type != SB_NULL)
				{
					u32TickCount = GetSecondOfWeek();//重新计算超时时间
					switch(u8Type)
					{
						case SB_FORCE_BOOT:
							Response(szData);
							EnterBootProc();
							break;
						case SB_WRITE:
							EnterWriteProc(szData + 4, u16Count - 7);
							Response(szData);
							break;
						case SB_READ:
							EnterReadProc();
							Response(szData);
							break;
						case SB_ENABLE:
							Response(szData);
							EnterAppProc();					
							break;
						case SB_HANDSHAKE:
							Response(szData);
							g_u32Offset = 0;
							break;
						case SB_HANDSHAKE_Ex:
							Response(szData);
							break;
						default:
							break;
					}
				}
			}
        }
		
		if((GetSecondOfWeek() - u32TickCount) > 3)
		{
			free(szData);
			EnterAppProc();
			u32TickCount = GetSecondOfWeek();
		}
        
    }   
}
