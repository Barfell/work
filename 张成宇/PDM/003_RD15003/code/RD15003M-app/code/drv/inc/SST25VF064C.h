#ifndef __SST25VF0_H_
#define __SST25VF0_H_		     
#include "kernal.h"


////////////////////////////////////////////////////////////////////////////////// 
//指令表
//64mbit = 8M bytes
//每次写256个字节/页

#define SST_DATA_UNIT_SIZE			0x100

#define SST25VF0_ReadReg					0x03
#define SST25VF0_HighSpeedReadReg			0x0B
#define SST25VF0_SectorErase4KReg			0x20
#define SST25VF0_SectorErase32KReg			0x52
#define SST25VF0_SectorErase64KReg			0xD8
#define SST25VF0_ChipeEraseFullReg			0x60		//C7
#define SST25VF0_PageProgramReg				0x02		
#define SST25VF0_ReadStatusReg				0x05		//RDSR
#define SST25VF0_EnableWriteStatusReg		0x50		//EWSR
#define SST25VF0_WriteStatusReg				0x01		//WRSR
#define SST25VF0_WriteEnableReg				0x06		//WREN
#define SST25VF0_WriteDisableReg			0x04		//WRDI
#define SST25VF0_ReadDidReg					0x90		//read id   //AB
#define SST25VF0_JedecIdReg					0x9f		  
#define SST25VF0_EHLDReg					0xAA		//EHLD
#define SST25VF0_ReadSidReg					0x88		//read security id
#define SST25VF0_ProSidReg					0xA5		//program user security id
#define SST25VF0_LockSidReg					0x85		//Lockout security id programming


#define SST25VF064C_JEDEC_ID   				0xBF254B


VOID SST25VF0_Init(VOID);
VOID ExternFlash_Init(VOID);
U32 ReadID(U8 ID_addr);
U32 JedecIDRead(VOID) ;
VOID ReadSID(U8 Dst, U8 *psave, U8 security_length) ;
VOID ProgSID(U8 *psecurityid) ;
VOID LockSID(VOID);
U8 Read(U32 Dst);


VOID ExternFlashBlockErase_64K(U32 Dst);
VOID ExternFlashBlockErase_32K(U32 Dst);
VOID ExternFlashSectorErase_4K(U32 Dst);
VOID ExternFlashChipErase(VOID);
VOID ExternFlashHighSpeedRead(U32 Dst, U8 *psave, U32 no_bytes);
VOID ExternFlashPageProgram(U32 Dst, U8 *pupper,U32 amount);

#endif
















