#ifndef __DTPROTOCO_H_
#define __DTPROTOCO_H_

typedef struct DTprotocol{
	unsigned char Header[1];//������
	unsigned char Length[4];//�������ݳ���      
	unsigned char Info[5];//��Ϣͷ
	unsigned char PacketLength[4];//�ܰ���
	unsigned char PacketNum[4];//��ǰ�����
	unsigned char Data[4096];//����
	unsigned char CrcSum[2];//crc��
	unsigned char EndFlag[2];//��ֹ��'\r\n'	
} DTprotocolStructType;



//�������
unsigned char DTcmdExtract(unsigned char *dat, DTprotocolStructType *DTprotocolStructure);
//ͨ������
void DTcmdTask(void);
//�����
void DTcmdProc(DTprotocolStructType DTprotocolStructure);
//������
void DTprotocol_TIME_handle(char *para);
void DTprotocol_UPDATE_handle(char *para);
void DTprotocol_PROTOCOL_handle(char *para);


#endif
