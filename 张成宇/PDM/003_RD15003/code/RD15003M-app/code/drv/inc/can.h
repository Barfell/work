#ifndef __CAN_H
#define __CAN_H	 
#include "kernal.h"

enum
{
	CAN_NO_DATA = 0,
};
	
//CAN1����RX0�ж�ʹ��
#define CAN1_RX0_INT_ENABLE	0		//0,��ʹ��;1,ʹ��.								    
										 							 				    
U8 CAN1_Mode_Init(U8 tsjw,U8 tbs2,U8 tbs1,u16 brp,U8 mode);//CAN��ʼ��
 
BOOL CanSendMsg(U8 *pMsg, U8 u8len);						//��������

U8 CanReceiveMsg(U8 *pBuf);							//��������

#endif

















