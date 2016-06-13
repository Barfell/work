#include "Zigbee.h"
#include "JN5139.h"
#include "kernel.h"

unsigned char JN_recived_flg = 0;
extern JNRAMType JNLoopRam;

//zigbeeģ��ĳ�ʼ����ģ�鷵�سɹ����ǳ�ʼ���ɹ�
unsigned char ZigbeeInit(void)
{
  JN5139Init();
  JN5139SendString("CFG,x07FFF800,0,0,5,0\r\n");
  if(ZigbeeRSP() == ZIGBEE_RSP_OK)
  {
    JN5139SendString("INI,0,0,x12345678,0,0\r\n");
    if(ZigbeeRSP() == ZIGBEE_RSP_OK)
    {
      JN5139SendString("STR,2\r\n");
      if(ZigbeeRSP() == ZIGBEE_RSP_OK)
      {
        return 1;
      }
    }
  }
  return 0;
}
//��zigbeeģ�鷢��һ������
unsigned char ZigbeeSendData(char *p,unsigned int length)
{
  char TempStr[200]={'\0'};
  strcat(TempStr,"DAT");
  strcat(TempStr,*p);
  JN5139SendString(TempStr);
  if(ZigbeeRSP() == ZIGBEE_RSP_OK)
  {return 1;}
  return 0;
}
//���������zigbeeģ�鷵�ط�״̬
char *ZigbeeRSP(void)
{
  char TempStr[20]={'\0'};
  unsigned int i;
  while(JN_recived_flg == 0)
  {
    delay_ms(1);
    i++;
    if(i >500)
    {return 0;}
  }
  JNRAMReadLength(TempStr, JNLoopRam.JNDatLength);
  if( strncmp(TempStr, ZIGBEE_RSP_OK, sizeof(ZIGBEE_RSP_OK)) == 0 )
  {return ZIGBEE_RSP_OK;}
  else
  {return 0;}
}
