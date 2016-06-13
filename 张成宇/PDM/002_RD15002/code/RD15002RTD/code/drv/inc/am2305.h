#ifndef __AM2305_H
#define __AM2305_H	 
#include "kernal.h"

VOID AM2305_Init(VOID);
U8 AM2305_Run(VOID);
VOID GetAm2305Data(U8 *pBuf);

#endif
