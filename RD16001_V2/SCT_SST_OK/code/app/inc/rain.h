#ifndef RAIN_H_
#define RAIN_H_

#define RAIN_COUNT_ADDR         1       //������������ĵ�ַ
#define RAIN_CONTENT_ADDR       5000    //����������ݵ���ʼ��ַ


void RainInit(void);
void SetRainNum(unsigned long num);
unsigned long GetRainNum(void);
//2016-04-26-19:24:55|(20byte)
//�����ж�ʱ��洢����
void StoreRain(void);
//��ȡָ����������������
//DSTΪ��ʼ��ȡ�ĵ�ַ
void ReadRain(unsigned long Dst, unsigned char *buf, unsigned char num);

#endif