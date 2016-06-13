#include "usbh_usr.h" 
#include "kernal.h"
#include "ff.h" 
 

static u8 AppState;
USB_OTG_CORE_HANDLE  USB_OTG_Core;
BOOL g_bUsbDebug = FALSE;

BOOL bUsbPlugin = FALSE;

//USB OTG �жϷ�����
//��������USB�ж�
void OTG_FS_IRQHandler(void)
{
  	USBH_OTG_ISR_Handler(&USB_OTG_Core);
} 
//USB HOST �û��ص�����.
USBH_Usr_cb_TypeDef USR_Callbacks=
{
	USBH_USR_Init,
	USBH_USR_DeInit,
	USBH_USR_DeviceAttached,
	USBH_USR_ResetDevice,
	USBH_USR_DeviceDisconnected,
	USBH_USR_OverCurrentDetected,
	USBH_USR_DeviceSpeedDetected,
	USBH_USR_Device_DescAvailable,
	USBH_USR_DeviceAddressAssigned,
	USBH_USR_Configuration_DescAvailable,
	USBH_USR_Manufacturer_String,
	USBH_USR_Product_String,
	USBH_USR_SerialNum_String,
	USBH_USR_EnumerationDone,
	USBH_USR_UserInput,
	USBH_USR_MSC_Application,
	USBH_USR_DeviceNotSupported,
	USBH_USR_UnrecoveredError
};
/////////////////////////////////////////////////////////////////////////////////
//����Ϊ���ص�����ʵ��.

//USB HOST ��ʼ�� 
void USBH_USR_Init(void)
{
    if(g_bUsbDebug == TRUE)
    {
        printf("USB OTG HS MSC Host\r\n");
        printf("> USB Host library started.\r\n");
        printf("  USB Host Library v2.1.0\r\n\r\n");
    }
	
}
//��⵽U�̲���
void USBH_USR_DeviceAttached(void)//U�̲���
{
    if(g_bUsbDebug == TRUE)
    {
        printf("��⵽USB�豸����!\r\n");
    }
}
//��⵽U�̰γ�
void USBH_USR_DeviceDisconnected (void)//U���Ƴ�
{
    if(g_bUsbDebug == TRUE)
    {
        printf("USB�豸�γ�!\r\n");
    }
    
    bUsbPlugin = FALSE;
}  
//��λ�ӻ�
void USBH_USR_ResetDevice(void)
{
    if(g_bUsbDebug == TRUE)
    {
        printf("��λ�豸...\r\n");
    }
}
//��⵽�ӻ��ٶ�
//DeviceSpeed:�ӻ��ٶ�(0,1,2 / ����)
void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed)
{
	if(DeviceSpeed==HPRT0_PRTSPD_HIGH_SPEED)
	{
        if(g_bUsbDebug == TRUE)
        {
            printf("����(HS)USB�豸!\r\n");
        }
 	}  
	else if(DeviceSpeed==HPRT0_PRTSPD_FULL_SPEED)
	{
        if(g_bUsbDebug == TRUE)
        {
            printf("ȫ��(FS)USB�豸!\r\n"); 
        }
	}
	else if(DeviceSpeed==HPRT0_PRTSPD_LOW_SPEED)
	{
        if(g_bUsbDebug == TRUE)
        {
            printf("����(LS)USB�豸!\r\n");  
        }
	}
	else
	{
        if(g_bUsbDebug == TRUE)
        {
            printf("�豸����!\r\n"); 
        }            
	}
}
//��⵽�ӻ���������
//DeviceDesc:�豸������ָ��
void USBH_USR_Device_DescAvailable(void *DeviceDesc)
{ 
	USBH_DevDesc_TypeDef *hs;
	hs=DeviceDesc;  
    if(g_bUsbDebug == TRUE)   
    {        
        printf("VID: %04Xh\r\n" , (uint32_t)(*hs).idVendor); 
        printf("PID: %04Xh\r\n" , (uint32_t)(*hs).idProduct); 
    }
}
//�ӻ���ַ����ɹ�
void USBH_USR_DeviceAddressAssigned(void)
{
    if(g_bUsbDebug == TRUE)
    {
        printf("�ӻ���ַ����ɹ�!\r\n");  
    }        
}
//��������������Ч
void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
                                          USBH_InterfaceDesc_TypeDef *itfDesc,
                                          USBH_EpDesc_TypeDef *epDesc)
{
	USBH_InterfaceDesc_TypeDef *id; 
	id = itfDesc;   
	if((*id).bInterfaceClass==0x08)
	{
        if(g_bUsbDebug == TRUE)
        {
            printf("���ƶ��洢���豸!\r\n"); 
        }
	}
    else if((*id).bInterfaceClass==0x03)
	{
        if(g_bUsbDebug == TRUE)
        {
            printf("HID �豸!\r\n"); 
        }
	}    
}
//��ȡ���豸Manufacturer String
void USBH_USR_Manufacturer_String(void *ManufacturerString)
{
    if(g_bUsbDebug == TRUE)
    {
        printf("Manufacturer: %s\r\n",(char *)ManufacturerString);
    }
}
//��ȡ���豸Product String 
void USBH_USR_Product_String(void *ProductString)
{
    if(g_bUsbDebug == TRUE)
    {
        printf("Product: %s\r\n",(char *)ProductString);  
    }
}
//��ȡ���豸SerialNum String 
void USBH_USR_SerialNum_String(void *SerialNumString)
{
    if(g_bUsbDebug == TRUE)
    {
        printf("Serial Number: %s\r\n",(char *)SerialNumString);
    }        
} 
//�豸USBö�����
void USBH_USR_EnumerationDone(void)
{ 
    if(g_bUsbDebug == TRUE)
    {
        printf("�豸ö�����!\r\n\r\n");  
    }        
} 
//�޷�ʶ���USB�豸
void USBH_USR_DeviceNotSupported(void)
{
    if(g_bUsbDebug == TRUE)
    {
        printf("�޷�ʶ���USB�豸!\r\n\r\n");   
    }        
}  
//�ȴ��û����밴��,ִ����һ������
USBH_USR_Status USBH_USR_UserInput(void)
{ 
    if(g_bUsbDebug == TRUE)
    {
        printf("�����û�ȷ�ϲ���!\r\n");
    }
	return USBH_USR_RESP_OK;
} 
//USB�ӿڵ�������
void USBH_USR_OverCurrentDetected (void)
{
    if(g_bUsbDebug == TRUE)
    {
        printf("�˿ڵ�������!!!\r\n");
    }
} 

