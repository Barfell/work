#ifndef _COMM_H_
#define _COMM_H_

#include "usart.h"

enum
{
	COMM_MAINCMD_DISPLAY = 0X05,
	COMM_MAINCMD_KEY = 0X06,//按键指令
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
	KEY_INVALID = 0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
};

U8 GetKeyNumber(VOID);
VOID SetKeyNumber(U8 u8Type);

VOID CommInit(VOID);
VOID ReceiveCommData(VOID);
VOID SendCommData(U8 u8Type);
VOID DisplayPercentage(U8 u8first, U8 u8Second);
VOID DisplayInstruction(U8 u8first, U8 u8Second);
VOID DisplayString(U8 x, U8 y, U8 *pBuf);
VOID DisplayClear(U8 x0, U8 y0, U8 x1, U8 y1, BOOL bType);

#endif

