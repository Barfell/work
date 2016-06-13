#ifndef _COMM_H_
#define _COMM_H_

#include "usart.h"

enum
{
	COMM_MAINCMD_STATE = 0X07,//״̬
};


enum
{
	COMM_STATE = 1,

};

#define COMM_HEADER		0XFE		//1��ͷ
#define COMM_DIRECTION	0X01		//2������
#define COMM_SEQUENTIAL	0XFF		//7�������

#define COMM_END1		0XEF		//β1
#define COMM_END2		0X0D		//β2

enum
{
	COMM_SUBCMD_INVALID = 0,
};


VOID CommInit(VOID);
VOID ReceiveCommData(VOID);
VOID SendCommData(U8 u8Type);

#endif

