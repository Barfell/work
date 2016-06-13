#ifndef _COMM_H_
#define _COMM_H_

#include "usart.h"

enum
{
	COMM_MAINCMD_STATE = 0X07,//状态
};


enum
{
	COMM_STATE = 1,

};

#define COMM_HEADER		0XFE		//1、头
#define COMM_DIRECTION	0X01		//2、主机
#define COMM_SEQUENTIAL	0XFF		//7、包序号

#define COMM_END1		0XEF		//尾1
#define COMM_END2		0X0D		//尾2

enum
{
	COMM_SUBCMD_INVALID = 0,
};


VOID CommInit(VOID);
VOID ReceiveCommData(VOID);
VOID SendCommData(U8 u8Type);

#endif

