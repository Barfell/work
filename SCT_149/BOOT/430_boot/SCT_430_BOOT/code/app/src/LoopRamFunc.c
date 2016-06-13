/*************************************************
*���λ���
*�̶����λ������ڴ��ڵ��շ�
*ʹ��ǰ��Ҫ��ʼ�����λ���
**************************************************
*/
#include "kernel.h"
#include "LoopRamFunc.h"


LoopRAMType Uartloop;

//���ڻ��λ����ʼ��
void LoopRAMInit(void)
{
  Uartloop.LoopDatLength = 0;//���λ�����Ч���ݵĳ���
  Uartloop.readpos = 0;//��ȡλ��
  Uartloop.writepos = 0;//д��λ��
}
//���ڻ��λ� д��һ��byte
void LoopRAMWriteByte(char dat )
{
    Uartloop.data[Uartloop.writepos] = dat;
    Uartloop.writepos++;
    Uartloop.writepos = Uartloop.writepos % LOOP_LENGTH;
    Uartloop.LoopDatLength++;
    if(Uartloop.LoopDatLength == LOOP_LENGTH)
      { Uartloop.LoopDatLength = 0;}
}
//���ڻ��λ���д��һ�����ȵ�����
void LoopRAMWriteLength(char *dat ,unsigned int length)
{
  while(length != 0)
  {
    LoopRAMWriteByte(*dat);
    dat++;
    length--;
  }
}
//���ڻ��λ������һ��byte
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
//���ڻ��λ����ȡһ�����ȵ����ݣ����ڡ�*p��
void LoopRAMReadLength( char *p, int length)
{
  unsigned int i;
  for(i=0;i<length; i++)
  {
    *(p+i) = LoopRAMReadByte();
  }
}


