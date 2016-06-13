#ifndef _SST25VF064_H
#define _SST25VF064_H

//��ʼ��ADC������
void SST25VF064Init(void);
unsigned char SST25VF064WriteReadByte(unsigned char cmd);
void SST25VF064Unselect(void);
void SST25VF064Select(void);
void SST25VF064Reset(void);
void SST25VF064SectorErase(unsigned long Addr);
void SST25VF064BlockErase(unsigned long Addr);
void SST25VF064BlockOPErase(unsigned long Addr);
void SST25VF064ChipErase(unsigned long Addr);
//1:unbusy
//0:busy
unsigned char SST25VF064BusySatue(void);
//��ĳһ����ַд��һ������
void SST25VF064ProgramByte(unsigned long Addr,unsigned char dat);
//��ĳһ����ַ��ʼ��д��һ�����ȵ���������
void SST25VF064ProgramLength(unsigned long Addr,unsigned char *dat,unsigned long length);
//��ȡĳһ��ַ��һ���ֽ�
unsigned char SST25VF064FlashReadByte(unsigned long Addr);
//��ȡһ�����ȵ�buff
void SST25VF064FlashRead(unsigned long Addr,unsigned char *pbuff,unsigned long length);


#endif



