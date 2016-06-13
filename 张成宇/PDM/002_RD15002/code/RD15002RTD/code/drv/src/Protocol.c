#include "Protocol.h"

VOID Init(PQueueInfo pQueueInfo)
{
	pQueueInfo->Front = 0;
	pQueueInfo->Rear = 0;
}
QueueLengthType GetQueueLength(PQueueInfo pQueueInfo)
{
	return (pQueueInfo->Rear - pQueueInfo->Front + MAXSIZE) % MAXSIZE;
}
BOOL AddQueue(PQueueInfo pQueueInfo, QueueDataType qValue)
{
    BOOL bState;
	if((pQueueInfo->Rear + 1) % MAXSIZE == pQueueInfo->Front)
	{
		bState = FALSE;
	}
    else
    {
    	pQueueInfo->queuedata[pQueueInfo->Rear] = qValue;
    	pQueueInfo->Rear = (pQueueInfo->Rear + 1) % MAXSIZE;
    	bState = TRUE;
    }
    return bState;
}
BOOL DeleteQueue(PQueueInfo pQueueInfo, QueueDataType *pqValue)
{
    BOOL bState;
	if(pQueueInfo->Front == pQueueInfo->Rear)
	{
		bState = FALSE;
	}
    else
    {
    	*pqValue = pQueueInfo->queuedata[pQueueInfo->Front];
    	pQueueInfo->Front = (pQueueInfo->Front + 1) % MAXSIZE;
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
