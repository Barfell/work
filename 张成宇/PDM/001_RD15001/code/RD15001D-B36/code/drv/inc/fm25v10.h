#ifndef __FM25V10_H_
#define __FM25V10_H_		     
#include "kernal.h"

#define FM25V10_SN 	0XEF13 	

#define SUSPEND_FM25V10()	GPIO_ResetBits(FM25V10_HOLD_GPIO,FM25V10_HOLD_PIN);
#define RELEASE_FM25V10()	GPIO_SetBits(FM25V10_HOLD_GPIO,FM25V10_HOLD_PIN);

////////////////////////////////////////////////////////////////////////////////// 
//指令表
#define FM25V10_WriteEnable			0x06                //写命令前要发送写使能指令。包括WRSR,WRITE,SNR,SNLW
#define FM25V10_WriteDisable		0x04 
#define FM25V10_ReadStatusReg		0x05 
#define FM25V10_WriteStatusReg		0x01 
#define FM25V10_ReadData			0x03 
#define FM25V10_FastReadData		0x0B 
#define FM25V10_WriteMemoryData		0x02 
#define FM25V10_EnterSleepMode		0xB9 
#define FM25V10_ReadDeviceID		0x9F 
#define FM25V10_ReadDeviceSn		0xC3


VOID FM25V10_Init(VOID);
U16  FM25V10_ReadID(VOID);  	        //读取FLASH ID
U8	 FM25V10_ReadSR(VOID);        		//读取状态寄存器 
VOID FM25V10_Write_SR(U8 sr);  			//写状态寄存器
VOID FM25V10_PowerDown(VOID);           //进入掉电模式
VOID FM25V10_WAKEUP(VOID);              //唤醒

VOID FramWriteByte(U32 address,U8 da);
U8 FramReadByte(U32 address);
VOID FramWriteInduce(U32 address,U32 number,U8 *p);
VOID FramReadInduce(U32 address,U32 number,U8 *p);

#endif
















