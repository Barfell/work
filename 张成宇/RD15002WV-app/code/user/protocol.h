#ifndef __PROTOCOL_H
#define __PROTOCOL_H	

#include "kernal.h" 


#define QUEUEUNIT     0x800  //2k
#define MAXQUEUESIZE        0x1800  //6K



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
BOOL DeleteQueue(PQueueInfo pQueueInfo, U8 *pBuf, QueueDataType *pqValue);
BOOL DeleteQueueEx(PQueueInfo pQueueInfo);
#endif 















