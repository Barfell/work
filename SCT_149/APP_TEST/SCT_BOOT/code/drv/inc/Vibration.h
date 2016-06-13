#ifndef _VIBRATION_H_
#define _VIBRATION_H_

#include "kernel.h"

extern unsigned long            TimeValue;
extern float                    freq;
extern unsigned char            FreqMeasureFinishFlag;

void VibrationIoInit(void);

void SetConnectToTran(void);

void SetConnectToRec(void);

void TranFreq(u32 freq);

void CaptureOn(void);

void CaptureOff(void);

#endif