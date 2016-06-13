/*
 * YAFFS: Yet Another Flash File System. A NAND-flash specific file system.
 *
 * Copyright (C) 2002-2007 Aleph One Ltd.
 *   for Toby Churchill Ltd and Brightstar Engineering
 *
 * Created by Charles Manning <charles@aleph1.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/*
 * yaffscfg2k.c  The configuration for the "direct" use of yaffs.
 *
 * This file is intended to be modified to your requirements.
 * There is no need to redistribute this file.
 */

#include "yaffscfg.h"
#include "yaffsfs.h"

#include <errno.h>

unsigned yaffs_traceMask = 

	YAFFS_TRACE_SCAN |  
	YAFFS_TRACE_GC |
	YAFFS_TRACE_ERASE | 
	YAFFS_TRACE_ERROR | 
	YAFFS_TRACE_TRACING | 
	YAFFS_TRACE_ALLOCATE | 
	YAFFS_TRACE_BAD_BLOCKS |
	YAFFS_TRACE_VERIFY | 
	
	0;
        


static int yaffsfs_lastError;
void yaffsfs_SetError(int err)
{
	yaffsfs_lastError = err;
}
int yaffsfs_GetLastError(void)
{
	return yaffsfs_lastError;
}

void yaffsfs_Lock(void)
{
}
void yaffsfs_Unlock(void)
{
}

__u32 yaffsfs_CurrentTime(void)
{
	return 0;
}


static int yaffs_kill_alloc = 0;
static size_t total_malloced = 0;
static size_t malloc_limit = 6000000;

void *yaffs_malloc(size_t size)
{
	void * this;

	this = malloc(size);
	return this;
}

void yaffs_free(void *ptr)
{
	free(ptr);
}

void yaffsfs_LocalInitialisation(void)
{
}

#include "yaffs_flashif2.h"

static yaffs_Device flashDev;

static yaffsfs_DeviceConfiguration yaffsfs_config[] = {
	{ "//", &flashDev},
	{(void *)0,(void *)0} /* Null entry to terminate list */
};


int yaffs_StartUp(void)
{   
	memset(&flashDev,0,sizeof(flashDev));

    flashDev.name="yaffs2";
	flashDev.totalBytesPerChunk = 2048;//名字误导人 实际上用2048
    flashDev.nDataBytesPerChunk =2048;
    flashDev.spareBytesPerChunk = 64;
	flashDev.nChunksPerBlock = 64;
	flashDev.nReservedBlocks = 5;
	flashDev.inbandTags = 0;
    //flashDev.useNANDECC = 0; //加上他反倒出问题了
	flashDev.startBlock = 0;
	flashDev.endBlock = yflash2_GetNumberOfBlocks()-1;
	flashDev.isYaffs2 = 1;
	flashDev.wideTnodesDisabled=0;
	flashDev.nShortOpCaches = 10; // Use caches
	flashDev.genericDevice = (void *) 2;	// Used to identify the device in fstat.
	flashDev.writeChunkWithTagsToNAND = yflash2_WriteChunkWithTagsToNAND;
	flashDev.readChunkWithTagsFromNAND = yflash2_ReadChunkWithTagsFromNAND;
	flashDev.eraseBlockInNAND = yflash2_EraseBlockInNAND;
	flashDev.initialiseNAND = yflash2_InitialiseNAND;
	flashDev.markNANDBlockBad = yflash2_MarkNANDBlockBad;
	flashDev.queryNANDBlock = yflash2_QueryNANDBlock;

	yaffs_initialise(yaffsfs_config);
	
	return 0;
}



void SetCheckpointReservedBlocks(int n)
{
//	flashDev.nCheckpointReservedBlocks = n;
}

