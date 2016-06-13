/*************************************************
*环形缓冲
*固定环形缓冲用于串口的收发
*使用前先要初始化环形缓冲
**************************************************
*/
#include "kernel.h"
#include "LoopRamFunc.h"


LoopRAMType Uartloop;

//串口环形缓冲初始化
void LoopRAMInit(void)
{
  Uartloop.LoopDatLength = 0;//环形缓冲有效数据的长度
  Uartloop.readpos = 0;//读取位置
  Uartloop.writepos = 0;//写入位置
}
//串口环形缓 写入一个byte
void LoopRAMWriteByte(char dat )
{
    Uartloop.data[Uartloop.writepos] = dat;
    Uartloop.writepos++;
    Uartloop.writepos = Uartloop.writepos % LOOP_LENGTH;
    Uartloop.LoopDatLength++;
    if(Uartloop.LoopDatLength == LOOP_LENGTH)
      { Uartloop.LoopDatLength = 0;}
}
//串口环形缓冲写入一定长度的数据
void LoopRAMWriteLength(char *dat ,unsigned int length)
{
  while(length != 0)
  {
    LoopRAMWriteByte(*dat);
    dat++;
    length--;
  }
}
//串口环形缓冲读出一个byte
char LoopRAMReadByte(void)
{
  char ReadDat = 0;
  if( (Uartloop.LoopDatLength != 0) )
  {
    ReadDat = Uartloop.data[Uartloop.readpos];
    Uartloop.readpos++;
    Uartloop.readpos = Uartloop.readpos % LOOP_LENGTH;
    Uartloop.LoopDatLength--;
  }
  return ReadDat;
}
//串口环形缓冲读取一定长度的数据，放于‘*p’
void LoopRAMReadLength( char *p, int length)
{
  unsigned int i;
  for(i=0;i<length; i++)
  {
    *(p+i) = LoopRAMReadByte();
  }
}


