#include "protocol.h"

VOID ResetQueue(PQueueInfo pQueueInfo)
{
    pQueueInfo->Front = 0;
    pQueueInfo->Rear = 0;
}

QueueDataType GetQueueLength(PQueueInfo pQueueInfo)
{
    QueueDataType Ret;
	Ret = (pQueueInfo->Rear - pQueueInfo->Front + MAXQUEUESIZE) % MAXQUEUESIZE;
    return Ret;
}

BOOL AddQueue(U8 *pDestBuf, U8 *pSrcBuf, PQueueInfo pQueueInfo, QueueDataType OffSet, U16 UsartRxCount)
{
    BOOL bState = TRUE;
    U16 u16Cnt;
	if(((pQueueInfo->Rear + OffSet) % MAXQUEUESIZE >= pQueueInfo->Front) && ((pQueueInfo->Rear + OffSet) > MAXQUEUESIZE))
	{
        
		bState = FALSE;
        //EnterException(ERR_ADD_FAIL);
	}
    else
    {
        u16Cnt = MAXQUEUESIZE - pQueueInfo->Rear;
        if(UsartRxCount > u16Cnt)
        {
            
            memcpy(pDestBuf + pQueueInfo->Rear, pSrcBuf, u16Cnt);
            memcpy(pDestBuf, pSrcBuf + u16Cnt, OffSet - u16Cnt);
        }
        else
        {
            memcpy(pDestBuf + pQueueInfo->Rear, pSrcBuf, UsartRxCount);
        }
    	pQueueInfo->Rear = (pQueueInfo->Rear + OffSet) % MAXQUEUESIZE;
        pQueueInfo->AddCount = pQueueInfo->AddCount + OffSet;
    	bState = TRUE;
    }
    return bState;
}

VOID GetQueue(U8 *pBuf, U8 *pSrcBuf, PQueueInfo pQueueInfo, QueueDataType OffSet)
{
    U16 u16Cnt;
    u16Cnt = MAXQUEUESIZE - pQueueInfo->Front;
                    
    if(u16Cnt < OffSet)
    {
        memcpy(pBuf, pSrcBuf + pQueueInfo->Front, u16Cnt);
        memcpy(pBuf + u16Cnt, pSrcBuf, OffSet - u16Cnt);
        
    }
    else
    {
        memcpy(pBuf, pSrcBuf + pQueueInfo->Front, OffSet);
    }
}


BOOL DeleteQueue(PQueueInfo pQueueInfo)
{
    BOOL bState;
	if(pQueueInfo->Front == pQueueInfo->Rear)
	{
		bState = FALSE;
	}
    else
    {
    	pQueueInfo->Front = (pQueueInfo->Front + QUEUEUNIT) % MAXQUEUESIZE;
        bState = TRUE;
    }
	return bState;
}
