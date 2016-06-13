#ifndef __APP_USB_H
#define __APP_USB_H	
#include "kernal.h"
#include "usb_bsp.h"
#include "usbh_usr.h"
#include "exfuns.h"

EXTERN USBH_HOST  USB_Host;
EXTERN USB_OTG_CORE_HANDLE  USB_OTG_Core;
EXTERN BOOL g_bUsbDebug;
EXTERN BOOL bUsbPlugin;

VOID StartUSB(VOID);

#endif 















