#ifndef SHELL_H
#define SHELL_H
#include "TypeCpu.h"
#include "Message.h"

void InitShell();
BOOL SendToShell(INT8U *data, INT16U len);
	
#endif

