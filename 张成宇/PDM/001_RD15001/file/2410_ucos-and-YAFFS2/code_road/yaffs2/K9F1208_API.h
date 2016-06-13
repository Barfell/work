#ifndef K9F1208_API_H
#define K9F1208_API_H
#include "TypeCpu.h"

int K9F1208_Init();
int K9F1208_WriteChunk(INT16U block_no, INT16U chunk_no, const INT8U *chunk_data, const INT8U *tag_data);
int K9F1208_ReadChunk(INT16U block_no, INT16U chunk_no, INT8U *chunk_data, INT8U *tag_data);
int K9F1208_EraseBlock(INT16U block_no);

#endif

