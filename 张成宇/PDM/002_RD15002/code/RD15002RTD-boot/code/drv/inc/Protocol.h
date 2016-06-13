#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_
#include "kernal.h"

#define MAXSIZE_A	2057
#define MAXSIZE_B	1500


typedef U8 QueueDataType;
typedef U16 QueueLengthType;

typedef struct _tagQueueInfo
{
	QueueLengthType Front;
	QueueLengthType Rear;
	U8 SizeType;
}CQueueInfo, *PQueueInfo;

enum
{
	QUEUETYPE_A,
	QUEUETYPE_B,
	
};

VOID Init(PQueueInfo pQueueInfo);
BOOL AddQueue(PQueueInfo pQueueInfo, QueueDataType qValue, QueueDataType *pBuf);
BOOL DeleteQueue(PQueueInfo pQueueInfo, QueueDataType *pqValue, QueueDataType *pBuf);
QueueLengthType GetQueueLength(PQueueInfo pQueueInfo);
U32 SoftGenCrc32(U32* puData, U32 uSize);
U32 HardGenCrc32(U32* puData, U32 uSize);




#endif

