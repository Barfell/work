/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/
#include "adaptor.h"
#include "diskio.h"
#include "bsp.h"
#include "lpc_types.h"
#include "nandflash_k9f2g08u0x.h"
#include "debug_frmwrk.h"
/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */
/*-----------------------------------------------------------------------*/



/*-----------------------------------------------------------------------*/
/* 初始化设备                                                  */
/*-----------------------------------------------------------------------*/
//drv为设备类型编号(自定义的)
DSTATUS disk_initialize (BYTE drv	)
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
	DRESULT res;
	
	FAT_ReadNF(sector,count,buff);

	return 0;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/
/* The FatFs module will issue multiple sector transfer request
/  (count > 1) to the disk I/O layer. The disk function should process
/  the multiple sector transfer properly Do. not translate it into
/  multiple single sector transfers to the media, or the data read/write
/  performance may be drasticaly decreased. */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
	DRESULT res;
	int i;


    put_str("write:");_DBH32(sector);put_str("");
	FAT_WriteNF2G08(sector,count,(uint8_t *)buff);

	return 0;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	DWORD *buff		/* Buffer to send/receive control data */
)
{      
        switch(ctrl)
        {
                case CTRL_SYNC:
                    return 0;
        		case GET_SECTOR_COUNT:  // 不能小于128
        			*(DWORD*)buff=1024;//256M共256*1024*1024/512,我这NF有3Bad
        			return 0;
        		case GET_BLOCK_SIZE:    // 取值范围可以是1~32768 否则返回 FR_MKFS_ABORTED
        			*(DWORD*)buff=512;//256M共256*1024*1024/512,我这NF有3Bad
        			return 0;
		default:
			break;
	}

	return 0;//RES_PARERR;
	
}

