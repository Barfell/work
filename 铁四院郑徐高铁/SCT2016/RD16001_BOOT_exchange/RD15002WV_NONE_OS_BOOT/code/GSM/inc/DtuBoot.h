#ifndef _DTUBOOT_H
#define _DTUBOOT_H

#include "kernal.h"

//#define __RD15002_PROTOCOL_		//使用协议时打开这个定义


enum
{
	IP_INTERVIEW,
	DOMAIN_INTERVIEW,
};

enum
{
	STM_FLASH = 0,
	SST25VF0_FLASH,
};

#define DTUTIMEOUT1		20
#define DTUTIMEOUT2		20




VOID WriteFlashFlag(VOID);

STATIC VOID HandleDataPackage(U8 *pBuf, U16 u16Length);

STATIC VOID HandleCmdProc(U8 *pBuf, U16 u16Length);

VOID DtuBoot(VOID);


#endif

