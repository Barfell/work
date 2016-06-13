/***********************************************************************//**
 * @file		nandflash_k9f1g08u0a.c
 * @brief		Contains all functions support for Nand Flash SamSung
 				K9F2G08U0B
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
 **********************************************************************/
#include "bsp.h"
#include "nandflash_k9f2g08u0x.h"
#include "lpc177x_8x_emc.h"
#include "lpc177x_8x_clkpwr.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_timer.h"
#include "debug_frmwrk.h"

uint8_t InvalidBlockTable[NANDFLASH_NUMOF_BLOCK];

/*********************************************************************//**
 * @brief 		Initialize external NAND FLASH memory
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void NandFlash_Init( void )
{
	uint32_t i;
	TIM_TIMERCFG_Type TIM_ConfigStruct;

	/**************************************************************************
	* Initialize EMC for NAND FLASH
	**************************************************************************/
	EMC_Init();

	LPC_EMC->Control = EMC_Control_E;//|(1<<1);

	EMC_StaMemConfigMW (0,EMC_StaticConfig_MW_8BITS);

	EMC_StaMemConfigPB(0,EMC_StaticConfig_PB); //PB = 1 WE# 信号有效
											   //PB = 0 WE#信号无效，BLS#取代WE#功能

	EMC_SetStaMemoryParameter(0, EMC_STA_MEM_WAITWEN, EMC_StaticWaitWen_WAITWEN(2));

	EMC_SetStaMemoryParameter(0, EMC_STA_MEM_WAITOEN, EMC_StaticWaitOen_WAITOEN(2));

	EMC_SetStaMemoryParameter(0, EMC_STA_MEM_WAITWR, EMC_StaticWaitwr_WAITWR(0x1f));

	EMC_SetStaMemoryParameter(0, EMC_STA_MEM_WAITPAGE, EMC_StaticwaitPage_WAITPAGE(0x1f));	

	EMC_SetStaMemoryParameter(0, EMC_STA_MEM_WAITWR, EMC_StaticWaitwr_WAITWR(0x1f));

	EMC_SetStaMemoryParameter(0, EMC_STA_MEM_WAITTURN, EMC_StaticWaitTurn_WAITTURN(0x1f));

    // init timer
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue	= 1;

	// Set configuration for Tim_config and Tim_MatchConfig
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);

  	// wait 2ms
	TIM_Waitms(2);

	/* assume all blocks are valid to begin with */
	for ( i = 0; i < NANDFLASH_NUMOF_BLOCK; i++ )
	{
		InvalidBlockTable[i] = 0;
	}

	return;
}

/*********************************************************************//**
 * @brief 		Issue Reset command to NAND FLASH memory
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void NandFlash_Reset( void )
{
	volatile uint8_t *pCLE;

	/* Reset NAND FLASH  through NAND FLASH command */
	pCLE = K9F1G_CLE;
	*pCLE = K9FXX_RESET;

	TIM_Waitms(2);
	return;
}

/*********************************************************************//**
 * @brief 		Read status from NAND FLASH memory
 * @param[in]	Cmd	command for read operation, should be:
 * 					-  K9FXX_BLOCK_PROGRAM_1
 *					-  K9FXX_BLOCK_ERASE_1
 *					-  K9FXX_READ_1
 * @return 		Status, could be:
 *				- TRUE: pass
 *				- FALSE: Failure
 **********************************************************************/
Bool NandFlash_ReadStatus(uint32_t Cmd)
{
	volatile uint8_t *pCLE;
	volatile uint8_t *pDATA;
	uint8_t StatusData;

	pCLE  = K9F1G_CLE;
	pDATA = K9F1G_DATA;

	*pCLE = K9FXX_READ_STATUS;

	while ( (*pDATA & 0xC0) != 0xC0 );

	StatusData = *pDATA;

	switch (Cmd)
	{
		case K9FXX_BLOCK_PROGRAM_1:
		case K9FXX_BLOCK_ERASE_1:
		  	if (StatusData & 0x01)	/* Erase/Program failure(1) or pass(0) */
				return(FALSE);
		  	else
				return(TRUE);

		case K9FXX_READ_1:				/* bit 5 and 6, Read busy(0) or ready(1) */
		  	return(TRUE);

		default:
		  	break;
	}

	return(FALSE);
}
/*********************************************************************//**
 * @brief 		Read ID from external NAND FLASH memory
 * @param[in]	None
 * @return 		ID value
 **********************************************************************/
