#include "board.h"
EXTERN USBH_HOST  USB_Host;
EXTERN USB_OTG_CORE_HANDLE  USB_OTG_Core;

EXTERN VOID OTG_FS_IRQHandler(VOID);
EXTERN BOOL g_bUsbState;
EXTERN BOOL g_bUsbDebug;
VOID TestUsbhost(VOID)
{
    g_bUsbDebug = TRUE;     //使能调试输出			
 	exfuns_init();
  	f_mount(fs[1],"1:",1); 	
		    	 
	printf("Test USB U pan\r\n");					    	 
	printf("USB is connecting...\r\n");		
  
	 		
  	USBH_Init(&USB_OTG_Core,USB_OTG_FS_CORE_ID,&USB_Host,&USBH_MSC_cb,&USR_Callbacks); 

	while(1)
	{	
		
		USBH_Process(&USB_OTG_Core, &USB_Host);
	}		
}
