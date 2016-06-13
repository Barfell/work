#ifndef __BSP_SST25VF064_H
#define __BSP_SST25VF064_H

//��ʼ��ADC������
void SST25VF064Init(void);
unsigned char SST25VF064WriteReadByte(unsigned char cmd);
void SST25VF064Unselect(void);
void SST25VF064Select(void);
void SST25VF064Reset(void);
void SST25VF064SectorErase(unsigned int Addr);
void SST25VF064BlockErase(unsigned int Addr);
void SST25VF064BlockOPErase(unsigned int Addr);
void SST25VF064ChipErase(unsigned int Addr);
//1:unbusy
//0:busy
unsigned char SST25VF064BusySatue(void);
//��ĳһ����ַд��һ������
void SST25VF064ProgramByte(unsigned int Addr,unsigned char dat);
//��ĳһ����ַ��ʼ��д��һ�����ȵ���������
void SST25VF064ProgramLength(unsigned int Addr,unsigned char *dat,unsigned int length);
//��ȡĳһ��ַ��һ���ֽ�
unsigned char SST25VF064FlashReadByte(unsigned int Addr);
//��ȡһ�����ȵ�buff
void SST25VF064FlashRead(unsigned int Addr,unsigned char *pbuff,unsigned int length);


#endif



