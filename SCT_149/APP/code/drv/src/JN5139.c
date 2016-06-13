#include "JN5139.h"
#include "msp430f149_uart.h"
#include "kernel.h"


JNRAMType JNLoopRam;



/*************************************JN5139�Ļ��λ��庯��*******************************************/
//���ڻ��λ����ʼ��
void JNRAMInit(void)
{
  JNLoopRam.JNDatLength = 0;//���λ�����Ч���ݵĳ���
  JNLoopRam.readpos = 0;//��ȡλ��
  JNLoopRam.writepos = 0;//д��λ��
}
//���ڻ��λ� д��һ��byte
void JNRAMWriteByte(char dat )
{
    JNLoopRam.data[JNLoopRam.writepos] = dat;
    JNLoopRam.writepos++;
    JNLoopRam.writepos = JNLoopRam.writepos % JN_LENGTH;
    JNLoopRam.JNDatLength++;
    if(JNLoopRam.JNDatLength == JN_LENGTH)
      { JNLoopRam.JNDatLength = 0;}
}
//���ڻ��λ���д��һ�����ȵ�����
void JNRAMWriteLength(char *dat ,unsigned int length)
{
  while(length != 0)
  {
    JNRAMWriteByte(*dat);
    dat++;
    length--;
  }
}
//���ڻ��λ������һ��byte
char JNRAMReadByte(void)
{
  char ReadDat = 0;
  if( (JNLoopRam.JNDatLength != 0) )
  {
    ReadDat = JNLoopRam.data[JNLoopRam.readpos];
    JNLoopRam.readpos++;
    JNLoopRam.readpos = JNLoopRam.readpos % JN_LENGTH;
    JNLoopRam.JNDatLength--;
  }
  return ReadDat;
}
//���ڻ��λ����ȡһ�����ȵ����ݣ����ڡ�*p��
void JNRAMReadLength( char *p, int length)
{
  unsigned int i;
  for(i=0;i<length; i++)
  {
    *(p+i) = JNRAMReadByte();
  }
}
/*************************************JN5139�Ļ��λ��庯��*******************************************/











/************************************��zigbee�Ĳ�������********************************************/
void JN5139SendByte(  char u8data)
{
  UART_SendByte(UART_1,u8data);
}
//��ZIGBEEģ�鷢��һ���ַ���
void JN5139SendString(char *p)
{
  while(*p != '\0')
  {
    JN5139SendByte(*p);
    p++;
  }
}
void JN5139Init(void)
{
  JNRAMInit();//����zigbee��ѭ�������ʼ��
}
/************************************��zigbee�Ĳ�������********************************************/
