#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include "tool.h"
#define MAXSIZE	1030

typedef U8 QueueDataType;
typedef U16 QueueLengthType;

typedef struct _tagQueueInfo
{
	QueueDataType queuedata[MAXSIZE];
	QueueLengthType Front;
	QueueLengthType Rear;
}CQueueInfo, *PQueueInfo;

VOID Init(PQueueInfo pQueueInfo);
BOOL AddQueue(PQueueInfo pQueueInfo, QueueDataType qValue);
BOOL DeleteQueue(PQueueInfo pQueueInfo, QueueDataType *pqValue);
QueueLengthType GetQueueLength(PQueueInfo pQueueInfo);
U32 SoftGenCrc32(U32* puData, U32 uSize);
U32 HardGenCrc32(U32* puData, U32 uSize);




#endif

