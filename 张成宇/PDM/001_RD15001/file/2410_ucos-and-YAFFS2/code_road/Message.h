#ifndef MESSAGE_H
#define MESSAGE_H
#include "TypeCpu.h"

typedef struct
{
	INT32U msg_id;
	INT8U *data;
	INT16U len;
}Message;

Message *NewMessage(INT32U id, INT8U *data, INT16U len);
void DeleteMessage(Message *msg);

#endif

