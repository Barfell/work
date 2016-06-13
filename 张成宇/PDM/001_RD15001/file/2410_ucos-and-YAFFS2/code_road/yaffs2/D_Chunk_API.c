#include "K9F1208_API.h"
#include "TypeCpu.h"
#include "D_Chunk_API.h"
#include "Yaffs_ECC.h"
#include <stdio.h>

static const INT16U D_CHUNK_NUM_IN_BLOCK = 16;
static const INT16U K9F1208_CHUNK_SIZE = 512;
static const INT16U K9F1208_TAG_SIZE = 16;

static INT8U GetBitFrom16Bytes(const INT8U *data, INT8U pos)
{
	INT8U byte_pos = pos / 8;
	INT8U bit_pos = pos % 8;
	INT8U mask = 1 << bit_pos;
	
	return ((data[byte_pos] & mask) > 0 ? 1 : 0);
}

static INT32U GetBitsFrom16Bytes(const INT8U *data, INT8U bin, INT8U run_len)
{
	assert(run_len <= 32);
	INT8U end = bin + run_len - 1;
	INT32U value = 0;
	INT8U offset = 0;
	INT8U i = bin;

	for (; i <= end; ++i, ++offset)
	{
		value |= (GetBitFrom16Bytes(data, i) << offset);
	}

	return value;
}

static void SetBitInto16Bytes(INT8U *data, INT8U pos, INT32U value)
{
	INT8U byte_pos = pos / 8;
	INT8U bit_pos = pos % 8;
	INT8U mask = 1 << bit_pos;

	if (0 != value)
		data[byte_pos] |= mask;
	else
		data[byte_pos] &= ~mask;
}

static void SetBitsInto16Bytes(INT8U *data, INT8U bin, INT8U run_len, INT32U value)
{
	assert(run_len <= 32);
	INT8U end = bin + run_len - 1;
	INT32U offset = 0;
	INT8U i = bin;

	for (; i <= end; ++i, ++offset)
	{
		INT32U bit_value = value & (1 << offset);
		SetBitInto16Bytes(data, i, bit_value);
	}	
}

static INT8U K9F1208TagIsUnused(const INT8U *tag)
{
	INT8U i = 0;
	for (; i < K9F1208_TAG_SIZE; ++i)
	{
		if (tag[i] != 0xff)	return 0;
	}

	return 1;
}

static INT8U K9F1208TagIsValid(const INT8U *tag)
{
	if (tag[5] == 0xff) return 1;
	else return 0;
}

static void YaffsTag2K9F1208Tag(const yaffs_ExtendedTags *yaffs_tag, INT8U *even_tag, INT8U *odd_tag)
{
	SetBitsInto16Bytes(even_tag, 0, 16, yaffs_tag->objectId);
	SetBitsInto16Bytes(even_tag, 16, 16, yaffs_tag->chunkId);
	SetBitsInto16Bytes(even_tag, 32, 1, yaffs_tag->extraIsShrinkHeader);
	SetBitsInto16Bytes(even_tag, 33, 1, yaffs_tag->extraShadows);
	SetBitsInto16Bytes(even_tag, 34, 4, yaffs_tag->extraObjectType);
	SetBitsInto16Bytes(even_tag, 38, 2, yaffs_tag->serialNumber);
	SetBitsInto16Bytes(even_tag, 40, 8, 0xff);
	SetBitsInto16Bytes(even_tag, 48, 11, yaffs_tag->byteCount);
	SetBitsInto16Bytes(even_tag, 59, 29, yaffs_tag->sequenceNumber);
	SetBitsInto16Bytes(even_tag, 88, 1, yaffs_tag->extraHeaderInfoAvailable);
	SetBitsInto16Bytes(even_tag, 89, 16, yaffs_tag->extraParentObjectId);
	SetBitsInto16Bytes(even_tag, 105, 21, yaffs_tag->extraFileLength);
	SetBitsInto16Bytes(even_tag, 126, 2, 0);
	SetBitsInto16Bytes(odd_tag, 0, 16, yaffs_tag->extraEquivalentObjectId);
	SetBitsInto16Bytes(odd_tag, 32, 8, 0);
	SetBitsInto16Bytes(odd_tag, 40, 8, 0xff);
	SetBitsInto16Bytes(odd_tag, 96, 32, 0);
}

