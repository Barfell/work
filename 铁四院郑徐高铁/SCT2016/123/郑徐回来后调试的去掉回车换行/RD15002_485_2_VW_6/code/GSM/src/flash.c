#include "flash.h"

/*
//boot
*FLASH_Sector_0     0x0800 0000 ~ 0x0800 3fff   16KB
*FLASH_Sector_1		0x0800 4000 ~ 0x0800 7fff   16KB
*FLASH_Sector_2     0x0800 8000 ~ 0x0800 bfff   16KB
*FLASH_Sector_3		0x0800 c000 ~ 0x0800 ffff   16KB
*FLASH_Sector_4		0x0801 0000 ~ 0x0801 ffff   64KB
//app
*FLASH_Sector_5		0x0802 0000 ~ 0x0803 ffff   128KB
*FLASH_Sector_6		0x0804 0000 ~ 0x0805 ffff   128KB
*FLASH_Sector_7		0x0806 0000 ~ 0x0807 ffff   128KB
*FLASH_Sector_8		0x0808 0000 ~ 0x0809 ffff   128KB
*FLASH_Sector_9		0x080a 0000 ~ 0x080b ffff   128KB
*FLASH_Sector_10	0x080c 0000 ~ 0x080d ffff   128KB
*FLASH_Sector_11	0x080e 0000 ~ 0x080f ffff   128KB
*f407---1MB
*/

//STATIC U32 g_u32PacketDataddress = STM32_FLASH_APP_ADDR;         ///��ǰ���µ����ݰ���ַ


VOID FlashInit(VOID)
{
	FLASH_Unlock();///Flash����
	while(MCUFlashErase(FLASH_Sector_5) != 1);
	while(MCUFlashErase(FLASH_Sector_6) != 1);
	while(MCUFlashErase(FLASH_Sector_7) != 1);
	while(MCUFlashErase(FLASH_Sector_8) != 1);
	while(MCUFlashErase(FLASH_Sector_9) != 1);
	while(MCUFlashErase(FLASH_Sector_10) != 1);
	while(MCUFlashErase(FLASH_Sector_11) != 1);
	FLASH_Lock();
}
/**********************************************************************************
* Precedure:	WriteOnePage
* Function:		��Ƭ��Flashд��һҳ��Ϣ����
* Parameter:
				u32 uWriteAddr,д�����ʼ��ַ
				u8 *pucWriteData,д�������
* Result:		FLASH_error,
				д��Flash�Ľ����Ϣ
				RES_OK = 0,	    0: Successful 
		                                        ERA_ERROR,	     erase  error
		                                        WRI_ERROR,	     2: Write error
		                                        LENG_ERROR,    //���ݳ��ȴ���
		                                        CHECK_ERROR,   //У��ʹ���
		                                         ERR_FLASH_ADDR,
		                                         ERR_LENGTH,

* Description:	�ú�������д�������������Ϣ
***********************************************************************************
* LOG	 DATE	 	AUTHOR		   	ACTION
***********************************************************************************
* 2015-07-03		syan  			Create this procedure
***********************************************************************************/
FLASH_error WriteOnePage(u32 uWriteAddr,u8 *pucWriteData)
{
//	u32 uFlashAddr=0x0;
//	u32 uWriteTimes=0;
//	u32 *pData=NULL;
	FLASH_error FLASH_STATUS=RES_OK;
//	FLASH_Status FLASHStatus = FLASH_COMPLETE;
//	///һҳд�����
//	uWriteTimes=STM_PAGE_SIZE/4;
//	
//	uFlashAddr = uWriteAddr;
//	pData=(u32*)pucWriteData;

//	while(FLASHStatus == FLASH_EraseSector(uFlashAddr��VoltageRange_3))
//	{
//		///ѭ��д��һҳ������
//		while(uWriteTimes>0)
//		{           
//		    FLASH_ProgramWord(uFlashAddr,*pData);
//			if (*(u32*)uFlashAddr != *pData)
//			{
//				///д��Flash����
//				FLASH_STATUS=WRI_ERROR;
//				return FLASH_STATUS ;
//			}
//			uFlashAddr += 4;
//			pData++;
//			uWriteTimes--;
//		} 
//		
//		FLASH_STATUS=RES_OK;
//		break;///����ѭ��,д��ɹ�
//	}
//    ///������Flash�ɹ��򱣴汾�θ��µ�������ַ   
//    if(FLASH_STATUS==RES_OK)
//	{
//		g_u32PacketDataddress = uFlashAddr;     
//	
//	}
	return FLASH_STATUS;
}

