#ifndef RAIN_H_
#define RAIN_H_

#define RAIN_COUNT_ADDR         1       //存放雨量数量的地址
#define RAIN_CONTENT_ADDR       5000    //存放雨量数据的起始地址


void RainInit(void);
void SetRainNum(unsigned long num);
unsigned long GetRainNum(void);
//2016-04-26-19:24:55|(20byte)
//雨量中断时候存储数据
void StoreRain(void);
//读取指定条数的雨量数据
//DST为开始读取的地址
void ReadRain(unsigned long Dst, unsigned char *buf, unsigned char num);

#endif