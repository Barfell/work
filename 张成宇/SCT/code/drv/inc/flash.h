#ifndef __FLASH_H__
#define __FLASH_H__
#include "kernel.h"   

#define STM32_FLASH_APP_ADDR					0x08006000  	//第一个应用程序起始地址(存放在FLASH)

#define STM_PAGE_SIZE 					0x400			//MD为1k/页		


#define BOOTINFOR_ADDRESS             	0x08005000 ///终端名版本号起始地址
#define UPDATE_FLAG_ADDRESS           	0x08005100 ///数据包更新地址
#define HARDWARE_EDITION              	0X99990901        
#define SOFTWARE_EDITION               	0X88880901   

//flash error code
typedef enum
{
	RES_OK = 0,	 /* 0: Successful */
	ERA_ERROR,	            /* erase  error*/
	WRI_ERROR,	     /* 2: Write error*/
	LENG_ERROR,//数据长度错误
	CHECK_ERROR,//校验和错误
	ERR_FLASH_ADDR,
	ERR_LENGTH,
}FLASH_error;

VOID _GoToSys(VOID);

VOID FlashInit(VOID);

VOID FlashReadSTM32(u32 uReadAddr,u16 uReadLen,u8 *pucDataBuffer);

FLASH_error FlashWriteSTM32(u32 uWriteAddr,u16 uDataLen,u8 *writeDataBuffer);

#define JumpToApp()	_GoToSys()
						   
#endif

















