#include "TypeCpu.h"
#include "ucos_ii.h"
#include <stdio.h>
#include <stdlib.h>
#include "Message.h"
#include "Uart.h"

static OS_EVENT *shell_q = 0;
static char q_err = 0;

static void ParseInput(INT8U *data, INT16U len)
{
	INT16U i = 0;

	for (; i < len; ++i)
	{
		WriteChar((char)data[i]);
	}
}

static void ShellTask(void *parameter)
{
	printf("Shell task is running......\n");

	while (1)
	{
		Message *msg = 0;
		msg = (Message *)OSQPend(shell_q, 0, &q_err);
		if (OS_NO_ERR != q_err) continue;
		ParseInput(msg->data, msg->len);
		DeleteMessage(msg);
	}
}

void InitShell()
{
	INT8U *stack = (INT8U *)malloc(0x1000) + 0x1000;
	void **q_buff = (void **)malloc(64 * sizeof(INT32U *));
	shell_q = OSQCreate(q_buff, 64);
	OSTaskCreate(ShellTask, (void *)0, (OS_STK *)stack, 9);
}

BOOL SendToShell(INT8U *data, INT16U len)
{
	Message *msg = NewMessage(0, data, len);
	INT8U result = OSQPost(shell_q, (void *)msg);

	if (OS_NO_ERR != result)
	{
		printf("failt to send msg to shell!\n");
		DeleteMessage(msg);
	}

	return (OS_NO_ERR == result) ? TRUE : FALSE;
}

