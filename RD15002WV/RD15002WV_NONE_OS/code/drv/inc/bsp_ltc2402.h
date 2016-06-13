#ifndef __LTC2402_H
#define __LTC2402_H

void LTC2402Init(void);
unsigned char LTC2402_ReadByte(void);
unsigned char LTC2402_TEST_EOC(void);
double LTC2402_GetResistance(unsigned char channel);
double GetNTCTemperature(double NTCRes);

#endif

