#ifndef _485_H_
#define _485_H_
#include "kernal.h"

extern char SENSOR_HEAD[];

U8 CalcCheckSum(U8* pSrcData, U16 wDataLen);

VOID Handle485WrapperProc(CHAR *pBuf, U16 u16Length);

VOID DT485_Init(VOID);

void DT485_Get(unsigned char *SensorType, unsigned char *SensorAddr, unsigned char *pBuf, U16 *pLength);
#endif

