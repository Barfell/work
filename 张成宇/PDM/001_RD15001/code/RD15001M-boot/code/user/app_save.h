#ifndef __APP_SAVE_H
#define __APP_SAVE_H	
#include "board.h"
enum
{
    GPSDATA = 0,
    INSDATA,
    OTHERDATA,
    RFIDDATA,
};

#define SAVEDATASIZE        8192        //8192=8k

VOID SaveDataInit(VOID);
VOID SaveFram(U8 *pBuf, U16 u16Cnt, U8 u8Type);
VOID SaveNandflash(U8 u8Type);
VOID SaveUsbProc(U8 u8Type);


#endif 















