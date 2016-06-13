#ifndef __LOOPRAMFUNC_H_
#define __LOOPRAMFUNC_H_


#define LOOP_LENGTH 300 /*环形缓冲大小*/


typedef struct loopram{
  unsigned int LoopDatLength;//环形缓冲内部有效数据长度
  unsigned int readpos; //读取的位置
  unsigned int writepos;//写入的位置
  char data[LOOP_LENGTH];//具体数据
} LoopRAMType;


void LoopRAMInit(LoopRAMType *looptype);
void LoopRAMWriteByte(LoopRAMType *looptype,char dat );
void LoopRAMWriteLength(LoopRAMType *looptype,char *dat ,unsigned int length);
char LoopRAMReadByte(LoopRAMType *looptype);
void LoopRAMReadLength(LoopRAMType *looptype, char *p, int length);

#endif
