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
#include "yaffs_fileem2k.h"
#include "yaffs_nandemul2k.h"

#include <errno.h>

unsigned yaffs_traceMask = 

	YAFFS_TRACE_SCAN |  
	YAFFS_TRACE_GC | YAFFS_TRACE_GC_DETAIL | 
	YAFFS_TRACE_ERASE | 
	YAFFS_TRACE_TRACING | 
	YAFFS_TRACE_ALLOCATE | 
	YAFFS_TRACE_CHECKPOINT |
	YAFFS_TRACE_BAD_BLOCKS |
	YAFFS_TRACE_VERIFY |
	YAFFS_TRACE_VERIFY_NAND |
	YAFFS_TRACE_VERIFY_FULL |
//	(~0) |
	
	0;
        


void yaffsfs_SetError(int err)
{
	//Do whatever to set error
	errno = err;
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
static size_t malloc_limit = 0 & 6000000;

void *yaffs_malloc(size_t size)
{
	size_t this;
	if(yaffs_kill_alloc)
		return NULL;
	if(malloc_limit && malloc_limit <(total_malloced + size) )
		return NULL;

	this = malloc(size);
	if(this)
		total_malloced += size;
	return this;
}

void yaffs_free(void *ptr)
{
	free(ptr);
}

void yaffsfs_LocalInitialisation(void)
{
	// Define locking semaphore.
}

// Configuration for:
// /ram  2MB ramdisk
// /boot 2MB boot disk (flash)
// /flash 14MB flash disk (flash)
// NB Though /boot and /flash occupy the same physical device they
// are still disticnt "yaffs_Devices. You may think of these as "partitions"
// using non-overlapping areas in the same device.
// 

#include "yaffs_ramdisk.h"
#include "yaffs_flashif.h"
#include "yaffs_nandemul2k.h"

#ifdef WT133664_PORT
#include "D_Chunk_API.h"
#endif

static yaffs_Device k9f1208_dev;

static yaffsfs_DeviceConfiguration yaffsfs_config[] = {
	{ "/", &k9f1208_dev},
	{0, 0} /* Null entry to terminate list */
};


int yaffs_StartUp(void)
{
	// Stuff to configure YAFFS
	// Stuff to initialise anything special (eg lock semaphore).
	yaffsfs_LocalInitialisation();
	
	// Set up devices
	memset(&k9f1208_dev,0,sizeof(k9f1208_dev));
    k9f1208_dev.isYaffs2 = 1;
	k9f1208_dev.nDataBytesPerChunk = 1024;
	k9f1208_dev.nChunksPerBlock = 16;
	k9f1208_dev.nReservedBlocks = 2; // Set this smaller for RAM
	k9f1208_dev.startBlock = 32; // Can use block 0
	k9f1208_dev.endBlock = 128; // Last block in 32MB.    
	k9f1208_dev.nShortOpCaches = 0;  // Disable caching on this device.
	k9f1208_dev.genericDevice = (void *) 0;  // Used to identify the device in fstat.
	k9f1208_dev.writeChunkWithTagsToNAND = DChunk_WriteChunk;
	k9f1208_dev.readChunkWithTagsFromNAND = DChunk_ReadChunk;
	k9f1208_dev.eraseBlockInNAND = DChunk_EreaseBlock;
	k9f1208_dev.initialiseNAND = DChunk_Initialize;
    k9f1208_dev.markNANDBlockBad = DChunk_MarkBadBlock;
    k9f1208_dev.queryNANDBlock = DChunk_QueryBlock;

	yaffs_initialise(yaffsfs_config);
	
	return 0;
}

void SetCheckpointReservedBlocks(int n)
{
//	flashDev.nCheckpointReservedBlocks = n;
}

