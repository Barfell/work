#ifndef __LOOPRAMFUNC_H_
#define __LOOPRAMFUNC_H_


#define LOOP_LENGTH 150


typedef struct loopram{
  unsigned int LoopDatLength;//���λ����ڲ���Ч���ݳ���
  unsigned int readpos;//��ȡ��λ��
  unsigned int writepos;//д���λ��
  char data[LOOP_LENGTH];//��������
} LoopRAMType;


void LoopRAMInit(void);
void LoopRAMWriteByte(char dat );
void LoopRAMWriteLength(char *dat ,unsigned int length);
char LoopRAMReadByte(void);
void LoopRAMReadLength( char *p, int length);

#endif
