#ifndef _S485_H
#define _S485_H

void Init485(void);
unsigned char Get485(char *device, char *dat485);
unsigned char GetTilt(char *device, char *dat485);
#endif