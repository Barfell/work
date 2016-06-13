#include "bsp.h"
#include "lpc_types.h"
#include "nandflash_k9f2g08u0x.h"
#include "debug_frmwrk.h"
#include "adaptor.h"
#include "ff.h" 
#include "diskio.h"		

extern uint8_t InvalidBlockTable[NANDFLASH_NUMOF_BLOCK];
uint8_t ReadBuf[NANDFLASH_PAGE_FSIZE], WriteBuf[NANDFLASH_PAGE_FSIZE];

FIL openfile;
FATFS fs;
FRESULT res;

//嘟一下写一个sector

uint8_t Nand_Test(void){

	uint32_t FlashID;
	uint32_t i;
	
	put_str("Read NAND Flash ID:  ");

	FlashID = NandFlash_ReadId();
	if ( (FlashID & 0xFFFF0000) != K9FXX_ID )
	{
		put_str_("Error in reading NAND Flash ID, testing terminated!");
		while( 1 );	/* Fatal error */
	}

	_DBH32_(FlashID);put_str_("");

	put_str_("Checking valid block...");
	if ( NandFlash_ValidBlockCheck() == FALSE )
	{
		put_str_("Valid block checking error, testing terminated! At block(s): ");

		for(i = 0; i < NANDFLASH_NUMOF_BLOCK; i++)
		{
			if (InvalidBlockTable[i] == FALSE)
			{
				_DBD32(i);put_str("");
			}
		}
	}

    /*for(i=0;i<512;i++){
		WriteBuf[i] = 0x88;
	}
	for(i=0;i<1024;i++){
		ReadBuf[i] = 0;
	}
	disk_write(0,WriteBuf,0,1);
	for(i=0;i<512;i++){
		WriteBuf[i] = 0x99;
	}
	disk_write(0,WriteBuf,1,1);
	disk_read(0,ReadBuf,0,2);
	put_str_(" disk rok ...");
	for(i=0;i<1024;i++){
		_DBH_(ReadBuf[i]);
	}
	while(1);*/
    for(i=0;i<2048;i++)
    {
        NandFlash_BlockErase(i);
    }

    
	CheckBad();
	res = f_mount(0,&fs); 
	if(res==RES_OK){
		put_str_("f mount ok");
	}
	else{
		put_str_("f mount err");put_str("");
		_DBH_(res);put_str("");
	}
	
	res = f_mkfs(0,0,0);
	if(res==RES_OK){
		put_str_("f mkfs ok");
	}
	else{
		put_str_("f mks err");put_str("");
		_DBH_(res);put_str("");
	}

    res = f_open(&openfile , "zjy.txt", FA_READ | FA_WRITE | FA_CREATE_NEW);
    if(res == FR_OK){
    		put_str("f open ok");
    }
    else{
    		put_str_("f open err");put_str("");
        	_DBH_(res);put_str("");
    }
	while(1);

	/**************************************************************
    * NandFlash_BlockErase() could scrub off all the invalid 	    *
    * block infomation including the factory initial invalid	    *
    * block table information. Per Samsung's K9F1G08 Users Manual,*
    * "Any intentional erasure of the initial invalid block		*
    * information is prohibited.									*
    *	However, during the driver debugging, it may create lot of  *
    *	invalid blocks. Below NandFlash_BlockErase() is used to deal *
    * with situation like that.                                   *
    *																*
    ***************************************************************/
    /* Erase the entire NAND FLASH */
    put_str_("Erase entire NAND Flash...");

    for ( i = 0; i < NANDFLASH_NUMOF_BLOCK; i++ )
    {
	  	if ( NandFlash_BlockErase(i) == FALSE )
	  	{
			put_str("Erase NAND Flash fail at block: ");_DBD32(i);put_str_("");
	  	}
   }

    /* For the test program, the pattern for the whole page 2048 bytes
    is organized as: 0x0, 0x1, ... 0xFF, 0x0, 0x01...... */
    for ( i = 0; i < NANDFLASH_RW_PAGE_SIZE; i++ )
    {
	  	ReadBuf[i] = 0;
	  	WriteBuf[i] = i;
    }

    /* If it's a valid block, program all the pages of this block,
    read back, and finally validate. */
    /* simple program to program the block 0 and page 0 */

    if ( InvalidBlockTable[0] != FALSE )
    {
    	put_str_("Write a block of 2K(one page) data to NAND Flash...");
	  	if ( NandFlash_PageProgram( 0, 0, &WriteBuf[0] ) == FALSE )
		  	{
	  			put_str_("Writing fail, testing terminated!");
			   return 0;
		  	}

	  	put_str_("Read back a block of 2K(one page)  data from NAND Flash...");
	  	if ( NandFlash_PageRead( 0, 0, &ReadBuf[0] ) == FALSE )
		  	{
	  			put_str_("Reading fail, testing terminated!");
				return 0;
		  	}

	  	/* Comparison read and write buffer */
	  	put_str_("Verify data...");
	  	for ( i = 0; i < NANDFLASH_RW_PAGE_SIZE; i++ )
	  	{
			if ( ReadBuf[i] != WriteBuf[i] )
			{
			  	put_str_("Verifying fail, testing terminated!");
				return 0;
			}
	  	}
	put_str_("Verifying success! press ESC return MENU!");
    return 1;
    }
	put_str_("Block Invalid,Test fail!");
    return 0;
}

