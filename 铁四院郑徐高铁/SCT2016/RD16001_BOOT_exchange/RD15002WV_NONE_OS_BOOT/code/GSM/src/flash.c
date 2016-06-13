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

STATIC U32 g_u32PacketDataddress = STM32_FLASH_APP_ADDR;         ///当前更新的数据包地址


VOID FlashInit(VOID)
{
	FLASH_Unlock();///Flash解锁
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
	MCUFlashUnlock();
	Flash_w_Length(uWriteAddr,pucWriteData,uDataLen);
	FLASH_Lock();
}

/**********************************************************************************
* Precedure:      DownSTM32Flash
* Function:	      启动下载flash 信息函数
* Parameter:       	u8* pucPacketData，启动下载固件信息的数据包
					u32 uWriteAddr,本次写入Flash的起始地址
					u32 uWriteLen,本次数据包中,包含有效数据的长度
* Result:
			 FLASH_error,
			 RES_OK = 0,	     0: Successful 
											 ERA_ERROR,	     erase  error
											 WRI_ERROR,	     2: Write error
											 LENG_ERROR,     //数据长度错误
											 CHECK_ERROR,   //校验和错误
											 ERR_FLASH_ADDR,//地址错误
											 ERR_LENGTH,       //长度错误
		
						  
* Description:	 该函数用于响应PC端下载Flash分区表信息指令(STM32)
***********************************************************************************
* LOG	 DATE	 	AUTHOR		   	ACTION
***********************************************************************************
* 2015-07-03		syan  			Create this procedure
***********************************************************************************/

FLASH_error DownSTM32Flash(u8* pucPacketData,u16 uDataLen)
{
	FLASH_error FLASH_STATUS=RES_OK;

	if(g_u32PacketDataddress%2 == 0)///地址必须为偶数,半字对齐
	{
		///调用写入Flash函数
		FLASH_STATUS = FlashWriteSTM32(g_u32PacketDataddress, uDataLen, pucPacketData);
		if(FLASH_STATUS != RES_OK)
			return FLASH_STATUS;
	}
	else
	{
		///返回写入Flash的地址错
		FLASH_STATUS = ERR_FLASH_ADDR;
		return FLASH_STATUS;
	}
	return FLASH_STATUS;
}




//读取指定地址的半字(16位数据) 
//faddr:读地址 
//返回值:对应数据.
u32 STMFLASH_ReadWord(u32 faddr)
{
	return *(vu32*)faddr; 
}  
//获取某个地址所在的flash扇区
//addr:flash地址
//返回值:0~11,即addr所在的扇区
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
//从指定地址开始写入指定长度的数据
//特别注意:因为STM32F4的扇区实在太大,没办法本地保存扇区数据,所以本函数
//         写地址如果非0XFF,那么会先擦除整个扇区且不保存扇区数据.所以
//         写非0XFF的地址,将导致整个扇区数据丢失.建议写之前确保扇区里
//         没有重要数据,最好是整个扇区先擦除了,然后慢慢往后写. 
//该函数对OTP区域也有效!可以用来写OTP区!
//OTP区域地址范围:0X1FFF7800~0X1FFF7A0F
//WriteAddr:起始地址(此地址必须为4的倍数!!)
//pBuffer:数据指针
//NumToWrite:字(32位)数(就是要写入的32位数据的个数.) 
void STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite)	
{ 
  FLASH_Status status = FLASH_COMPLETE;
	u32 addrx=0;
	u32 endaddr=0;	
  if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4)return;	//非法地址
	FLASH_Unlock();									//解锁 
  FLASH_DataCacheCmd(DISABLE);//FLASH擦除期间,必须禁止数据缓存
 		
	addrx=WriteAddr;				//写入的起始地址
	endaddr=WriteAddr+NumToWrite*4;	//写入的结束地址
	if(addrx<0X1FFF0000)			//只有主存储区,才需要执行擦除操作!!
	{
		while(addrx<endaddr)		//扫清一切障碍.(对非FFFFFFFF的地方,先擦除)
		{
			if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)//有非0XFFFFFFFF的地方,要擦除这个扇区
			{   
				status=FLASH_EraseSector(STMFLASH_GetFlashSector(addrx),VoltageRange_3);//VCC=2.7~3.6V之间!!
				if(status!=FLASH_COMPLETE)break;	//发生错误了
			}else addrx+=4;
		} 
	}
	if(status==FLASH_COMPLETE)
	{
		while(WriteAddr<endaddr)//写数据
		{
			if(FLASH_ProgramWord(WriteAddr,*pBuffer)!=FLASH_COMPLETE)//写入数据
			{ 
				break;	//写入异常
			}
			WriteAddr+=4;
			pBuffer++;
		} 
	}
  FLASH_DataCacheCmd(ENABLE);	//FLASH擦除结束,开启数据缓存
	FLASH_Lock();//上锁
} 

//从指定地址开始读出指定长度的数据
//ReadAddr:起始地址
//pBuffer:数据指针
//NumToRead:字(4位)数
void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead)   	
{
	u32 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//读取4个字节.
		ReadAddr+=4;//偏移4个字节.	
	}
}

