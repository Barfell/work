#ifndef _LTC2402_H_
#define _LTC2402_H_


extern double g_dRes;
extern double g_dTem;

unsigned char LTC2402_TEST_EOC(void);

//初始化
void LTC2402Init(void);

//获取电阻值
double LTC2402_GetResistance(void);


//计算温度
double GetNTCTemperature(double NTCRes);

#endif

