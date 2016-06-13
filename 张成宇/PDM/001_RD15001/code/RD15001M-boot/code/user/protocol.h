#ifndef __PROTOCOL_H
#define __PROTOCOL_H	

#include "sys.h"

//#define QUEUEUNIT     0x200  //512
//#define MAXQUEUESIZE        0x2000  //8K
#define SD_COUNT                4//根QUEUEUNIT定，如果是0x200，那就是1
#define QUEUEUNIT     0x800  //2k
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
BOOL AddQueue(U8 *pDestBuf, U8 *pSrcBuf, PQueueInfo pQueueInfo, QueueDataType OffSet, U16 UsartRxCount);
VOID GetQueue(U8 *pBuf, U8 *pSrcBuf, PQueueInfo pQueueInfo, QueueDataType OffSet);
BOOL DeleteQueue(PQueueInfo pQueueInfo);

#endif 















