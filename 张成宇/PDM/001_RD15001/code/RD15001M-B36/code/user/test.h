#ifndef __TEST_H
#define __TEST_H

#include "kernal.h"

VOID TestImu(VOID);
VOID TestGps(VOID);
VOID TestUsart1(VOID);
VOID TestUsart2(VOID);
VOID TestUsart3(VOID);
VOID TestUsart4(VOID);
VOID TestUsartSend(VOID);
VOID TestUsart(VOID);
VOID TestBeepProc(VOID);

VOID TestSynProc(VOID);
VOID TestCommProc(VOID);
VOID TestCommGuiProc(VOID);
VOID TestCommKeyProc(VOID);
VOID TestUsbhost(VOID);
VOID TestSdProc(VOID);
VOID TestCanProc(VOID);

VOID TestNandflash(VOID);

VOID TestInsGpsOtherNandStorage(VOID);//INS+GPS+¿Ô≥ÃπÏæ‡”√nand+fram

#endif

