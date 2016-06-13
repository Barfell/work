#ifndef _VIBRATION_H_
#define _VIBRATION_H_

extern unsigned long            TimeValue;
extern float                    freq;
extern unsigned char            FreqMeasureFinishFlag;

void VibrationIoInit(void);

void SetConnectToTran(void);

void SetConnectToRec(void);

void FAN3122IoInit(void);

void FAN3122_OFF(void);

void FAN3122_ON(void);;

void TranFreq(int freq);

void CaptureOn(void);

void CaptureOff(void);

#endif