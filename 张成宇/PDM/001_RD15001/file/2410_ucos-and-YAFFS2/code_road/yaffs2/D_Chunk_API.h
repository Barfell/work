#ifndef D_CHUNK_API_H
#define D_CHUNK_API_H
#include "yaffs_guts.h"

int DChunk_EreaseBlock(struct yaffs_DeviceStruct * dev, int block_index);
int DChunk_Initialize(struct yaffs_DeviceStruct * dev);
int DChunk_WriteChunk(struct yaffs_DeviceStruct * dev, int chunk_index, const __u8 * data, const yaffs_ExtendedTags * tags);
int DChunk_ReadChunk(struct yaffs_DeviceStruct * dev, int chunk_index, __u8 * data, yaffs_ExtendedTags * tags);
int DChunk_MarkBadBlock(struct yaffs_DeviceStruct * dev, int block_index);
int DChunk_QueryBlock(struct yaffs_DeviceStruct * dev, int block_index, yaffs_BlockState *state, int *seq_num);

#endif

