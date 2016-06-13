#include "comm.h"

enum
{
	COMM_DATA_PASS = 1,
	COMM_DATA_ERROR,
};

STATIC U8 *g_pCommbuf;

STATIC U8 g_u8State;


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


STATIC VOID WriteCommData(U8 *pBuf, U16 u16Count)
{
	USART3_Send(pBuf, &u16Count);
}

VOID SendCommData(U8 u8Type)
{
	g_pCommbuf[0] = COMM_HEADER;
	g_pCommbuf[1] = COMM_DIRECTION;
	g_pCommbuf[4] = 0;//应答长度为0
	g_pCommbuf[5] = 0;//应答长度为0
	g_pCommbuf[6] = COMM_SEQUENTIAL;
	g_pCommbuf[8] = COMM_END1;
	g_pCommbuf[9] = COMM_END2;
	
	switch(u8Type)
	{
		case COMM_STATE:
			g_pCommbuf[2] = COMM_MAINCMD_STATE;
			g_pCommbuf[3] = g_u8State;
			break;
		default:
			break;
		
	}
	g_pCommbuf[7] = CalcCheckSum(g_pCommbuf + 1, 10 - 4);
	WriteCommData(g_pCommbuf, 10);
}


VOID CommInit(VOID)
{
	U8 *pBuf;
	uart3_init(115200, 256, 256);
	pBuf = mymalloc(SRAMIN, 256);
	if(pBuf == NULL)
	{
		EnterException(ERR_COMM_MALLOC_FAIL);
	}
	else
	{
		g_pCommbuf = pBuf;
	}

	
}



VOID ReceiveCommData(VOID)
{
	U16 u16Length;
	U8 u8Value;
	
	u16Length = GetUsartCurrentLength(USART3_TYPE);
	
	if(u16Length != 0)
	{
		
		
		g_u8State = COMM_DATA_ERROR;
		
		memcpy(g_pCommbuf, g_pUsart3_rx_buf, u16Length);
		
		if(g_pCommbuf[0] == COMM_HEADER)
		{
			u8Value = CalcCheckSum(g_pCommbuf + 1, u16Length - 4);
			
			if(u8Value == g_pCommbuf[u16Length - 3])//校验成功时返回正确应答
			{
				g_u8State = COMM_DATA_PASS;
								
				
			}
		}
	}
}

