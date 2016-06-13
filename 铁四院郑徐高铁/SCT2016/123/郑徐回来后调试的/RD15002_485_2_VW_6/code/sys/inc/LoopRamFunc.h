#ifndef __LOOPRAMFUNC_H_
#define __LOOPRAMFUNC_H_


#define LOOP_LENGTH 1024


typedef struct loopram{
  unsigned int LoopDatLength;//环形缓冲内部有效数据长度
  unsigned int readpos;//读取的位置
  unsigned int writepos;//写入的位置
  char data[LOOP_LENGTH];//具体数据
} LoopRAMType;


void LoopRAMInit(void);
void LoopRAMWriteByte(unsigned char dat );
void LoopRAMWriteLength(unsigned char *dat ,unsigned int length);
char LoopRAMReadByte(void);
void LoopRAMReadLength( unsigned char *p, int length);

#endif
