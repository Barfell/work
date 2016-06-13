#include "flash.h"

__asm void _GoToSys(void)
{
	LDR R0, =0x08006004//#0x08006004
	LDR PC, [R0]
	
} 
VOID FlashInit(U32 Page_Address)
{
	FLASH_Status FLASHStatus = FLASH_COMPLETE;
	FLASH_Unlock();///Flash解锁
	while(FLASHStatus !=FLASH_ErasePage(Page_Address))
	{
		DelayMs(2);
	}        
	FLASH_Lock();
}

/**********************************************************************************
* Precedure:	WriteOnePage
* Function:		向片内Flash写入一页信息函数
* Parameter:
				u32 uWriteAddr,写入的起始地址
				u8 *pucWriteData,写入的数据
* Result:		FLASH_error,
				写入Flash的结果信息
				RES_OK = 0,	    0: Successful 
		                                        ERA_ERROR,	     erase  error
		                                        WRI_ERROR,	     2: Write error
		                                        LENG_ERROR,    //数据长度错误
		                                        CHECK_ERROR,   //校验和错误
		                                         ERR_FLASH_ADDR,
		                                         ERR_LENGTH,

* Description:	该函数用于写入分区表配置信息
***********************************************************************************
* LOG	 DATE	 	AUTHOR		   	ACTION
***********************************************************************************
* 2015-07-03		syan  			Create this procedure
***********************************************************************************/
FLASH_error WriteOnePage(u32 uWriteAddr,u8 *pucWriteData)
{

	u32 uFlashAddr=0x0;
	u32 uWriteTimes=0;
	u32 *pData=NULL;
	FLASH_error FLASH_STATUS=RES_OK;
	FLASH_Status FLASHStatus = FLASH_COMPLETE;
	///一页写入次数
	uWriteTimes=STM_PAGE_SIZE/4;
	
	uFlashAddr=uWriteAddr;
	pData=(u32*)pucWriteData;

	while(FLASHStatus ==FLASH_ErasePage(uFlashAddr))
	{
		///循环写入一页的数据
		while(uWriteTimes>0)
		{           
		    FLASH_ProgramWord(uFlashAddr,*pData);
			if (*(u32*)uFlashAddr != *pData)
			{
				///写入Flash出错
				FLASH_STATUS=WRI_ERROR;
				return FLASH_STATUS ;
			}
			uFlashAddr += 4;
			pData++;
			uWriteTimes--;
		} 
		
		FLASH_STATUS=RES_OK;
		break;///跳出循环,写入成功
	}
	return FLASH_STATUS;
}

/**********************************************************************************
* Precedure:	FlashReadSTM32
* Function:		读取STM32片内Flash数据的函数
* Parameter:
				u32 uReadAddr,读取的起始地址
				u32 uReadLen,读取的长度信息
				u8 *pucDataBuffer,将读取的信息装入的数组指针
* Result:		无
* Description:	该函数用于读取STM32片内Flash上的固件信息
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
* Function:		写入Flash函数
* Parameter:
				u32 uWriteAddr,写入的起始地址
				u32 uDataLen,写入的长度
				u8 *pucWriteData,写入的数据
* Result:		      FLASH_error,
				写入Flash的结果信息
				RES_OK = 0,	    0: Successful 
		                                        ERA_ERROR,	     erase  error
		                                        WRI_ERROR,	     2: Write error
		                                        LENG_ERROR,    //数据长度错误
		                                        CHECK_ERROR,   //校验和错误
		                                        ERR_FLASH_ADDR,
		                                         ERR_LENGTH,

* Description:	该函数用于写入分区表配置信息
***********************************************************************************
* LOG	 DATE	 	AUTHOR		   	ACTION
***********************************************************************************
* 2015-07-03		syan  			Create this procedure
***********************************************************************************/

FLASH_error FlashWriteSTM32(u32 uWriteAddr,u16 uDataLen,u8 *pucWriteData)
{
	u32 uFlashAddr=0x0;
	u32 uStartAddr=0x0;
	u16 uWriteLen=0x0;
	u8 ucDataBuffer[STM_PAGE_SIZE];
	memset(ucDataBuffer, 0xff, STM_PAGE_SIZE);	
	u8 *pData=NULL;
	u8 *pucDataBuffer=NULL;
	FLASH_error FLASH_STATUS=RES_OK;
	uFlashAddr =uStartAddr= uWriteAddr;

	pData=pucWriteData;
	pucDataBuffer=ucDataBuffer;
	

	///写入的地址为奇数,出错
	if((uFlashAddr%2)!=0)
	{
		FLASH_STATUS=ERR_FLASH_ADDR;
		return FLASH_STATUS;
	}
	else
	{	
		FLASH_Unlock();
		///判断写入的数据是否需要写两页
		if(((uFlashAddr%STM_PAGE_SIZE)+ uDataLen)>STM_PAGE_SIZE)
		{          
			uStartAddr=uFlashAddr-uFlashAddr%STM_PAGE_SIZE;
			///将一整页读到内存中
			FlashReadSTM32(uStartAddr,STM_PAGE_SIZE,ucDataBuffer);
			///修改内存中的数据
			uWriteLen=STM_PAGE_SIZE-(uFlashAddr%STM_PAGE_SIZE);

			pucDataBuffer=pucDataBuffer+(uFlashAddr%STM_PAGE_SIZE);

			memcpy(pucDataBuffer,pData,uWriteLen);
			///写入一页的信息
			FLASH_STATUS=WriteOnePage(uStartAddr,ucDataBuffer);
	        if (FLASH_STATUS != RES_OK)
			{
				return FLASH_STATUS;
			}
			pData=pData+uWriteLen;

			pucDataBuffer=ucDataBuffer;
			///将第二页内容读到内存中
			uStartAddr=uStartAddr+STM_PAGE_SIZE;
			FlashReadSTM32(uStartAddr,STM_PAGE_SIZE,ucDataBuffer);
			///修改内存中数据
			memcpy(pucDataBuffer,pData,uDataLen-uWriteLen);
			///写入一页的信息
			FLASH_STATUS=WriteOnePage(uStartAddr,ucDataBuffer);
			if (FLASH_STATUS != RES_OK)
			{
				return FLASH_STATUS;
			}
		}
		else
		{           
			FlashReadSTM32(uStartAddr,STM_PAGE_SIZE,ucDataBuffer);

			pucDataBuffer=pucDataBuffer+(uFlashAddr%STM_PAGE_SIZE);
			///修改内存中数据
			
			memcpy(pucDataBuffer,pData,uDataLen);
			
			///写入一页的信息
			FLASH_STATUS=WriteOnePage(uStartAddr,ucDataBuffer);
			
			if (FLASH_STATUS != RES_OK)
	                        {
			   return FLASH_STATUS;
	                        }
		}
		///写入成功
		FLASH_Lock();
	}
	
	return FLASH_STATUS;
}