uint32_t NandFlash_ReadId( void )
{
	uint8_t a, b, c, d;
	volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	volatile uint8_t *pDATA;

	pCLE  = K9F1G_CLE;
	pALE  = K9F1G_ALE;
	pDATA = K9F1G_DATA;

	*pCLE = K9FXX_READ_ID;
	*pALE = 0;

	a = *pDATA;
	b = *pDATA;
	d = *pDATA;
	c = *pDATA;

	return ((a << 24) | (b << 16) | (c << 8) | d);
}

/*********************************************************************//**
 * @brief 		Erase the whole NAND FLASH memory block based on the
 *				block number
 * @param[in]	blockNum	number of block that will be erased, should
 *				be in range: 0 .. 2048
 * @return 		Erase status, could be:
 * 					- TRUE: pass
 *					- FALSE: failure
 **********************************************************************/
Bool NandFlash_BlockErase( uint32_t blockNum )
{
	volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	uint32_t rowAddr;

	pCLE  = K9F1G_CLE;
	pALE  = K9F1G_ALE;

	rowAddr = blockNum * NANDFLASH_PAGE_PER_BLOCK;// page 为单位  block内的第一page所属全局page的号
	
	*pCLE = K9FXX_BLOCK_ERASE_1;

	*pALE = (uint8_t)(rowAddr & 0x00FF);			/* column address low */

	*pALE = (uint8_t)((rowAddr & 0xFF00) >> 8);	/* column address high */

	*pALE = (uint8_t)((rowAddr & 0xFF0000) >> 16);	/* column address high */

	*pCLE = K9FXX_BLOCK_ERASE_2;
    // 这里的时间有可能需要减
	Delay(10);//delay 10ms. K9F2G08 Block Erase Time max 10ms type 1.5ms

	return(NandFlash_ReadStatus(K9FXX_BLOCK_ERASE_1));
}

/*********************************************************************//**
 * @brief 		This routine is used to check if the block is valid or
 *				not.
 * @param[in]	None
 * @return 		Checking status, could be:
 * 					- TRUE: all blocks are valid
 *					- FALSE: invalid block is found, an initial invalid
 *						     table will be created
 * 检查每一块内的前两页的第2049个字节,有不为0xff值时说明是厂家标记的坏块
 **********************************************************************/
Bool NandFlash_ValidBlockCheck( void )
{
	uint32_t block, page;
	Bool retValue = TRUE;

	uint8_t data = 0;

	for ( block = 0; block < NANDFLASH_NUMOF_BLOCK; block++ )
	{
		for ( page = 0; page < 2; page++ )
		{
			/* Check column address 2048 at first page and second page 	2048作为page内地址读*/
			NandFlash_PageReadFromAddr(block, page, NANDFLASH_INVALIDBLOCK_CHECK_COLUMM, &data, 1);

			if(data != 0xFF)
			{
				// found invalid block number, mark block number in the invalid
				// block table
				InvalidBlockTable[block] = 0;
				//At least one block is invalid
				retValue = FALSE;
			}else{
			   	InvalidBlockTable[block] = 1;
			}
		}
	}

	return(retValue);
}

/*********************************************************************//**
 * @brief 		Write a full page of program into NAND flash based on the
 *				page number, write up to 2112 bytes of data at a time.
 * @param[in]	pageNum		number of page that will be programmed, should
 * 				be in range: 0..63
 * 				blockNum	number of block that will be programmed, should
 * 				be in range: 0..1023
 * 				bufPtr		pointer to the buffer that contain data will be
 * 				programmed in flash memory
 * @return 		Program status, could be:
 * 					- TRUE: success
 * 					- FALSE: fail
 **********************************************************************/

/*********************************************************************//**
 * @brief 		Read the whole NAND FLASH memory page based on the
**				page number, the data will be stored in the pointer
**				to the buffer.
 * @param[in]	pageNum		number of page that will be read, should
 * 				be in range: 0..63
 * 				blockNum	number of block that will be read, should
 * 				be in range: 0..2047
 * 				bufPtr		pointer to the buffer that contain data will be
 * 				read from flash memory
 * @return 		Read status, could be:
 * 					- TRUE: success
 * 					- FALSE: fail
 **********************************************************************/
Bool NandFlash_PageRead( uint32_t pageNum, uint32_t blockNum, uint8_t *bufPtr )
{
	return (NandFlash_PageReadFromBeginning(pageNum, blockNum, bufPtr) != 0);
}

