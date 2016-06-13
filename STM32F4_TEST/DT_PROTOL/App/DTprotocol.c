#include "DTprotocol.h"
#include <stdio.h>
#include <string.h>





//��ԭʼ������ȡ������������DT��������ȡ����������ȡ  �ɹ��򷵻�1������ȡ�򷵻�0
//ͨ���жϿո�������ȡ����
unsigned char DTcmdExtract(char *dat, DTprotocolStructType DTprotocolStructure)
{
	char temp[50]={'\0'};
	unsigned char i = 0, j = 0;
	memset(&DTprotocolStructure,0,sizeof(DTprotocolStructure));


	/*���������������򱣴浽DTprotocolStructure*/
	while(*(dat+i) != ' ')
	{
		*(temp+j) = *(dat+i);
		i++;
		j++;
		if(i > DATA_MAX_LEGTH)//�ո���������
		{return 0;}
	}
	/*-------------Header------------*/
	if(strncmp(temp, DT_CMD_HEAD, sizeof(DT_CMD_HEAD)) == 0)
	{
		strcat(DTprotocolStructure.Header, temp);
		memset(temp,'\0',50);
		j = 0;
		i++;//�����ո���
		while(*(dat+i) != ' ')
		{
			*(temp+j) = *(dat+i);
			i++;
			j++;
			if(i >DATA_MAX_LEGTH)//�ո���������
			{ memset(&DTprotocolStructure, 0, sizeof(DTprotocolStructure)); return 0;}
		}
		/*-------------Device_id-------------*/
		if(strncmp(temp, DEV_ID, sizeof(DEV_ID)) == 0)
		{
			/*����Ϊ�����ʽ���豸id����Ӧ��ʱ��*/
				strcat(DTprotocolStructure.Device_id, temp);
				memset(temp,'\0',50);
				j = 0;
				i++;
				while(*(dat+i) != ' ')
				{
					*(temp+j) = *(dat+i);
					i++;
					j++;
					if(i > DATA_MAX_LEGTH)//�ո���������
					{ memset(&DTprotocolStructure, 0, sizeof(DTprotocolStructure)); return 0;}
				}
				/*-------------Cmd-------------*/
				strcat(DTprotocolStructure.Cmd, temp);
				memset(temp,'\0',50);
				j = 0;
				i++;
				while(*(dat+i) != ' ')
				{
					*(temp+j) = *(dat+i);
					i++;
					j++;
					if(i > DATA_MAX_LEGTH)//�ո���������
					{ memset(&DTprotocolStructure, 0, sizeof(DTprotocolStructure)); return 0;}
				}
				/*-------------CmdType-------------*/
				strcat(DTprotocolStructure.CmdType, temp);
				memset(temp,'\0',50);
				j = 0;
				i++;
				while(  !(  *(dat+i) == '\r'  &&   *(dat+i+1) == '\n' ) )
				{
					*(temp+j) = *(dat+i);
					i++;
					j++;
					if(i > DATA_MAX_LEGTH)//�ո���������
					{ memset(&DTprotocolStructure, 0, sizeof(DTprotocolStructure)); return 0;}
				}
				/*-------------CmdPara-------------*/
				strcat(DTprotocolStructure.CmdPara, temp);
				return 1;
		}
		else//������豸id��һ��
		{ memset(&DTprotocolStructure, 0, sizeof(DTprotocolStructure)); return 0;}
	}
	else//����DT��ʽ ֱ�ӷ��ػ���Ԥ��������ʽ
	{return 0;}
}







//��������д���,�����ṹ�嶼����ȡ�ɹ����(ȷ����DT��������ϵ���ҶԱ�������)
void DTcmdProc(DTprotocolStructType DTprotocolStructure)
{
	/*���ò������ǻ�ȡ����*/
	/*--------------------------CONF--------------------------------*/
	if( strncmp(DTprotocolStructure.Cmd, DT_CMD_CONF, sizeof(DTprotocolStructure.Cmd)) == 0 )
	{
		if(strncmp(DTprotocolStructure.CmdType, DT_CMD_TYPE_TIME, sizeof(DTprotocolStructure.CmdType)) == 0)
		{/*ʱ������DT_CMD_TYPE_TIME�������*/
			DTprotocol_TIME_handle(DTprotocolStructure.CmdPara);//����ʱ�亯��
		}
		if(strncmp(DTprotocolStructure.CmdType, DT_CMD_TYPE_UPDATE, sizeof(DTprotocolStructure.CmdType)) == 0)
		{/*����DT_CMD_TYPE_UPDATE�������*/
			DTprotocol_UPDATE_handle(DTprotocolStructure.CmdPara);
		}
		if(strncmp(DTprotocolStructure.CmdType, DT_CMD_TYPE_PROTOCOL, sizeof(DTprotocolStructure.CmdType)) == 0)
		{/*����DT_CMD_TYPE_PROTOCOL�������*/
			DTprotocol_PROTOCOL_handle(DTprotocolStructure.CmdPara);
		}
		
		/* ...�˴������������.. */
	}
	/*--------------------------READ--------------------------------*/
	else if( strncmp(DTprotocolStructure.Cmd, DT_CMD_READ, sizeof(DTprotocolStructure.Cmd)) == 0 )
	{
		if(strncmp(DTprotocolStructure.CmdType, DT_CMD_TYPE_TIME, sizeof(DTprotocolStructure.CmdType)) == 0)
		{/**/}
		if(strncmp(DTprotocolStructure.CmdType, DT_CMD_TYPE_UPDATE, sizeof(DTprotocolStructure.CmdType)) == 0)
		{/**/}
		if(strncmp(DTprotocolStructure.CmdType, DT_CMD_TYPE_PROTOCOL, sizeof(DTprotocolStructure.CmdType)) == 0)
		{/**/}
	}
	/*--------------------------other--------------------------------*/
	else
	{
		/*   .....   */
	}
}




/*-------------------���������Ӧ���Ӻ���-------------------------*/
void DTprotocol_TIME_handle(char *para)
{
	
}

void DTprotocol_UPDATE_handle(char *para)
{
	//��λ��ת
}

void DTprotocol_PROTOCOL_handle(char *para)
{
	
}