static void K9F1208Tag2YaffsTag(const INT8U *even_tag, const INT8U *odd_tag, yaffs_ExtendedTags *yaffs_tag)
{
	yaffs_tag->validMarker0 = 0xAAAAAAAA;
	yaffs_tag->validMarker1 = 0x55555555;
	yaffs_tag->chunkUsed = (K9F1208TagIsUnused(even_tag) && K9F1208TagIsUnused(odd_tag)) ? 0 : 1;
	yaffs_tag->objectId = GetBitsFrom16Bytes(even_tag, 0, 16);
	yaffs_tag->chunkId = GetBitsFrom16Bytes(even_tag, 16, 16);
	yaffs_tag->extraIsShrinkHeader = GetBitsFrom16Bytes(even_tag, 32, 1);
	yaffs_tag->extraShadows = GetBitsFrom16Bytes(even_tag, 33, 1);
	yaffs_tag->extraObjectType = (yaffs_ObjectType)GetBitsFrom16Bytes(even_tag, 34, 4);
	yaffs_tag->serialNumber = GetBitsFrom16Bytes(even_tag, 38, 2);
	yaffs_tag->byteCount= GetBitsFrom16Bytes(even_tag, 48, 11);
	yaffs_tag->chunkDeleted = 0;
	yaffs_tag->sequenceNumber = GetBitsFrom16Bytes(even_tag, 59, 29);
	yaffs_tag->extraHeaderInfoAvailable = GetBitsFrom16Bytes(even_tag, 88, 1);
	yaffs_tag->extraParentObjectId = GetBitsFrom16Bytes(even_tag, 89, 16);
	yaffs_tag->extraFileLength = GetBitsFrom16Bytes(even_tag, 105, 21);
	yaffs_tag->extraEquivalentObjectId = GetBitsFrom16Bytes(odd_tag, 0, 16);
	yaffs_tag->blockBad = (K9F1208TagIsValid(even_tag) & K9F1208TagIsValid(odd_tag)) ? 0 : 1;
}

static INT16U CalcDChunkTagECC(INT8U *tag)
{
    yaffs_ECCOther ecc = {0};
    INT16U ecc_calc = 0;
    yaffs_ECCCalculateOther(tag, K9F1208_TAG_SIZE << 1, &ecc);
    ecc_calc = ecc.colParity + ((ecc.lineParity & 0x0000001f) << 6) + ((ecc.lineParityPrime & 0x0000001f) << 11);
    return ecc_calc;
}

static INT32U Calc512BytesECC(INT8U *data)
{
    yaffs_ECCOther ecc = {0};
    INT32U ecc_calc = 0;
    yaffs_ECCCalculateOther(data, K9F1208_CHUNK_SIZE, &ecc);
    ecc_calc = ecc.colParity + ((ecc.lineParity & 0x000001ff) << 6) + ((ecc.lineParityPrime & 0x000001ff) << 15);
    return ecc_calc;
}

int DChunk_EreaseBlock(struct yaffs_DeviceStruct * dev, int block_index)
{
	return K9F1208_EraseBlock(block_index);
}

int DChunk_Initialize(struct yaffs_DeviceStruct *dev)
{
	K9F1208_Init();
    return YAFFS_OK;
}

int DChunk_WriteChunk(struct yaffs_DeviceStruct *dev, int d_chunk_index, const __u8 *data, const yaffs_ExtendedTags *tags)
{
    INT16U block_index = d_chunk_index / D_CHUNK_NUM_IN_BLOCK;
    INT8U d_chunk_index_in_block = d_chunk_index % D_CHUNK_NUM_IN_BLOCK;
    INT8U even_chunk_index = d_chunk_index_in_block << 1;
    INT8U odd_chunk_index = (d_chunk_index_in_block << 1) + 1;

    INT8U d_chunk_tag[K9F1208_TAG_SIZE << 1];
	INT8U *even_tag = d_chunk_tag;
	INT8U *odd_tag = d_chunk_tag + K9F1208_TAG_SIZE;

	INT8U *d_chunk_data = (INT8U *)data;
	if (0 == d_chunk_data)
	{
		d_chunk_data = (INT8U *)malloc(K9F1208_CHUNK_SIZE << 1);
		memset(d_chunk_data, 0, K9F1208_CHUNK_SIZE << 1);
	}

	INT8U *even_chunk_data = d_chunk_data;
	INT8U *odd_chunk_data = d_chunk_data + K9F1208_CHUNK_SIZE;

    INT32U first_chunk_ecc_calc = Calc512BytesECC(even_chunk_data);
    INT32U second_chunk_ecc_calc = Calc512BytesECC(odd_chunk_data);
	INT16U tag_ecc_calc = 0;
	int even_write_result = 0;
	int odd_write_result = 0;

	memset(d_chunk_tag, 0, K9F1208_TAG_SIZE << 1);

	YaffsTag2K9F1208Tag(tags, even_tag, odd_tag);
    SetBitsInto16Bytes(odd_tag, 48, 24, first_chunk_ecc_calc);
    SetBitsInto16Bytes(odd_tag, 72, 24, second_chunk_ecc_calc);
    tag_ecc_calc = CalcDChunkTagECC(d_chunk_tag);
    SetBitsInto16Bytes(odd_tag, 16, 16, tag_ecc_calc);

    even_write_result = K9F1208_WriteChunk(block_index, even_chunk_index, even_chunk_data, even_tag);
    odd_write_result = K9F1208_WriteChunk(block_index, odd_chunk_index, odd_chunk_data, odd_tag);

	if (0 == data) free(d_chunk_data);

	return (even_write_result | odd_write_result);
}

