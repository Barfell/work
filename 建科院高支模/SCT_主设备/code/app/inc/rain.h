#ifndef RAIN_H_
#define RAIN_H_

void RainInit(void);
void StoreRain(void);
void WriteRainToFlash(unsigned long addr, char* rain);
unsigned int GetRainNum(void);

#endif