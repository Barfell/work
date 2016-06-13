/****************************************************
  ͨ��Э����ļ���
1.��������һ���ַ����Ƿ���DT��ʽ��
2.��������---�Խ��յ������������Ӧ�Ĵ���
3.����������Ӻ���
*****************************************************
*/
#include "DTprotocol.h"
#include "LoopRamFunc.h"
#include <stdio.h>
#include <string.h>

extern unsigned char UartFinishFlag;
extern LoopRAMType Uartloop;

//DT RD15001 CONF UPDATE 2016-01-15-09:05:09
//��ԭʼ������ȡ������������DT��������ȡ����������ȡ  �ɹ��򷵻�1������ȡ�򷵻�0
//ͨ���жϿո�������ȡ����
unsigned char DTcmdExtract(unsigned char *dat, DTprotocolStructType *DTprotocolStructure)
{
	unsigned char i = 0;
	if( ( *(dat + 0) == 0xF1) && sizeof(dat) >= 22)//������������ݰ��Ŀ�ʼ
	{
		DTprotocolStructure->Header[0] = *(dat+0); 
		for(i=0;i<4;i++)
		{DTprotocolStructure->Length[i] = *(dat+i + 1);}
		for(i=0;i<5;i++)
		{DTprotocolStructure->Info[i] = *(dat+i+5);}
		for(i=0;i<4;i++)
		{DTprotocolStructure->PacketLength[i] = *(dat+i+10);}
		for(i=0;i<4;i++)
		{DTprotocolStructure->PacketNum[i] = *(dat+i+14);}
	}
	return 1;
}



//����ͨ�����񡣴��ڽӵ��������ж���
void DTcmdTask(void)
{
  
}


//��������д���,�����ṹ�嶼����ȡ�ɹ����(ȷ����DT��������ϵ���ҶԱ�������)
void DTcmdProc(DTprotocolStructType DTprotocolStructure)
{
	
}




/*-------------------���������Ӧ���Ӻ���-------------------------*/
void DTprotocol_TIME_handle(char *para)
{
  printf("DTprotocol_TIME_handle run....  para is:%s\r\n",para);
}

void DTprotocol_UPDATE_handle(char *para)
{
  printf("DTprotocol_UPDATE_handle run....  para is:%s\r\n",para);
  
  //FirmwareUpdate();           //��λ��ת��BOOT  
}

void DTprotocol_PROTOCOL_handle(char *para)
{
  printf("DTprotocol_PROTOCOL_handle run....  para is:%s\r\n",para);
}

