#ifndef _JN5139_H_
#define _JN5139_H_


#define JN_LENGTH 150


typedef struct JNram{
  unsigned int JNDatLength;//���λ����ڲ���Ч���ݳ���
  unsigned int readpos;//��ȡ��λ��
  unsigned int writepos;//д���λ��
  char data[JN_LENGTH];//��������
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


