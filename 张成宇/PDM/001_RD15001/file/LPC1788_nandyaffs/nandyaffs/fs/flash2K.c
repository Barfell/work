#include "yaffs_flashif2.h"
#include "yaffs_packedtags2.h"


#include "nandflash_k9f2g08u0x.h"
#include "debug_frmwrk.h"

// blockNumber 0~xxxx
int yflash2_EraseBlockInNAND(yaffs_Device *dev, int blockNumber)
{
	if((blockNumber < dev->startBlock)
     ||(blockNumber > dev->endBlock))
	{	 
		return  YAFFS_FAIL;
	}
	//��Ӧ���ǿ��
	if(Nand_EraseBlockLarge(blockNumber))
	{// ���ط�0ֵ
		return YAFFS_OK;
    }

	return  YAFFS_FAIL;
}
// chunkInNAND = page  0~xxxx
int yflash2_WriteChunkWithTagsToNAND(yaffs_Device *dev,int chunkInNAND,const __u8 *data, const yaffs_ExtendedTags *tags)
{
    yaffs_PackedTags2  *pkt;
    __u8  tmp[64]={'\0'};
    int i;

    //put_str_("yaffs write9");
    //_DBH32_(chunkInNAND);
	pkt=(yaffs_PackedTags2*)tmp;
	yaffs_PackTags2(pkt,tags);
    
    i = Nand_WritePageWithSpare2048(chunkInNAND,data,tmp);// ����1ʱ��ʾд�ɹ�
    
	if(i)
	{
		return  YAFFS_OK;
	}	
 
	return YAFFS_FAIL;
}
// chunkInNAND = page  0~xxxx
int yflash2_ReadChunkWithTagsFromNAND(yaffs_Device *dev,int chunkInNAND, __u8 *data, yaffs_ExtendedTags *tags)
{
    yaffs_PackedTags2   *upt;
    __u8  tmp[64]={'\0'};
    int i;
    
    i = Nand_ReadPageWithSpare2048(chunkInNAND,data,tmp);// ����1ʱ��ʾ���ɹ�

    upt = (yaffs_PackedTags2*)tmp;

    if(i)
	{
		yaffs_UnpackTags2(tags,upt);
        
		return  YAFFS_OK;
	}
	
	return YAFFS_FAIL;
}
int yflash2_GetNumberOfBlocks()
{
    return 1024;
}
int yflash2_InitialiseNAND(yaffs_Device *dev)
{

	return YAFFS_OK;
}
int yflash2_MarkNANDBlockBad(struct yaffs_DeviceStruct *dev, int blockNo)
{

	return YAFFS_OK;
}
//�������û�иı�  ��ԭ���Ĵ�����ͬ
int yflash2_QueryNANDBlock(struct yaffs_DeviceStruct *dev, int blockNo, yaffs_BlockState *state, __u32 *sequenceNumber)
{
	yaffs_ExtendedTags tags;
	int chunkNo;
    
	*sequenceNumber = 0;
	
	chunkNo = blockNo * (dev->nChunksPerBlock);
 
	yflash2_ReadChunkWithTagsFromNAND(dev,chunkNo,NULL,&tags);
	if(tags.blockBad)
	{
		*state = YAFFS_BLOCK_STATE_DEAD;
	}
	else if(!tags.chunkUsed)
	{
		*state = YAFFS_BLOCK_STATE_EMPTY;
	}
	else if(tags.chunkUsed)
	{
		*state = YAFFS_BLOCK_STATE_NEEDS_SCANNING;
		*sequenceNumber = tags.sequenceNumber;
	}
	return YAFFS_OK;	
}
