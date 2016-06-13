#ifndef __SYN_H
#define __SYN_H	 
#include "kernal.h"

#include "device.h"
//app
#include "app_usb.h"

VOID EtrSynInit(VOID);

U32 GetEtrSynCount(VOID);

VOID SetEtrSynCount(U32 u32Value);

VOID CpldOn(VOID);

VOID CpldOff(VOID);


#endif

















