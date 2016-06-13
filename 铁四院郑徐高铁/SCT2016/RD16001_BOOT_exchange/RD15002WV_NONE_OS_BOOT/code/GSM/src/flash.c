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

STATIC U32 g_u32PacketDataddress = STM32_FLASH_APP_ADDR;         ///��ǰ���µ����ݰ���ַ


VOID FlashInit(VOID)
{
	FLASH_Unlock();///Flash����
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
//	while(MCUFlashErase(FLASH_Sector_5) != 1);
//	while(MCUFlashErase(FLASH_Sector_6) != 1);
//	while(MCUFlashErase(FLASH_Sector_7) != 1);
	while(MCUFlashErase(FLASH_Sector_8) != 1);
	while(MCUFlashErase(FLASH_Sector_9) != 1);
	while(MCUFlashErase(FLASH_Sector_10) != 1);
	while(MCUFlashErase(FLASH_Sector_11) != 1);
	while(MCUFlashErase(FLASH_Sector_3) != 1);
	while(MCUFlashErase(FLASH_Sector_4) != 1);
	
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
    u8* pucReadAddr=NULL;
    pucReadAddr = (u8*)(uReadAddr);
	memcpy(pucDataBuffer,pucReadAddr,uReadLen);
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
	MCUFlashUnlock();
	Flash_w_Length(uWriteAddr,pucWriteData,uDataLen);
	FLASH_Lock();
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

	if(g_u32PacketDataddress%2 == 0)///��ַ����Ϊż��,���ֶ���
	{
		///����д��Flash����
		FLASH_STATUS = FlashWriteSTM32(g_u32PacketDataddress, uDataLen, pucPacketData);
		if(FLASH_STATUS != RES_OK)
			return FLASH_STATUS;
	}
	else
	{
		///����д��Flash�ĵ�ַ��
		FLASH_STATUS = ERR_FLASH_ADDR;
		return FLASH_STATUS;
	}
	return FLASH_STATUS;
}




//��ȡָ����ַ�İ���(16λ����) 
//faddr:����ַ 
//����ֵ:��Ӧ����.
u32 STMFLASH_ReadWord(u32 faddr)
{
	return *(vu32*)faddr; 
}  
//��ȡĳ����ַ���ڵ�flash����
//addr:flash��ַ
//����ֵ:0~11,��addr���ڵ�����
uint16_t STMFLASH_GetFlashSector(u32 addr)
{
	if(addr<ADDR_FLASH_SECTOR_1)return FLASH_Sector_0;
	else if(addr<ADDR_FLASH_SECTOR_2)return FLASH_Sector_1;
	else if(addr<ADDR_FLASH_SECTOR_3)return FLASH_Sector_2;
	else if(addr<ADDR_FLASH_SECTOR_4)return FLASH_Sector_3;
	else if(addr<ADDR_FLASH_SECTOR_5)return FLASH_Sector_4;
	else if(addr<ADDR_FLASH_SECTOR_6)return FLASH_Sector_5;
	else if(addr<ADDR_FLASH_SECTOR_7)return FLASH_Sector_6;
	else if(addr<ADDR_FLASH_SECTOR_8)return FLASH_Sector_7;
	else if(addr<ADDR_FLASH_SECTOR_9)return FLASH_Sector_8;
	else if(addr<ADDR_FLASH_SECTOR_10)return FLASH_Sector_9;
	else if(addr<ADDR_FLASH_SECTOR_11)return FLASH_Sector_10; 
	return FLASH_Sector_11;	
}
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ر�ע��:��ΪSTM32F4������ʵ��̫��,û�취���ر�����������,���Ա�����
//         д��ַ�����0XFF,��ô���Ȳ������������Ҳ�������������.����
//         д��0XFF�ĵ�ַ,�����������������ݶ�ʧ.����д֮ǰȷ��������
//         û����Ҫ����,��������������Ȳ�����,Ȼ����������д. 
//�ú�����OTP����Ҳ��Ч!��������дOTP��!
//OTP�����ַ��Χ:0X1FFF7800~0X1FFF7A0F
//WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ4�ı���!!)
//pBuffer:����ָ��
//NumToWrite:��(32λ)��(����Ҫд���32λ���ݵĸ���.) 
void STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite)	
{ 
  FLASH_Status status = FLASH_COMPLETE;
	u32 addrx=0;
	u32 endaddr=0;	
  if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4)return;	//�Ƿ���ַ
	FLASH_Unlock();									//���� 
  FLASH_DataCacheCmd(DISABLE);//FLASH�����ڼ�,�����ֹ���ݻ���
 		
	addrx=WriteAddr;				//д�����ʼ��ַ
	endaddr=WriteAddr+NumToWrite*4;	//д��Ľ�����ַ
	if(addrx<0X1FFF0000)			//ֻ�����洢��,����Ҫִ�в�������!!
	{
		while(addrx<endaddr)		//ɨ��һ���ϰ�.(�Է�FFFFFFFF�ĵط�,�Ȳ���)
		{
			if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)//�з�0XFFFFFFFF�ĵط�,Ҫ�����������
			{   
				status=FLASH_EraseSector(STMFLASH_GetFlashSector(addrx),VoltageRange_3);//VCC=2.7~3.6V֮��!!
				if(status!=FLASH_COMPLETE)break;	//����������
			}else addrx+=4;
		} 
	}
	if(status==FLASH_COMPLETE)
	{
		while(WriteAddr<endaddr)//д����
		{
			if(FLASH_ProgramWord(WriteAddr,*pBuffer)!=FLASH_COMPLETE)//д������
			{ 
				break;	//д���쳣
			}
			WriteAddr+=4;
			pBuffer++;
		} 
	}
  FLASH_DataCacheCmd(ENABLE);	//FLASH��������,�������ݻ���
	FLASH_Lock();//����
} 

//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToRead:��(4λ)��
void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead)   	
{
	u32 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//��ȡ4���ֽ�.
		ReadAddr+=4;//ƫ��4���ֽ�.	
	}
}

