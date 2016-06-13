#ifndef __SYN_H
#define __SYN_H	 
#include "kernal.h"

VOID SynInit(VOID);


U32 GetSynCount(VOID);

VOID SendMileGaugeDataProc(VOID);

VOID SendMileDataProc(VOID);

VOID SendGaugeDataProc(VOID);

VOID HandleSynDataProc(VOID);

VOID DisplayMileDataProc(VOID); 

#endif

















