#include "Protocol.h"

VOID Init(PQueueInfo pQueueInfo)
{
	pQueueInfo->Front = 0;
	pQueueInfo->Rear = 0;
}
QueueLengthType GetQueueLength(PQueueInfo pQueueInfo)
{
	U16 u16Size;
	
	if(pQueueInfo->SizeType == QUEUETYPE_A)
	{
		u16Size = MAXSIZE_A;
	}
	else
	{
		u16Size = MAXSIZE_B;
	}
	return (pQueueInfo->Rear - pQueueInfo->Front + u16Size) % u16Size;
}
BOOL AddQueue(PQueueInfo pQueueInfo, QueueDataType qValue, QueueDataType *pBuf)
{
    BOOL bState;
	U16 u16Size;
	
	if(pQueueInfo->SizeType == QUEUETYPE_A)
	{
		u16Size = MAXSIZE_A;
	}
	else
	{
		u16Size = MAXSIZE_B;
	}
	
	if((pQueueInfo->Rear + 1) % u16Size == pQueueInfo->Front)
	{
		bState = FALSE;
	}
    else
    {
    	pBuf[pQueueInfo->Rear] = qValue;
    	pQueueInfo->Rear = (pQueueInfo->Rear + 1) % u16Size;
    	bState = TRUE;
    }
    return bState;
}
BOOL DeleteQueue(PQueueInfo pQueueInfo, QueueDataType *pqValue, QueueDataType *pBuf)
{
    BOOL bState;
	U16 u16Size;
	
	if(pQueueInfo->SizeType == QUEUETYPE_A)
	{
		u16Size = MAXSIZE_A;
	}
	else
	{
		u16Size = MAXSIZE_B;
	}
	
	if(pQueueInfo->Front == pQueueInfo->Rear)
	{
		bState = FALSE;
	}
    else
    {
    	*pqValue = pBuf[pQueueInfo->Front];
    	pQueueInfo->Front = (pQueueInfo->Front + 1) % u16Size;
        bState = TRUE;
    }
	return bState;
}

U32 SoftGenCrc32(U32* puData, U32 uSize) 
{ 
	U32 crc = 0xFFFFFFFF;
	U32 i=0,j=0,temp; 
	for(i=0;i<uSize;i++)
	{ 
		temp = puData[i]; 
		for(j=0;j<32;j++)
		{ 
			if( (crc ^ temp) & 0x80000000 )
			{ 
				crc = 0x04C11DB7 ^ (crc<<1); 
			}
			else
			{ 
				crc <<=1; 
			} 
			temp<<=1; 
		} 
	}
	
	return crc; 
} 

U32 HardGenCrc32(U32* puData, U32 uSize)
{
	CRC_ResetDR();
	return CRC_CalcBlockCRC((U32 *)puData, (U32)uSize);
}
