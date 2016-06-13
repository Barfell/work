#ifndef __LOOPRAMFUNC_H_
#define __LOOPRAMFUNC_H_


#define LOOP_LENGTH 300 /*���λ����С*/


typedef struct loopram{
  unsigned int LoopDatLength;//���λ����ڲ���Ч���ݳ���
  unsigned int readpos; //��ȡ��λ��
  unsigned int writepos;//д���λ��
  char data[LOOP_LENGTH];//��������
} LoopRAMType;


void LoopRAMInit(LoopRAMType *looptype);
void LoopRAMWriteByte(LoopRAMType *looptype,char dat );
void LoopRAMWriteLength(LoopRAMType *looptype,char *dat ,unsigned int length);
char LoopRAMReadByte(LoopRAMType *looptype);
void LoopRAMReadLength(LoopRAMType *looptype, char *p, int length);

#endif