/*********************************************************************//**
 * @brief 		Read the whole NAND FLASH memory page based on the
**				page number, the data will be stored in the pointer
**				to the buffer.
 * @param[in]	pageNum		number of page that will be read, should
 * 				be in range: 0..63
 * 				blockNum	number of block that will be read, should
 * 				be in range: 0..2047
 * 				bufPtr		pointer to the buffer that contain data will be
 * 				read from flash memory
 * @return 		number of byte(s) read til the end of the page
 * 读一页数据(2048+64)bytes
 **********************************************************************/
int NandFlash_PageReadFromBeginning(uint32_t blockNum, uint32_t pageNum, uint8_t* bufPtr)
{
	return (NandFlash_PageReadFromAddr(blockNum, pageNum, 0, bufPtr, NANDFLASH_PAGE_FSIZE));// 操作的是fsize
}

/*********************************************************************//**
 * @brief 		Read the whole NAND FLASH memory page based on the
**				page number, the data will be stored in the pointer
**				to the buffer.
 * @param[in]	pageNum:	number of page that will be read, should
 * 				be in range: 0..63
 * 				blockNum:	number of block that will be read, should
 * 							be in range: 0..1023
 *				addressInPage: the address in NandFlash to be read,
 * 							calculated from the beginning of page
 * 				bufPtr:		pointer to the buffer that contain data will be
 * 							read from flash memory
 *				size: the number of byte(s) to be read and stored to the buffer
 * @return 		number of byte(s) read til the end of the page
 **********************************************************************/
int NandFlash_PageReadFromAddr(uint32_t blockNum, uint32_t pageNum,
											uint32_t addrInPage, uint8_t* bufPtr, uint32_t size)
{
	uint32_t curAddr = 0;

	curAddr += blockNum * NANDFLASH_BLOCK_FSIZE;	// 操作的是fsize

	curAddr += pageNum * NANDFLASH_PAGE_FSIZE;	// 操作的是fsize

	curAddr += addrInPage;

	return (NandFlash_ReadFromAddr(curAddr, bufPtr, size));
}

/*********************************************************************//**
 * @brief 		Read the whole NAND FLASH memory at an expected address,
 *				the data will be stored in the pointer to the buffer.
 * @param[in]	addressInWholeNand: the address in NandFlash to be read,
 * 						calculated from the beginning of Nand base address 0
 * 				bufPtr:	pointer to the buffer that contain data will be
 * 						read from flash memory
 *				size: the number of byte(s) to be read and stored to the buffer
 * @return 		number of byte(s) read til the end of the page
 * 注意:这里操作的addrInWholeNand 为包括了(2048+64)的字节地址
 **********************************************************************/
int NandFlash_ReadFromAddr(uint32_t addrInWholeNand, uint8_t* bufPtr, uint32_t size)
{
	volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	volatile uint8_t *pDATA;
	volatile uint8_t nand_buf;
	uint32_t i, curColumm, curRow;

	i = 0;

	pCLE  = K9F1G_CLE;
	pALE  = K9F1G_ALE;
	pDATA = K9F1G_DATA;

	curColumm = addrInWholeNand % NANDFLASH_PAGE_FSIZE;		// 操作的是fsize
	curRow = addrInWholeNand / NANDFLASH_PAGE_FSIZE;			// 操作的是fsize

	*pCLE = K9FXX_READ_1;

	*pALE = (uint8_t)(curColumm & 0x000000FF);			/* column address low */

	*pALE = (uint8_t)((curColumm & 0x00000F00) >> 8);		/* column address high */

	*pALE = (uint8_t)(curRow & 0x000000FF);		/* row address low */

	*pALE = (uint8_t)((curRow & 0x0000FF00) >> 8);

	*pALE = (uint8_t)((curRow & 0x00010000) >> 16);	/* row address high */

	*pCLE = K9FXX_READ_2;

	Delay(1);

	//Get data from the current address in the page til the end of the page
	for ( i = 0; i < (NANDFLASH_PAGE_FSIZE - curColumm); i++ )
	{
		*bufPtr = *pDATA;
		if((i + 1) >= size)
			break;
		bufPtr++;
	}

	// Ok, return
	return i;
}


// add by zjy self
int NandFlash_SectorRead(uint32_t sectorNum, uint8_t* bufPtr)
{
	uint32_t curAddr = 0;

	curAddr += sectorNum * 512;
	curAddr +=(sectorNum/4)*NANDFLASH_SPARE_SIZE;
	return (NandFlash_ReadFromAddr(curAddr, bufPtr, 512));
}




