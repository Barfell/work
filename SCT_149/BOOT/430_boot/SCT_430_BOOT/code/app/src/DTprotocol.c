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


unsigned char uart_recived_flg = 0;
extern LoopRAMType Uartloop;


//��ԭʼ������ȡ������������DT��������ȡ����������ȡ  �ɹ��򷵻�1������ȡ�򷵻�0
//ͨ���жϿո�������ȡ����
unsigned char DTcmdExtract(char *dat, DTprotocolStructType *DTprotocolStructure)
{
	char temp[50]={'\0'};
	unsigned char i = 0, j = 0;
	memset(DTprotocolStructure,0,sizeof(*DTprotocolStructure));


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
                //printf("temp:%s\r\n",temp);
		strcat(DTprotocolStructure->Header, temp);
                //printf("DTprotocolStructure.Header:%s\r\n",DTprotocolStructure->Header);
		memset(temp,'\0',50);
		j = 0;
		i++;//�����ո���
		while(*(dat+i) != ' ')
		{
			*(temp+j) = *(dat+i);
			i++;
			j++;
			if(i >DATA_MAX_LEGTH)//�ո���������
			{ memset(DTprotocolStructure,0,sizeof(*DTprotocolStructure)); return 0;}
		}
		/*-------------Device_id-------------*/
		if(strncmp(temp, DEV_ID, sizeof(DEV_ID)) == 0)
		{
                                //printf("temp:%s\r\n",temp);
			/*����Ϊ�����ʽ���豸id����Ӧ��ʱ��*/
				strcat(DTprotocolStructure->Device_id, temp);
                               // printf("DTprotocolStructure.Device_id:%s\r\n",DTprotocolStructure->Device_id);
				memset(temp,'\0',50);
				j = 0;
				i++;
				while(*(dat+i) != ' ')
				{
					*(temp+j) = *(dat+i);
					i++;
					j++;
					if(i > DATA_MAX_LEGTH)//�ո���������
					{ memset(DTprotocolStructure,0,sizeof(*DTprotocolStructure)); return 0;}
				}
				/*-------------Cmd-------------*/
                               // printf("temp:%s\r\n",temp);
				strcat(DTprotocolStructure->Cmd, temp);
                                //printf("DTprotocolStructure.Cmd:%s\r\n",DTprotocolStructure->Cmd);
				memset(temp,'\0',50);
				j = 0;
				i++;
				while(*(dat+i) != ' ')
				{
					*(temp+j) = *(dat+i);
					i++;
					j++;
					if(i > DATA_MAX_LEGTH)//�ո���������
					{ memset(DTprotocolStructure,0,sizeof(*DTprotocolStructure)); return 0;}
				}
				/*-------------CmdType-------------*/
                                //printf("temp:%s\r\n",temp);
				strcat(DTprotocolStructure->CmdType, temp);
                                //printf("DTprotocolStructure.CmdType:%s\r\n",DTprotocolStructure->CmdType);
				memset(temp,'\0',50);
				j = 0;
				i++;
				while(  !(  *(dat+i) == '\r'  &&   *(dat+i+1) == '\n' ) )
				{
					*(temp+j) = *(dat+i);
					i++;
					j++;
					if(i > DATA_MAX_LEGTH)//�ո���������
					{ memset(DTprotocolStructure,0,sizeof(*DTprotocolStructure)); return 0;}
				}
				/*-------------CmdPara-------------*/
                                //printf("temp:%s\r\n",temp);
				strcat(DTprotocolStructure->CmdPara, temp);
                                //printf("DTprotocolStructure.CmdPara:%s\r\n",DTprotocolStructure->CmdPara);
				return 1;
		}
		else//������豸id��һ��
		{ memset(DTprotocolStructure,0,sizeof(*DTprotocolStructure)); return 0;}
	}
	else//����DT��ʽ ֱ�ӷ��ػ���Ԥ��������ʽ
	{return 0;}
}



//����ͨ�����񡣴��ڽӵ��������ж���
void DTcmdTask(void)
{
  char strcmd123[100]={'\0'};
  DTprotocolStructType DTprotocoltestStructure;
  //һ�����ݽ������
  if(uart_recived_flg == 1)
      {
        uart_recived_flg = 0;
        //��ȡ�����λ��������
        LoopRAMReadLength(strcmd123, Uartloop.LoopDatLength);
        printf("Uart recived data:%s",strcmd123);
        //����DT��ʽ������
        if(  DTcmdExtract(strcmd123,&DTprotocoltestStructure) == 1 )
        { 
          printf("%s\r\n",DTprotocoltestStructure.Header);
          printf("%s\r\n",DTprotocoltestStructure.Device_id);
          printf("%s\r\n",DTprotocoltestStructure.Cmd);
          printf("%s\r\n",DTprotocoltestStructure.CmdType);
          printf("%s\r\n",DTprotocoltestStructure.CmdPara);
        }
        //��������
        DTcmdProc(DTprotocoltestStructure);//��������
      }
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
  printf("DTprotocol_TIME_handle run....  para is:%s\r\n",para);
}

void DTprotocol_UPDATE_handle(char *para)
{
	//��λ��ת
  printf("DTprotocol_UPDATE_handle run....  para is:%s\r\n",para);
}

void DTprotocol_PROTOCOL_handle(char *para)
{
  printf("DTprotocol_PROTOCOL_handle run....  para is:%s\r\n",para);
}

