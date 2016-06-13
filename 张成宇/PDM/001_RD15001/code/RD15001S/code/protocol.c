#include "protocol.h"

void Init(PQueueInfo pQueueInfo)
{
	pQueueInfo->u8Front = 0;
	pQueueInfo->u8Rear = 0;
}
QueueDataType GetQueueLength(PQueueInfo pQueueInfo)
{
	return (pQueueInfo->u8Rear - pQueueInfo->u8Front + MAXSIZE) % MAXSIZE;
}
BOOL AddQueue(PQueueInfo pQueueInfo, QueueDataType qValue)
{
    BOOL xdata bState;
	if((pQueueInfo->u8Rear + 1) % MAXSIZE == pQueueInfo->u8Front)
	{
		bState = FALSE;
	}
    else
    {
    	pQueueInfo->queuedata[pQueueInfo->u8Rear] = qValue;
    	pQueueInfo->u8Rear = (pQueueInfo->u8Rear + 1) % MAXSIZE;
    	bState = TRUE;
    }
    return bState;
}
BOOL DeleteQueue(PQueueInfo pQueueInfo, QueueDataType *pqValue)
{
    BOOL xdata bState;
	if(pQueueInfo->u8Front == pQueueInfo->u8Rear)
	{
		bState = FALSE;
	}
    else
    {
    	*pqValue = pQueueInfo->queuedata[pQueueInfo->u8Front];
    	pQueueInfo->u8Front = (pQueueInfo->u8Front + 1) % MAXSIZE;
        bState = TRUE;
    }
	return bState;
}