uint32_t  Nand_EraseBlockLarge(int BlockAddr)
{
    volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	uint32_t rowAddr;

	pCLE  = K9F1G_CLE;
	pALE  = K9F1G_ALE;

	rowAddr = BlockAddr * NANDFLASH_PAGE_PER_BLOCK;
	
	*pCLE = K9FXX_BLOCK_ERASE_1;
    
	*pALE = (uint8_t)(rowAddr & 0x00FF);			/* column address low */
    
	*pALE = (uint8_t)((rowAddr & 0xFF00) >> 8);	/* column address high */
    
	*pALE = (uint8_t)((rowAddr & 0xFF0000) >> 16);	/* column address high */
    
	*pCLE = K9FXX_BLOCK_ERASE_2;
    // 这里的时间有可能需要减
	Delay(10);//delay 10ms. K9F2G08 Block Erase Time max 10ms type 1.5ms
    
	return 1;//(NandFlash_ReadStatus(K9FXX_BLOCK_ERASE_1));
}

int  Nand_WritePageWithSpare2048(int PageNum,const uint8_t * DataBuf,const uint8_t *Spare)
{
	volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	volatile uint8_t *pDATA;
	volatile uint32_t i, curAddr, curColumm,curRow;

	pCLE  = K9F1G_CLE;
	pALE  = K9F1G_ALE;
	pDATA = K9F1G_DATA;

    if(DataBuf == NULL)
	    curColumm = NANDFLASH_RW_PAGE_SIZE;
    else
        curColumm = 0;
    
	curRow = PageNum;

	*pCLE = K9FXX_BLOCK_PROGRAM_1;

	*pALE =  (uint8_t)(curColumm & 0x000000FF);		/* column address low */

	*pALE = (uint8_t)((curColumm & 0x00000F00) >> 8);	/* column address high */

	*pALE = (uint8_t)(curRow & 0x000000FF);		/* row address low */

	*pALE = (uint8_t)((curRow & 0x0000FF00) >> 8);

	*pALE = (uint8_t)((curRow & 0x00010000) >> 16);	/* row address high */

    if(DataBuf != NULL)
    {
    	for ( i = 0; i < NANDFLASH_RW_PAGE_SIZE; i++ )
    	{
    		*pDATA = *DataBuf++;
    	}
    }

    if(Spare != NULL)
    {
        for ( i = 0; i < NANDFLASH_SPARE_SIZE; i++ ) // 添加写spare
    	{
    		*pDATA = *Spare++;
    	}
    }
    
	*pCLE = K9FXX_BLOCK_PROGRAM_2;

	Delay(1);			//delay 1ms

	return 1;//( NandFlash_ReadStatus( K9FXX_BLOCK_PROGRAM_1 ) );
}

int Nand_ReadPageWithSpare2048(int PageNum,uint8_t *const DataBuf, uint8_t *const Spare)
{
	volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	volatile uint8_t *pDATA;
	volatile uint8_t nand_buf;
	uint32_t i, curColumm, curRow;
    volatile uint8_t j;
    
	i = 0;

	pCLE  = K9F1G_CLE;
	pALE  = K9F1G_ALE;
	pDATA = K9F1G_DATA;

	curColumm = 0;
	curRow = PageNum;

	*pCLE = K9FXX_READ_1;

	*pALE = (uint8_t)(curColumm & 0x000000FF);			/* column address low */

	*pALE = (uint8_t)((curColumm & 0x00000F00) >> 8);		/* column address high */

	*pALE = (uint8_t)(curRow & 0x000000FF);		/* row address low */

	*pALE = (uint8_t)((curRow & 0x0000FF00) >> 8);

	*pALE = (uint8_t)((curRow & 0x00010000) >> 16);	/* row address high */

	*pCLE = K9FXX_READ_2;

    
	Delay(1);
    
    if(DataBuf != NULL)
    {
        for(i=0;i<NANDFLASH_RW_PAGE_SIZE;i++)
        {
            DataBuf[i]=*pDATA;
        }
    }
    else
    {
        for(i=0;i<NANDFLASH_RW_PAGE_SIZE;i++)
        {
            j=*pDATA;
        } 
    }
    if(Spare!=NULL)
    {
        for(i=0;i<NANDFLASH_SPARE_SIZE;i++)
        {
        	Spare[i]=*pDATA;
        }
    }
    else
    {
        for(i=0;i<NANDFLASH_SPARE_SIZE;i++)
        {
        	j=*pDATA;
        }
    }
    
	return 1;
}

