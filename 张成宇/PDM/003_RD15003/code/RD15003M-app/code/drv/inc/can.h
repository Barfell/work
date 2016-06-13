#ifndef __CAN_H
#define __CAN_H	 
#include "kernal.h"

enum
{
	CAN_NO_DATA = 0,
};
	
//CAN1接收RX0中断使能
#define CAN1_RX0_INT_ENABLE	0		//0,不使能;1,使能.								    
										 							 				    
U8 CAN1_Mode_Init(U8 tsjw,U8 tbs2,U8 tbs1,u16 brp,U8 mode);//CAN初始化
 
BOOL CanSendMsg(U8 *pMsg, U8 u8len);						//发送数据

U8 CanReceiveMsg(U8 *pBuf);							//接收数据

#endif

















