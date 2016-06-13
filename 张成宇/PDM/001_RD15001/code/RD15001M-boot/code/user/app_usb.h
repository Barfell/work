#ifndef __APP_USB_H
#define __APP_USB_H	
#include "board.h"

EXTERN USBH_HOST  USB_Host;
EXTERN USB_OTG_CORE_HANDLE  USB_OTG_Core;
EXTERN BOOL g_bUsbDebug;
EXTERN BOOL bUsbPlugin;

VOID StartUSB(VOID);

#endif 