/**********************************************************************************
* Precedure:	FlashReadSTM32
* Function:		��ȡSTM32Ƭ��Flash���ݵĺ���
* Parameter:
				u32 uReadAddr,��ȡ����ʼ��ַ
				u32 uReadLen,��ȡ�ĳ�����Ϣ
				u8 *pucDataBuffer,����ȡ����Ϣװ�������ָ��
* Result:		��
* Description:	�ú������ڶ�ȡSTM32Ƭ��Flash�ϵĹ̼���Ϣ
***********************************************************************************
* LOG	 DATE	 	AUTHOR		   	ACTION
***********************************************************************************
* 2015-07-03		syan  			Create this procedure
***********************************************************************************/
void FlashReadSTM32(u32 uReadAddr,u16 uReadLen,u8 *pucDataBuffer)
{
//    u8* pucReadAddr=NULL;
//    pucReadAddr = (u8*)(uReadAddr);
//	memcpy(pucDataBuffer,pucReadAddr,uReadLen);
}
/**********************************************************************************
* Precedure:	FlashWriteSTM32
* Function:		д��Flash����
* Parameter:
				u32 uWriteAddr,д�����ʼ��ַ
				u32 uDataLen,д��ĳ���
				u8 *pucWriteData,д�������
* Result:		      FLASH_error,
				д��Flash�Ľ����Ϣ
				RES_OK = 0,	    0: Successful 
		                                        ERA_ERROR,	     erase  error
		                                        WRI_ERROR,	     2: Write error
		                                        LENG_ERROR,    //���ݳ��ȴ���
		                                        CHECK_ERROR,   //У��ʹ���
		                                        ERR_FLASH_ADDR,
		                                         ERR_LENGTH,

* Description:	�ú�������д�������������Ϣ
***********************************************************************************
* LOG	 DATE	 	AUTHOR		   	ACTION
***********************************************************************************
* 2015-07-03		syan  			Create this procedure
***********************************************************************************/

