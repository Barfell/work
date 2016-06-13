#ifndef _JN5139_H_
#define _JN5139_H_


#define JN_LENGTH 150


typedef struct JNram{
  unsigned int JNDatLength;//环形缓冲内部有效数据长度
  unsigned int readpos;//读取的位置
  unsigned int writepos;//写入的位置
  char data[JN_LENGTH];//具体数据
} JNRAMType;



void JN5139SendByte(  char u8data);
void JN5139SendString(char *p);
void JN5139Init(void);

void JNRAMInit(void);
void JNRAMWriteByte(char dat );
void JNRAMWriteLength(char *dat ,unsigned int length);
char JNRAMReadByte(void);
void JNRAMReadLength( char *p, int length);

#endif


