/*************************************************
*环形缓冲
*固定环形缓冲用于串口的收发
*使用前先要初始化环形缓冲
**************************************************
*/
#include "includes.h"



//串口环形缓冲初始化
void LoopRAMInit(LoopRAMType *looptype)
{
  looptype = malloc(sizeof(LoopRAMType));
  looptype->LoopDatLength       = 0;//环形缓冲有效数据的长度
  looptype->readpos             = 0;//读取位置
  looptype->writepos            = 0;//写入位置
  free(looptype);
}
//串口环形缓 写入一个byte
void LoopRAMWriteByte(LoopRAMType *looptype, char dat )
{
    looptype->data[looptype->writepos] = dat;
    (looptype->writepos)++;
    looptype->writepos = (looptype->writepos) % LOOP_LENGTH;
    (looptype->LoopDatLength)++;
    if(looptype->LoopDatLength == LOOP_LENGTH)
      { looptype->LoopDatLength = 0;}
}
//串口环形缓冲写入一定长度的数据
void LoopRAMWriteLength(LoopRAMType *looptype,char *dat ,unsigned int length)
{
  while(length != 0)
  {
    LoopRAMWriteByte(looptype,*dat);
    dat++;
    length--;
  }
}
//串口环形缓冲读出一个byte
char LoopRAMReadByte(LoopRAMType *looptype)
{
  char ReadDat = 0;
  if( (looptype->LoopDatLength != 0) )
  {
    ReadDat = looptype->data[looptype->readpos];
    (looptype->readpos++);
    looptype->readpos = looptype->readpos % LOOP_LENGTH;
    (looptype->LoopDatLength)--;
  }
  return ReadDat;
}
//串口环形缓冲读取一定长度的数据，放于‘*p’
void LoopRAMReadLength(LoopRAMType *looptype, char *p, int length)
{
  unsigned int i;
  for(i=0;i<length; i++)
  {
    *(p+i) = LoopRAMReadByte(looptype);
  }
}


