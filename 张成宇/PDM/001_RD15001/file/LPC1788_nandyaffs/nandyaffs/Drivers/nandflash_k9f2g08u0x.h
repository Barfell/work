/***********************************************************************//**
 * @file		sdram_mt48lc8m32lfb5.h
 * @brief		Contains all macro definitions and function prototypes
 * 				support for external Nand Flash SamSung K9F1G08U0A
 * @version		1.0
 * @date		13. Dec. 2010
 * @author		NXP MCU SW Application Team
 **************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **************************************************************************/

#ifndef NANDFLASH_K9F1G08U0A_H_
#define NANDFLASH_K9F1G08U0A_H_

#include "lpc177x_8x_emc.h"

#ifndef _USING_OEM_QVGA_BASEBRD
#define _RUNNING_WITH_K9F1G08U0C
#else
#undef _RUNNING_WITH_K9F1G08U0C
#endif


/*****************************************************************************
 * Defines and typedefs
 ****************************************************************************/
#define K9F1G_CLE   ((volatile uint8_t *)(0x80000000|(0x1<<20)))
#define K9F1G_ALE	((volatile uint8_t *)(0x80000000|(0x1<<19)))
#define K9F1G_DATA  ((volatile uint8_t *)0x81000000)

#define NANDFLASH_BASE_ADDR			0x00000000

#define NANDFLASH_INVALIDBLOCK_CHECK_COLUMM			(2048)

// total 2048 blocks in a device
#define NANDFLASH_NUMOF_BLOCK		2048

// total pages in a block
#define NANDFLASH_PAGE_PER_BLOCK		64

#define NANDFLASH_RW_PAGE_SIZE		2048		// 2048 bytes/page

#define NANDFLASH_SPARE_SIZE		64 			//64 (bytes spare)/page

//full page size
#define NANDFLASH_PAGE_FSIZE		(NANDFLASH_RW_PAGE_SIZE + NANDFLASH_SPARE_SIZE)

// attention rwsize and fsize
#define NANDFLASH_BLOCK_RWSIZE	(NANDFLASH_RW_PAGE_SIZE * NANDFLASH_PAGE_PER_BLOCK)
#define NANDFLASH_BLOCK_FSIZE	(NANDFLASH_PAGE_FSIZE * NANDFLASH_PAGE_PER_BLOCK)


#define NANDFLASH_ADDR_COLUMM_POS		0
#define NANDFLASH_ADDR_ROW_POS			16

#define K9FXX_ID					0xECDA0000	/* Byte 3 and 2 only */

#define K9FXX_READ_1            		0x00
#define K9FXX_READ_2            		0x30
#define K9FXX_READ_ID           		0x90
#define K9FXX_RESET             			0xFF
#define K9FXX_BLOCK_PROGRAM_1   	0x80
#define K9FXX_BLOCK_PROGRAM_2   	0x10
#define K9FXX_BLOCK_ERASE_1     	0x60
#define K9FXX_BLOCK_ERASE_2     	0xD0
#define K9FXX_READ_STATUS       		0x70

#define K9FXX_BUSY              	(1 << 6)
#define K9FXX_OK                	(1 << 0)

#define ERR_RETVAL_OK				(0)
#define ERR_RETVAL_ERROR			(-1)
#define ERR_RETVAL_WRONG_INPUT		(-2)

extern void NandFlash_Init( void );
extern void NandFlash_Reset( void );
extern void NandFlash_WaitForReady( void );	/* same as CheckBusy, no time out */
extern uint32_t NandFlash_ReadId( void );
extern Bool NandFlash_ReadStatus( uint32_t Cmd );
extern Bool NandFlash_BlockErase( uint32_t blockNum );
extern Bool NandFlash_ValidBlockCheck( void );

extern Bool NandFlash_PageRead( uint32_t pageNum, uint32_t blockNum, uint8_t *bufPtr );

extern int NandFlash_PageReadFromBeginning(uint32_t block, uint32_t page, uint8_t* bufPtr);
extern int NandFlash_PageReadFromAddr(uint32_t blockNum, uint32_t pageNum,
													uint32_t addrInPage, uint8_t* bufPtr, uint32_t size);
extern int NandFlash_ReadFromAddr(uint32_t addrInWholeNand, uint8_t* bufPtr, uint32_t size);
extern int NandFlash_SectorRead(uint32_t sectorNum, uint8_t* bufPtr);//add by zjy

extern uint32_t  Nand_EraseBlockLarge(int BlockAddr);
extern int  Nand_WritePageWithSpare2048(int PageNum,const uint8_t * DataBuf,const uint8_t *Spare);
extern int Nand_ReadPageWithSpare2048(int PageNum,uint8_t *const DataBuf, uint8_t *const Spare);
#endif /* NANDFLASH_K9F1G08U0A_H_ */
