#ifndef __FEQMEAUREMENT_H
#define __FEQMEAUREMENT_H

#include "kernal.h"

void TranPulse(unsigned int freq,unsigned char num);
void OutPutFreqSet(unsigned int freq);
void FreqModuleInit(void);
double CalDisplacement(double Freq,double T);
double Measure(void);
double GetFreq(unsigned char ch);

extern double OnFreq;
extern unsigned char measureflag;
extern unsigned char PulseOnFlag;
#endif






