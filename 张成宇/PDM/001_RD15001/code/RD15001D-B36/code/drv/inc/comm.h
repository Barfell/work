#ifndef __COMM_H
#define __COMM_H

#include "usart.h"
#include "LcdDrv.h" 
#include "key.h"
enum
{
	COMM_MAINCMD_DISPLAY = 0X05,
	COMM_MAINCMD_KEY = 0X06,//按键指令
	COMM_MAINCMD_STATE = 0X07,//状态
};

enum
{
	COMM_SUBCMD_INVALID = 0,
	COMM_SUBCMD_DISPLAY_PERCENTAGE,
	COMM_SUBCMD_DISPLAY_INSTRUCTION,
	COMM_SUBCMD_DISPLAY_STRING,
	COMM_SUBCMD_DISPLAY_CLEAR,
};

enum
{
	LINE_1 = 0,
	LINE_2 = 7,
	LINE_3 = 15,
	LINE_4 = 23,
	LINE_5 = 31,
	LINE_6 = 39,
	LINE_7 = 47,
	LINE_8 = 55,
	LINE_9 = 63,
	LINE_10 = 71,
	LINE_11 = 79,
	LINE_12 = 87,
	
};
enum
{
	COMM_STATE = 1,
	COMM_KEY,
};

#define COMM_HEADER				0XFE		//1、头
#define COMM_DIRECTION			0X10		//2、从机	
#define COMM_SEQUENTIAL			0XFF		//7、包序号

#define COMM_END1				0XEF		//尾1
#define COMM_END2				0X0D		//尾2

enum
{
	DISPLAY_PERCENTAGE = 1,
};


VOID CommInit(VOID);
U8 CalcCheckSum(U8* pSrcData, U16 wDataLen);
VOID ReceiveCommData(VOID);
VOID SendCommData(U8 u8Type);

#endif


