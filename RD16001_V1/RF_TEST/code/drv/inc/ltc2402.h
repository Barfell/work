#ifndef _LTC2402_H_
#define _LTC2402_H_


extern double g_dRes;
extern double g_dTem;

unsigned char LTC2402_TEST_EOC(void);

//��ʼ��
void LTC2402Init(void);

//��ȡ����ֵ
double LTC2402_GetResistance(void);


//�����¶�
double GetNTCTemperature(double NTCRes);

#endif

