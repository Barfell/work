#include "comm.h"
#include "syn.h"
#include "GUI.h"
#include "CPLD.h" 
enum
{
	COMM_DATA_PASS = 1,
	COMM_DATA_ERROR,
};

STATIC U8 *g_pCommbuf;

STATIC U8 g_u8State;

U8 CalcCheckSum(U8* pSrcData, U16 wDataLen)
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
	USART2_Send(pBuf, &u16Count);
}


VOID CommInit(VOID)
{
	U8 *pBuf;
	uart2_init(115200, 256, 256);
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
		case COMM_KEY:
			g_pCommbuf[2] = COMM_MAINCMD_KEY;
			g_pCommbuf[3] = GetKeyNumber();
			break;
		default:
			break;
		
	}
	g_pCommbuf[7] = CalcCheckSum(g_pCommbuf + 1, 10 - 4);
	WriteCommData(g_pCommbuf, 10);
}


VOID HandleDisplay(VOID)
{
	U16 u16Length;
	U8 szBuf[20];
	const GUI_FONT GUI_UNI_PTR *pOldFont;
	pOldFont = GUI_SetFont(&GUI_Font6x8);//GUI_Font6x8
	
	u16Length = MAKEWORD(g_pUsart2_rx_buf[5], g_pUsart2_rx_buf[4]) - 2;
	if(g_pUsart2_rx_buf[3] == COMM_SUBCMD_DISPLAY_STRING)
	{
		memcpy(szBuf, g_pUsart2_rx_buf + 9, u16Length);
		*(szBuf + u16Length) = '\0';
		GUI_ClearRect(0, g_pUsart2_rx_buf[8],  128, g_pUsart2_rx_buf[8] + 7);//这里加7是因为避免影响下一行的数据
		GUI_DispStringAt((char *)szBuf, g_pUsart2_rx_buf[7], g_pUsart2_rx_buf[8]); 		
		if(memcmp(szBuf, "Start test...", 13) == 0)
		{
			CpldOn();
		}
//		else if(memcmp(szBuf, "Start save...", 13) == 0)
//		{
//			CpldOff();
//		}			
	}
	else if(g_pUsart2_rx_buf[3] == COMM_SUBCMD_DISPLAY_CLEAR)
	{
		if(g_pUsart2_rx_buf[7] == TRUE)
		{
			GUI_Clear();

		}
		else
		{
			GUI_ClearRect(g_pUsart2_rx_buf[8], g_pUsart2_rx_buf[9], g_pUsart2_rx_buf[8] + g_pUsart2_rx_buf[10], g_pUsart2_rx_buf[9] + g_pUsart2_rx_buf[11]);
			
		}
	}
	GUI_SetFont(pOldFont);
}

STATIC U8 g_TestRfidRev = 0;
	
VOID ReceiveCommData(VOID)
{
    U32 u32Tick;
	U16 u16Length;
	U8 u8Value;


	u16Length = GetUsartCurrentLength(USART2_TYPE);
	if(u16Length != 0)
	{
		ClearUsartCurrentLength(USART2_TYPE);
		u16Length = MAKEWORD(g_pUsart2_rx_buf[5], g_pUsart2_rx_buf[4]);
		if((g_pUsart2_rx_buf[0] == COMM_HEADER) && (g_pUsart2_rx_buf[u16Length + 8] == COMM_END1) && (g_pUsart2_rx_buf[u16Length + 9] == COMM_END2))
		{
			u8Value = CalcCheckSum(g_pUsart2_rx_buf + 1, 6 + u16Length);
			if(u8Value == g_pUsart2_rx_buf[7 + u16Length])
			{
				switch(g_pUsart2_rx_buf[2])
				{
					case COMM_MAINCMD_DISPLAY:
						HandleDisplay();
						break;
					default:
						break;
				}
				
			}
		}
	}
	
	u16Length = GetUsartCurrentLength(USART1_TYPE);
	if(u16Length == 15)
	{
		g_TestRfidRev = (++g_TestRfidRev) % 2;
		if(g_TestRfidRev == 0)
		{
			LcdBackLightOn();
		}
		else
		{
			LcdBackLightOff();
		}
		ClearUsartCurrentLength(USART1_TYPE);
        

    u32Tick = GetSynCount();
    *(g_pUsart1_rx_buf + 1) = (u32Tick/1000000000)+'0' ;
    *(g_pUsart1_rx_buf + 2) = ((u32Tick/100000000)%10)+'0' ;
    *(g_pUsart1_rx_buf + 3) = ((u32Tick/10000000)%10)+'0' ;
    *(g_pUsart1_rx_buf + 4) = ((u32Tick/1000000)%10)+'0' ;
    *(g_pUsart1_rx_buf + 5) = ((u32Tick/100000)%10)+'0' ;
    *(g_pUsart1_rx_buf + 6) = ((u32Tick/10000)%10)+'0' ;
    *(g_pUsart1_rx_buf + 7) = ((u32Tick/1000)%10)+'0' ;
    *(g_pUsart1_rx_buf + 8) = ((u32Tick/100)%10)+'0' ;
    *(g_pUsart1_rx_buf + 9) = ((u32Tick/10)%10)+'0' ;
    *(g_pUsart1_rx_buf + 10) = (u32Tick%10)+'0' ;
    *(g_pUsart1_rx_buf + 15) = '\r' ;
    *(g_pUsart1_rx_buf + 16) = '\n' ;
     u16Length = 17;   
	USART2_Send(g_pUsart1_rx_buf, &u16Length);
		
	}
}