FLASH_error FlashWriteSTM32(u32 uWriteAddr,u16 uDataLen,u8 *pucWriteData)
{
//	u32 uFlashAddr=0x0;
//	u32 uStartAddr=0x0;
//	u16 uWriteLen=0x0;
//	u8 *pData=NULL;
//	u8 *pucDataBuffer=NULL;
//	u8 ucDataBuffer[STM_PAGE_SIZE];
	FLASH_error FLASH_STATUS=RES_OK;
//	
//	memset(ucDataBuffer, 0xff, STM_PAGE_SIZE);	
//	uFlashAddr =uStartAddr= uWriteAddr;
//	pData=pucWriteData;
//	pucDataBuffer=ucDataBuffer;
//	

//	///д��ĵ�ַΪ����,����
//	if((uFlashAddr%2)!=0)
//	{
//		FLASH_STATUS=ERR_FLASH_ADDR;
//		return FLASH_STATUS;
//	}
//	else
//	{	
//		FLASH_Unlock();
//		///�ж�д��������Ƿ���Ҫд��ҳ
//		if(((uFlashAddr%STM_PAGE_SIZE)+ uDataLen)>STM_PAGE_SIZE)
//		{          
//			uStartAddr=uFlashAddr-uFlashAddr%STM_PAGE_SIZE;
//			///��һ��ҳ�����ڴ���
//			FlashReadSTM32(uStartAddr,STM_PAGE_SIZE,ucDataBuffer);
//			///�޸��ڴ��е�����
//			uWriteLen=STM_PAGE_SIZE-(uFlashAddr%STM_PAGE_SIZE);

//			pucDataBuffer=pucDataBuffer+(uFlashAddr%STM_PAGE_SIZE);

//			memcpy(pucDataBuffer,pData,uWriteLen);
//			///д��һҳ����Ϣ
//			FLASH_STATUS=WriteOnePage(uStartAddr,ucDataBuffer);
//	        if (FLASH_STATUS != RES_OK)
//			{
//				return FLASH_STATUS;
//			}
//			pData=pData+uWriteLen;

//			pucDataBuffer=ucDataBuffer;
//			///���ڶ�ҳ���ݶ����ڴ���
//			uStartAddr=uStartAddr+STM_PAGE_SIZE;
//			FlashReadSTM32(uStartAddr,STM_PAGE_SIZE,ucDataBuffer);
//			///�޸��ڴ�������
//			memcpy(pucDataBuffer,pData,uDataLen-uWriteLen);
//			///д��һҳ����Ϣ
//			FLASH_STATUS=WriteOnePage(uStartAddr,ucDataBuffer);
//			if (FLASH_STATUS != RES_OK)
//			{
//				return FLASH_STATUS;
//			}
//		}
//		else
//		{           
//			FlashReadSTM32(uStartAddr,STM_PAGE_SIZE,ucDataBuffer);

//			pucDataBuffer=pucDataBuffer+(uFlashAddr%STM_PAGE_SIZE);
//			///�޸��ڴ�������
//			
//			memcpy(pucDataBuffer,pData,uDataLen);
//			
//			///д��һҳ����Ϣ
//			FLASH_STATUS=WriteOnePage(uStartAddr,ucDataBuffer);
//			
//			if (FLASH_STATUS != RES_OK)
//	                        {
//			   return FLASH_STATUS;
//	                        }
//		}
//		///д��ɹ�
//		FLASH_Lock();
//	}
//	
	return FLASH_STATUS;
}

/**********************************************************************************
* Precedure:      DownSTM32Flash
* Function:	      ��������flash ��Ϣ����
* Parameter:       	u8* pucPacketData���������ع̼���Ϣ�����ݰ�
					u32 uWriteAddr,����д��Flash����ʼ��ַ
					u32 uWriteLen,�������ݰ���,������Ч���ݵĳ���
* Result:
			 FLASH_error,
			 RES_OK = 0,	     0: Successful 
											 ERA_ERROR,	     erase  error
											 WRI_ERROR,	     2: Write error
											 LENG_ERROR,     //���ݳ��ȴ���
											 CHECK_ERROR,   //У��ʹ���
											 ERR_FLASH_ADDR,//��ַ����
											 ERR_LENGTH,       //���ȴ���
		
						  
* Description:	 �ú���������ӦPC������Flash��������Ϣָ��(STM32)
***********************************************************************************
* LOG	 DATE	 	AUTHOR		   	ACTION
***********************************************************************************
* 2015-07-03		syan  			Create this procedure
***********************************************************************************/

FLASH_error DownSTM32Flash(u8* pucPacketData,u16 uDataLen)
{
	FLASH_error FLASH_STATUS=RES_OK;

//	if(g_u32PacketDataddress%2 == 0)///��ַ����Ϊż��,���ֶ���
//	{
//		///����д��Flash����
//		FLASH_STATUS = FlashWriteSTM32(g_u32PacketDataddress, uDataLen, pucPacketData);
//		if(FLASH_STATUS != RES_OK)
//			return FLASH_STATUS;
//	}
//	else
//	{
//		///����д��Flash�ĵ�ַ��
//		FLASH_STATUS = ERR_FLASH_ADDR;
//		return FLASH_STATUS;
//	}
//		
	return FLASH_STATUS;
}




