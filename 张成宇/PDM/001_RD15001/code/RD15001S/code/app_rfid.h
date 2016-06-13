#ifndef __APP_RFID_H
#define __APP_RFID_H
#include "system.h"	
#include <string.h>
//P4口与其余口的配置方式一样的， 只不过其不能位操作。
//read
#define  READ_P40 (P4&0x01) 
#define  READ_P41 (P4&0x02)
#define  READ_P42 (P4&0x04)
#define  READ_P43 (P4&0x08) 
#define  READ_P44 (P4&0x10) 
#define  READ_P45 (P4&0x20)
#define  READ_P46 (P4&0x40)
#define  READ_P47 (P4&0x80)
//Werite
#define  WRITE_P40_H (P4|=0x01)
#define  WRITE_P41_H (P4|=0x02)
#define  WRITE_P40_L (P4&=0xfe)
#define  WRITE_P41_L (P4&=0xfd)

#define RFID_RESET()        WRITE_P41_L
#define RFID_UNRESET()      WRITE_P41_H

#define RFID_SHUTDOWN()     WRITE_P40_L
#define RFID_UNSHUTDOWN()   WRITE_P40_H

#define READ_RFID_RESET()	READ_P41

typedef	unsigned char			U8;
typedef U8*						P_U8;
typedef signed char				S8;
typedef S8*						P_S8;
typedef unsigned short			U16;
typedef U16*					P_U16;
typedef signed short			S16;
typedef S16*					P_S16;
typedef unsigned long			U32;
typedef U32*					P_U32;
typedef signed long				S32;
typedef S32*					P_S32;

typedef	U8					BOOL;

typedef char					CHAR;
typedef unsigned char           UCHAR;
typedef CHAR *					LPSTR;
typedef const CHAR *			LPCSTR;
typedef CHAR *                  PCHAR;
typedef	void					VOID;
#define STATIC  				static 

#if	defined(TRUE)
#undef	TRUE
#endif
#define	TRUE					(1 == 1)

#if	defined(FALSE)
#undef	FALSE
#endif
#define	FALSE					(1 == 0)

#if	defined(NULL)
#undef	NULL
#endif
#define	NULL					(0)                 

#define RFIDDATACOUNT   50


// 简单运算定义
#define MAKEBYTE(l, h)			((unsigned char)(((unsigned char)(l) & 0x0F) | ((((unsigned char)(h)) << 4) & 0xF0)))
#define MAKEWORD(l, h)			((unsigned short)((((unsigned char)(l))&0x00FF) | ((((unsigned short)((unsigned char)(h))) << 8)&0xFF00)))
#define MAKELONG(l, h)			((U32)(((U16)(l)) | ((U32)((U16)(h))) << 16))
#define LOWORD(l)				((unsigned short)((l) & 0xFFFF))
#define HIWORD(l)				((unsigned short)(((unsigned long)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)				((unsigned char)((w) & 0xFF))
#define HIBYTE(w)				((unsigned char)(((unsigned short)(w) >> 8) & 0xFF))
#define HIHALFBYTE(b)			((unsigned char)(((b) >> 4) & 0x0F))
#define LOHALFBYTE(b)			((unsigned char)((b) & 0x0F))
#define max(a, b)				(((a) > (b)) ? (a) : (b))
#define min(a, b)				(((a) < (b)) ? (a) : (b))


enum
{
    BOOTLOADER_RUNNING,
    APPLICTATION_RUNNING
};

enum
{
    GETCURRENTPROGRAM = 0,
    BOOTFIRMWARE,
    SETFREQUENCYCHANNEL,
    SETPROTOCOL,
    SETANTENNA,
    CLEARBUFFER,
    SEARCHTAG,
    GETTAGDATA,   
    GETTAGDATAId,
    PRIMECONTINUEREADING,
    CONTINUEREADING,
    ENHANCEDISTANCE,
    ENHANCESPEED1,
    ENHANCESPEED2,
    ENHANCESPEED3,
    ENHANCESPEED4,
    ENHANCESPEED5,
    ENHANCESPEED6,
    CONTINUEREADINGEX,
    STOPREADING,
	ONCEMODE,
	ERR_ADD_FAIL,
    
};

enum
{
    RFID_TAG1 = 0,
    RFID_TAG2,
    RFID_TAG3,
    RFID_TAG4,
    RFID_TAG5,
    RFID_TAG6,
    RFID_TAG7,
    RFID_TAG8,
    RFID_TAG9,
    RFID_TAG10,
    RFID_TAG11,
    RFID_TAG12,
    RFID_TAG13
};

typedef struct  _tagRfid
{
    U8 u8CmdType;
    U8 szCmdSenddata[RFIDDATACOUNT];
    U8 szReceivedata[RFIDDATACOUNT];
    U8 u8SendCount;
    U8 u8ReceiveCount;
    U8 u8RfidState;
    U8 u8Tag;
       
} CRfidVar, *PCRfidVar; 

enum
{
	ERR_RFID_STEP_1 = 1,
	ERR_RFID_STEP_2,
	ERR_RFID_STEP_3,
	ERR_RFID_STEP_4,
	ERR_RFID_STEP_5,
	ERR_RFID_STEP_6,
	ERR_RFID_STEP_7,
	ERR_RFID_STEP_8,
	ERR_RFID_STOP,
	ERR_TEST_MALLOC_FAIL,
};


extern CRfidVar g_cRfidVar;
extern U8 g_u8TagOffset;

VOID GetCmdProc(U8 cCmdType, U8 *pData, U8 *pCount);
BOOL CompareTag(U8 *pBuf);
BOOL HandleTag(U8 *pBuf);
BOOL SendAndWaitRfidDataProc(U8 u8CmdType);
BOOL SendAndWaitRfidDataProcEnhance(U16 u16Data);
U16 CalculateRfidCrc(U8 *u8Buf, U16 len);
VOID RfidInitProc(VOID);

#endif 















