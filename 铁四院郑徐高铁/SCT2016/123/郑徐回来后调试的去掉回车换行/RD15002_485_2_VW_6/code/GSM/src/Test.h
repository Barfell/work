#ifndef __TEST_H
#define __TEST_H	 
#include "kernal.h"

void SendAndWait485DataProc(U8 *pBuf, U16 u16Length, U8 *pData);
void LowPowerEntry(void);
VOID TestDtu(VOID);
VOID ReadLockId(U32 *pData);
#endif

