static void CalcDChunkECC(INT8U *d_chunk_tag, INT8U *chunk_data, yaffs_ExtendedTags *tags)
{
	INT8U *even_tag = d_chunk_tag;
	INT8U *odd_tag = d_chunk_tag + K9F1208_TAG_SIZE;
	INT8U *even_chunk_data = chunk_data;
	INT8U *odd_chunk_data = chunk_data + K9F1208_CHUNK_SIZE;

	INT16U tag_ecc_read = (INT16U)GetBitsFrom16Bytes(odd_tag, 16, 16);
	INT32U first_half_chunk_ecc_read = (INT32U)GetBitsFrom16Bytes(odd_tag, 48, 24);
	INT32U second_half_chunk_ecc_read = (INT32U)GetBitsFrom16Bytes(odd_tag, 72, 24);

	INT16U tag_ecc_calc = 0;
	INT32U first_half_chunk_ecc_calc = 0;
	INT32U second_half_chunk_ecc_calc = 0;
	SetBitsInto16Bytes(odd_tag, 16, 16, 0); // clear ecc for itself
	tag_ecc_calc = CalcDChunkTagECC(d_chunk_tag);
	first_half_chunk_ecc_calc = Calc512BytesECC(even_chunk_data);
	second_half_chunk_ecc_calc = Calc512BytesECC(odd_chunk_data);

	if ((tag_ecc_read == tag_ecc_calc)
        && (first_half_chunk_ecc_read == first_half_chunk_ecc_calc)
        && (second_half_chunk_ecc_read == second_half_chunk_ecc_calc))
        tags->eccResult = YAFFS_ECC_RESULT_NO_ERROR;
    else
        tags->eccResult = YAFFS_ECC_RESULT_UNFIXED; // should try to correct tag with yaffs_ECCCorrectOther
}

int DChunk_ReadChunk(struct yaffs_DeviceStruct *dev, int d_chunk_index, __u8 *data, yaffs_ExtendedTags *tags)
{
	INT16U block_index = d_chunk_index / D_CHUNK_NUM_IN_BLOCK;
	INT8U d_chunk_index_in_block = d_chunk_index % D_CHUNK_NUM_IN_BLOCK;
	INT8U even_chunk_index = d_chunk_index_in_block << 1;
	INT8U odd_chunk_index = (d_chunk_index_in_block << 1) + 1;

	INT8U d_chunk_tag[K9F1208_TAG_SIZE << 1];
	INT8U *even_tag = d_chunk_tag;
	INT8U *odd_tag = d_chunk_tag + K9F1208_TAG_SIZE;

	INT8U *d_chunk_data = data;
	if (0 == d_chunk_data)
	{
		d_chunk_data = (INT8U *)malloc(K9F1208_CHUNK_SIZE << 1);
		memset(d_chunk_data, 0, K9F1208_CHUNK_SIZE << 1);
	}

	int even_read_result = K9F1208_ReadChunk(block_index, even_chunk_index, d_chunk_data, even_tag);
	int odd_read_result = K9F1208_ReadChunk(block_index, odd_chunk_index, d_chunk_data + K9F1208_CHUNK_SIZE, odd_tag);

	K9F1208Tag2YaffsTag(even_tag, odd_tag, tags);

	if (tags->chunkUsed) CalcDChunkECC(d_chunk_tag, d_chunk_data, tags);
	else tags->eccResult = YAFFS_ECC_RESULT_NO_ERROR;

	if (0 == data) free(d_chunk_data);

    return (even_read_result | odd_read_result);
}

int DChunk_MarkBadBlock(struct yaffs_DeviceStruct *dev, int block_index)
{
    INT8U even_tag[K9F1208_TAG_SIZE];
    INT8U odd_tag[K9F1208_TAG_SIZE];

	SetBitsInto16Bytes(even_tag, 40, 8, 0);
	SetBitsInto16Bytes(odd_tag, 40, 8, 0);

    int even_write_result = K9F1208_WriteChunk(block_index, 0, 0, even_tag);
    int odd_write_result = K9F1208_WriteChunk(block_index, 1, 0, odd_tag);

	return (even_write_result | odd_write_result);
}

int DChunk_QueryBlock(struct yaffs_DeviceStruct *dev, int block_index, yaffs_BlockState *state, int *seq_num)
{
	INT8U d_chunk_tag[K9F1208_TAG_SIZE << 1];
	INT8U *even_tag = d_chunk_tag;
	INT8U *odd_tag = d_chunk_tag + K9F1208_TAG_SIZE;
	int even_read_result = K9F1208_ReadChunk(block_index, 0, 0, even_tag);
	int odd_read_result = K9F1208_ReadChunk(block_index, 1, 0, odd_tag);

	if (!K9F1208TagIsValid(even_tag) || !K9F1208TagIsValid(odd_tag))
        *state = YAFFS_BLOCK_STATE_DEAD;
    else if (K9F1208TagIsUnused(even_tag) && K9F1208TagIsUnused(odd_tag))
        *state = YAFFS_BLOCK_STATE_EMPTY;
    else
        *state = YAFFS_BLOCK_STATE_NEEDS_SCANNING;

    return (even_read_result | odd_read_result);
}