extern u8 USH_User_App(void);		//�û�����������
//USB HOST MSC���û�Ӧ�ó���
int USBH_USR_MSC_Application(void)
{
	u8 res=0;
  	switch(AppState)
  	{
    	case USH_USR_FS_INIT://��ʼ���ļ�ϵͳ 
            if(g_bUsbDebug == TRUE)
            {
                printf("��ʼִ���û�����!!!\r\n");
            }
			AppState=USH_USR_FS_TEST;
      		break;
    	case USH_USR_FS_TEST:	//ִ��USB OTG ����������
			res=USH_User_App(); //�û�������
     		res=0;
			if(res)AppState=USH_USR_FS_INIT;
      		break;
    	default:break;
  	} 
	return res;
}
//�û�Ҫ�����³�ʼ���豸
void USBH_USR_DeInit(void)
{
  	AppState=USH_USR_FS_INIT;
}
//�޷��ָ��Ĵ���!!  
void USBH_USR_UnrecoveredError (void)
{
    if(g_bUsbDebug == TRUE)
    {
        printf("�޷��ָ��Ĵ���!!!\r\n\r\n");	
    }
}
////////////////////////////////////////////////////////////////////////////////////////
//�û����庯��,ʵ��fatfs diskio�Ľӿں��� 
USBH_HOST              USB_Host;

//��ȡU��״̬
//����ֵ:0,U��δ����
//      1,����
u8 USBH_UDISK_Status(void)
{
	return HCD_IsDeviceConnected(&USB_OTG_Core);//����U��״̬
}

//��U��
//buf:�����ݻ�����
//sector:������ַ
//cnt:��������	
//����ֵ:����״̬;0,����;����,�������;		 
u8 USBH_UDISK_Read(u8* buf,u32 sector,u32 cnt)
{
	u8 res=1;
	if(HCD_IsDeviceConnected(&USB_OTG_Core)&&AppState==USH_USR_FS_TEST)//���ӻ�����,����APP����״̬
	{  		    
		do
		{
			res=USBH_MSC_Read10(&USB_OTG_Core,buf,sector,512*cnt);
			USBH_MSC_HandleBOTXfer(&USB_OTG_Core ,&USB_Host);		      
			if(!HCD_IsDeviceConnected(&USB_OTG_Core))
			{
				res=1;//��д����
				break;
			};   
		}while(res==USBH_MSC_BUSY);
	}else res=1;		  
	if(res==USBH_MSC_OK)res=0;	
	return res;
}

//дU��
//buf:д���ݻ�����
//sector:������ַ
//cnt:��������	
//����ֵ:����״̬;0,����;����,�������;		 
u8 USBH_UDISK_Write(u8* buf,u32 sector,u32 cnt)
{
	u8 res=1;
	if(HCD_IsDeviceConnected(&USB_OTG_Core)&&AppState==USH_USR_FS_TEST)//���ӻ�����,����APP����״̬
	{  		    
		do
		{
			res=USBH_MSC_Write10(&USB_OTG_Core,buf,sector,512*cnt); 
			USBH_MSC_HandleBOTXfer(&USB_OTG_Core ,&USB_Host);		      
			if(!HCD_IsDeviceConnected(&USB_OTG_Core))
			{
				res=1;//��д����
				break;
			};   
		}while(res==USBH_MSC_BUSY);
	}else res=1;		  
	if(res==USBH_MSC_OK)res=0;	
	return res;
}












































