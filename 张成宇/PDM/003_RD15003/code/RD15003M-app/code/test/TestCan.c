#include "can.h"
#include "usart.h"
enum
{
	CAN_NORMAL_MODE = 0,
	CAN_LOOP_MODE
};

VOID TestCanProc(VOID)
{
	U8 u8Ret;
	U8 szBuf[32] = {0};
	U8 u8Length;
	U8 u8mode;
	U32 u32Tick;
	
	
//	u8mode = CAN_LOOP_MODE;//CAN初始化环回模式,波特率500Kbps 
		
	u8mode = CAN_Mode_Normal;//CAN普通模式初始化,普通模式,波特率500Kbps

	CAN1_Mode_Init(CAN_SJW_1tq, CAN_BS2_6tq, CAN_BS1_7tq, 6, u8mode);		

	u32Tick = GetTickCount();
	while(1)
	{
		if((GetTickCount() - u32Tick) > 1000)
		{
			u32Tick = GetTickCount();
			
			memset(szBuf, 0x55, 8);

			u8Length = 8;

			u8Ret = CanSendMsg(szBuf, u8Length);//发送
			
			if(u8Ret == FALSE)
			{
				printf("Send fail\r\n");
			}
			else
			{
				printf("Send ok\r\n");
			}
		}
		
		u8Ret = CanReceiveMsg(szBuf);
		
		if(u8Ret != CAN_NO_DATA)//接收到有数据
		{
			
			USART1_Send(szBuf, (U16 *)&u8Ret);
		
		}
		
	}
}


