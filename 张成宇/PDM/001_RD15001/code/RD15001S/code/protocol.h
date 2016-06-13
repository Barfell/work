#ifndef __PROTOCOL_H
#define __PROTOCOL_H	

#include "app_rfid.h" 

//#define QUEUEUNIT     		100  
//#define MAXQUEUESIZE        200  

#define MAXSIZE	200

typedef U8 QueueDataType;

typedef struct _tagQueueInfo//for IIC data
{
	QueueDataType queuedata[MAXSIZE];
	QueueDataType u8Front;
	QueueDataType u8Rear;
}CQueueInfo, *PQueueInfo;

void Init(PQueueInfo pQueueInfo);//for IIC data
BOOL AddQueue(PQueueInfo pQueueInfo, QueueDataType qValue);
QueueDataType GetQueueLength(PQueueInfo pQueueInfo);
BOOL DeleteQueue(PQueueInfo pQueueInfo, QueueDataType *pqValue);

#endif 















