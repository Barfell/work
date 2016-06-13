#ifndef __DTPROTOCO_H_
#define __DTPROTOCO_H_

//protocol
#define DT_CMD_HEAD 			"DT"
#define DEV_ID      			"RD15001"
//cmd
#define DT_CMD_CONF     		"CONF"
#define DT_CMD_READ     		"READ"
//cmd type
#define DT_CMD_TYPE_TIME		"TIME"
#define DT_CMD_TYPE_UPDATE		"UPDATE"
#define DT_CMD_TYPE_PROTOCOL	        "PROTOCOL"

#define DATA_MAX_LEGTH   100            //�����ж��������ݵ���ȷ��



/*DT �����ʽ�ṹ��*/
typedef struct DTprotocol{
	 char Header[5];		//������ϵ/DT
	 char Device_id[20];	        //�豸id
	 char Cmd[10];			//����/CONF/READ
	 char CmdType[10];		//��������/TIME/UPDATE/.....
	 char CmdPara[50];		//�������
} DTprotocolStructType;

/*DT ���������ݸ�ʽ�ṹ��*/
typedef struct DTpacket{
	 char Index[2];				//��ͷ
	 char Length[4];			//�˰����ݳ���
	 char TotalPacketNum[4];	        //�ܰ�����
	 char CurrentPacketNum[4];	        //��ǰ�����
	 char Dat[4096];			//����
	 char CRCValue;				//crcУ��ֵ
} DTpacketStructType;



//�������
unsigned char DTcmdExtract(char *dat, DTprotocolStructType *DTprotocolStructure);
//ͨ������
void DTcmdTask(void);
//�����
void DTcmdProc(DTprotocolStructType DTprotocolStructure);
//������
void DTprotocol_TIME_handle(char *para);
void DTprotocol_UPDATE_handle(char *para);
void DTprotocol_PROTOCOL_handle(char *para);


#endif
