#ifndef __ADC_H
#define __ADC_H	 
#include "kernal.h"

VOID AdcInit(VOID);
U16 GetAdc(U8 u8Channel);
U16 GetAdcAverage(U8 u8Channel, U8 u8Times);

#define ADC_CHANNEL		ADC_Channel_1
#endif

















