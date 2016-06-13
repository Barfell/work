#include "JN5139.h"
#include "msp430f149_uart.h"
#include "kernel.h"


JNRAMType JNLoopRam;



/*************************************JN5139的环形缓冲函数*******************************************/
//串口环形缓冲初始化
void JNRAMInit(void)
{
  JNLoopRam.JNDatLength = 0;//环形缓冲有效数据的长度
  JNLoopRam.readpos = 0;//读取位置
  JNLoopRam.writepos = 0;//写入位置
}
//串口环形缓 写入一个byte
void JNRAMWriteByte(char dat )
{
    JNLoopRam.data[JNLoopRam.writepos] = dat;
    JNLoopRam.writepos++;
    JNLoopRam.writepos = JNLoopRam.writepos % JN_LENGTH;
    JNLoopRam.JNDatLength++;
    if(JNLoopRam.JNDatLength == JN_LENGTH)
      { JNLoopRam.JNDatLength = 0;}
}
//串口环形缓冲写入一定长度的数据
void JNRAMWriteLength(char *dat ,unsigned int length)
{
  while(length != 0)
  {
    JNRAMWriteByte(*dat);
    dat++;
    length--;
  }
}
//串口环形缓冲读出一个byte
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
//串口环形缓冲读取一定长度的数据，放于‘*p’
void JNRAMReadLength( char *p, int length)
{
  unsigned int i;
  for(i=0;i<length; i++)
  {
    *(p+i) = JNRAMReadByte();
  }
}
/*************************************JN5139的环形缓冲函数*******************************************/











/************************************对zigbee的操作函数********************************************/
void JN5139SendByte(  char u8data)
{
  UART_SendByte(UART_1,u8data);
}
//给ZIGBEE模块发送一串字符串
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
  JNRAMInit();//用于zigbee的循环缓冲初始化
}
/************************************对zigbee的操作函数********************************************/
