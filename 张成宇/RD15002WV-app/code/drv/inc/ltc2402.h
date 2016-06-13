#ifndef __LTC2402_H
#define __LTC2402_H	 
#include "kernal.h"

#define 	LTC2402_SPI		SPI1



void LTC2402Init(void);
u8 LTC2402_ReadByte(void);
u8 LTC2402_TEST_EOC(void);
void LTC2402_SWitchInit(void);
void LTC2402_SwitchChannel(u8 u8channel);

double LTC2402_GetResistance(void);
double LTC2402_GetAverageResistance(void);
double GetPTTemperature(double PTRes);
double GetNTCTemperature(double NTCRes);
#endif


