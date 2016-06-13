#ifndef __PROTOCOL_H
#define __PROTOCOL_H	

#include "kernal.h" 


#define SD_COUNT                4//根QUEUEUNIT定，如果是0x200，那就是1
#define QUEUEUNIT     0x1000  //4k
#define MAXQUEUESIZE        0x2800  //10K



typedef U32 QueueDataType; 

typedef struct _tagQueueInfo
{
	QueueDataType Front;
	QueueDataType Rear;
    QueueDataType AddCount;
    QueueDataType WriteCount;
    QueueDataType ReadCount;
    
}CQueueInfo, *PQueueInfo;

VOID ResetQueue(PQueueInfo pQueueInfo);
QueueDataType GetQueueLength(PQueueInfo pQueueInfo);
VOID AddQueue(U8 *pDestBuf, U8 *pSrcBuf, PQueueInfo pQueueInfo, U16 UsartRxCount);
VOID GetQueue(U8 *pBuf, U8 *pSrcBuf, PQueueInfo pQueueInfo, QueueDataType OffSet);
BOOL DeleteQueue(PQueueInfo pQueueInfo);

#endif 















