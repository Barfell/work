#include "app_usb.h"

U8 USH_User_App(VOID)
{ 
	u32 total,free;
	U8 res=0;
    if(g_bUsbDebug == TRUE)
    {
        printf("USB connect success!\r\n");	
    }
	res=exf_getfree("1:",&total,&free);
	if(res==0)
	{  
        if(g_bUsbDebug == TRUE)
        {
            printf("FATFS OK!");	
            printf("U Disk Total Size:  %d   MB\r\n", total>>10);	 
            printf("U Disk  Free Size:   %d  MB\r\n", free>>10); 	
        }            
	} 
    if(g_bUsbDebug == TRUE)  
    {        
        printf("USB is connecting...\r\n");	
    }
    
    bUsbPlugin = TRUE;
 
	return res;
} 

VOID StartUSB(VOID)
{			
 	exfuns_init();
    
  	f_mount(fs[1],"1:",1); 	

  	USBH_Init(&USB_OTG_Core,USB_OTG_FS_CORE_ID,&USB_Host,&USBH_MSC_cb,&USR_Callbacks); 
    
}


