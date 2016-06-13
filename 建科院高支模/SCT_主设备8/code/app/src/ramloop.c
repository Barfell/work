/*************************************************
*���λ���
*�̶����λ������ڴ��ڵ��շ�
*ʹ��ǰ��Ҫ��ʼ�����λ���
**************************************************
*/
#include "includes.h"



//���ڻ��λ����ʼ��
void LoopRAMInit(LoopRAMType *looptype)
{
  looptype = malloc(sizeof(LoopRAMType));
  looptype->LoopDatLength       = 0;//���λ�����Ч���ݵĳ���
  looptype->readpos             = 0;//��ȡλ��
  looptype->writepos            = 0;//д��λ��
  free(looptype);
}
//���ڻ��λ� д��һ��byte
void LoopRAMWriteByte(LoopRAMType *looptype, char dat )
{
    looptype->data[looptype->writepos] = dat;
    (looptype->writepos)++;
    looptype->writepos = (looptype->writepos) % LOOP_LENGTH;
    (looptype->LoopDatLength)++;
    if(looptype->LoopDatLength == LOOP_LENGTH)
      { looptype->LoopDatLength = 0;}
}
//���ڻ��λ���д��һ�����ȵ�����
void LoopRAMWriteLength(LoopRAMType *looptype,char *dat ,unsigned int length)
{
  while(length != 0)
  {
    LoopRAMWriteByte(looptype,*dat);
    dat++;
    length--;
  }
}
//���ڻ��λ������һ��byte
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
//���ڻ��λ����ȡһ�����ȵ����ݣ����ڡ�*p��
void LoopRAMReadLength(LoopRAMType *looptype, char *p, int length)
{
  unsigned int i;
  for(i=0;i<length; i++)
  {
    *(p+i) = LoopRAMReadByte(looptype);
  }
}


