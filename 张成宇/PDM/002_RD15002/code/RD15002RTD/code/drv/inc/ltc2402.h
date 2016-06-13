#ifndef __LTC2402_H
#define __LTC2402_H	 
#include "kernal.h"

VOID Ltc2402SoftInit(VOID);
U8 LTC2402_TEST_EOC_Start(VOID);
VOID LTC2402_TEST_EOC_End(VOID);
U8 LTC2402_ReadByte(VOID);
#endif


