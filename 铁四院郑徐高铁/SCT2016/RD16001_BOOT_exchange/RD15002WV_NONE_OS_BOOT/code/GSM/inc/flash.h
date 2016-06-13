#ifndef __FLASH_H__
#define __FLASH_H__
#include "includes.h"   

#define STM_APP_ADDRESS 				0x08080000
#define STM32_FLASH_APP_ADDR			0x08080000  	//��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)

#define STM_PAGE_SIZE 					0x400			//MDΪ1k/ҳ		


#define BOOTINFOR_ADDRESS             	0x080e0000 ///�ն����汾����ʼ��ַ
#define UPDATE_FLAG_ADDRESS           	0x080e0100 ///���ݰ����µ�ַ
#define HARDWARE_EDITION              	0X99990901        
#define SOFTWARE_EDITION               	0X88880901   


//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH����ʼ��ַ
 

//FLASH ��������ʼ��ַ
#define ADDR_FLASH_SECTOR_0     ((u32)0x08000000) 	//����0��ʼ��ַ, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     ((u32)0x08004000) 	//����1��ʼ��ַ, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     ((u32)0x08008000) 	//����2��ʼ��ַ, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     ((u32)0x0800C000) 	//����3��ʼ��ַ, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     ((u32)0x08010000) 	//����4��ʼ��ַ, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     ((u32)0x08020000) 	//����5��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_6     ((u32)0x08040000) 	//����6��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_7     ((u32)0x08060000) 	//����7��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_8     ((u32)0x08080000) 	//����8��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_9     ((u32)0x080A0000) 	//����9��ʼ��ַ, 128 Kbytes  
#define ADDR_FLASH_SECTOR_10    ((u32)0x080C0000) 	//����10��ʼ��ַ,128 Kbytes  
#define ADDR_FLASH_SECTOR_11    ((u32)0x080E0000) 	//����11��ʼ��ַ,128 Kbytes  



//flash error code
typedef enum
{
	RES_OK = 0,	 /* 0: Successful */
	ERA_ERROR,	            /* erase  error*/
	WRI_ERROR,	     /* 2: Write error*/
	LENG_ERROR,//���ݳ��ȴ���
	CHECK_ERROR,//У��ʹ���
	ERR_FLASH_ADDR,
	ERR_LENGTH,
}FLASH_error;

//VOID _GoToSys(VOID);

VOID FlashInit(VOID);

VOID FlashReadSTM32(u32 uReadAddr,u16 uReadLen,u8 *pucDataBuffer);

FLASH_error FlashWriteSTM32(u32 uWriteAddr,u16 uDataLen,u8 *writeDataBuffer);



u32 STMFLASH_ReadWord(u32 faddr);		  	//������  
void STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����
		
						   
#endif

















