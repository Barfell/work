#include "Message.h"
#include <stdlib.h>
#include <string.h>

Message *NewMessage(INT32U id, INT8U *data, INT16U len)
{
	Message *msg = (Message *)malloc(sizeof(Message));
	msg->msg_id = id;
	msg->len = len;
	msg->data = 0;

	if (msg->len != 0)
	{
		msg->data = (INT8U *)malloc(len);
		memcpy(msg->data, data, len);
	}

	return msg;
}

void DeleteMessage(Message *msg)
{
	if (0 == msg) return;

	if (msg->len != 0)
	{
		free(msg->data);
	}

	free(msg);
}

