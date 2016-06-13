#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "C8051F340.h"
#include <intrins.h>
#include <absacc.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define crystal 12000000


//-------------------------------------------------------//
typedef unsigned char uchar;
typedef unsigned int uint;	
typedef unsigned long int ulong; 
//-------------------------------------------------------//


//--------------------------------------------------------//
//void Init_Device();
//void DelayUs(unsigned char t);
//void DelayMs(unsigned int t);
//U32 GetTickCount(void);
void EnterException(unsigned char ucErrCode);

//unsigned char Read_SensorData(void);
//unsigned char Am2305_Read();
//
//void StartRfid(void);

 
#endif