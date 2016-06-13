#ifndef __UARTBOOT_H__
#define __UARTBOOT_H__
#include "kernel.h"   

enum
{
	SB_NULL = 0,
    SB_FORCE_BOOT,
    SB_WRITE,
    SB_READ,
    SB_ENABLE,
    SB_HANDSHAKE,
    SB_HANDSHAKE_Ex,
};

U8 ParseCmd(U8 *pBuf, U16 u16Cnt);
						   
#endif

















