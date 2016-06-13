#include "comm.h"

enum
{
	COMM_DATA_PASS = 1,
	COMM_DATA_ERROR,
};

STATIC U8 *g_pCommbuf;

STATIC U8 g_u8State;

STATIC U8 u8KeyNumbuer = KEY_INVALID;//按键编号

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

VOID DisplayPercentage(U8 u8first, U8 u8Second)
{
	g_pCommbuf[0] = COMM_HEADER;
	g_pCommbuf[1] = COMM_DIRECTION;
	g_pCommbuf[2] = COMM_MAINCMD_DISPLAY;
	g_pCommbuf[3] = COMM_SUBCMD_DISPLAY_PERCENTAGE;//子命令
	g_pCommbuf[4] = 0;//	 大端
	g_pCommbuf[5] = 2;//    大端
	g_pCommbuf[6] = COMM_SEQUENTIAL;
	g_pCommbuf[7] = u8first;
	g_pCommbuf[8] = u8Second;
	g_pCommbuf[10] = COMM_END1;
	g_pCommbuf[11] = COMM_END2;
	g_pCommbuf[9] = CalcCheckSum(g_pCommbuf + 1, 12 - 4);
	
	WriteCommData(g_pCommbuf, 12);
	
}

VOID DisplayInstruction(U8 u8first, U8 u8Second)
{
	g_pCommbuf[0] = COMM_HEADER;
	g_pCommbuf[1] = COMM_DIRECTION;
	g_pCommbuf[2] = COMM_MAINCMD_DISPLAY;
	g_pCommbuf[3] = COMM_SUBCMD_DISPLAY_INSTRUCTION;//子命令
	g_pCommbuf[4] = 0;//	 大端
	g_pCommbuf[5] = 2;//    大端
	g_pCommbuf[6] = COMM_SEQUENTIAL;
	g_pCommbuf[7] = u8first;
	g_pCommbuf[8] = u8Second;
	g_pCommbuf[10] = COMM_END1;
	g_pCommbuf[11] = COMM_END2;
	g_pCommbuf[9] = CalcCheckSum(g_pCommbuf + 1, 12 - 4);
	
	WriteCommData(g_pCommbuf, 12);
	
}

//回传给显示板显示数据
VOID DisplayString(U8 x, U8 y, U8 *pBuf)
{
	U16 u16Length, u16LengthEx;
		
	u16LengthEx = strlen((char *)pBuf);
	
	u16Length = u16LengthEx + 2;
	
	g_pCommbuf[0] = COMM_HEADER;
	g_pCommbuf[1] = COMM_DIRECTION;
	g_pCommbuf[2] = COMM_MAINCMD_DISPLAY;
	g_pCommbuf[3] = COMM_SUBCMD_DISPLAY_STRING;//子命令
	g_pCommbuf[4] = HIBYTE(u16Length);//	 大端
	g_pCommbuf[5] = LOBYTE(u16Length);//    大端
	g_pCommbuf[6] = COMM_SEQUENTIAL;
	g_pCommbuf[7] = x;
	g_pCommbuf[8] = y;
	memcpy(g_pCommbuf + 9, pBuf, strlen((char *)pBuf));
	g_pCommbuf[9 + u16LengthEx] = CalcCheckSum(g_pCommbuf + 1, 6 + u16Length);
	g_pCommbuf[10 + u16LengthEx] = COMM_END1;
	g_pCommbuf[11 + u16LengthEx] = COMM_END2;
	
	WriteCommData(g_pCommbuf, 10 + u16Length);
	
	
	
}

VOID DisplayClear(U8 x0, U8 y0, U8 x1, U8 y1, BOOL bType)
{
	U16 u16Length;
	 
	u16Length = 5;
	
	g_pCommbuf[0] = COMM_HEADER;
	g_pCommbuf[1] = COMM_DIRECTION;
	g_pCommbuf[2] = COMM_MAINCMD_DISPLAY;
	g_pCommbuf[3] = COMM_SUBCMD_DISPLAY_CLEAR;//子命令
	g_pCommbuf[4] = HIBYTE(u16Length);//	 大端
	g_pCommbuf[5] = LOBYTE(u16Length);//    大端
	g_pCommbuf[6] = COMM_SEQUENTIAL;
	g_pCommbuf[7] = bType;
	g_pCommbuf[8] = x0;
	g_pCommbuf[9] = y0;
	g_pCommbuf[10] = x1;
	g_pCommbuf[11] = x1;
	g_pCommbuf[12] = CalcCheckSum(g_pCommbuf + 1, 6 + u16Length);
	g_pCommbuf[13] = COMM_END1;
	g_pCommbuf[14] = COMM_END2;
	
	WriteCommData(g_pCommbuf, 10 + u16Length);
	
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
								
				if(g_pCommbuf[2] == COMM_MAINCMD_KEY)
				{
					SetKeyNumber(g_pCommbuf[3]);
				}
//				if()//特定命令才需要返回状态，目前只有显示指令，故不返回状态
//				{
//					SendCommData(COMM_STATE);
//				}
				
			}
		}
	}
}

U8 GetKeyNumber(VOID)
{
	return u8KeyNumbuer;
}
VOID SetKeyNumber(U8 u8Type)
{
	u8KeyNumbuer = u8Type;
}
