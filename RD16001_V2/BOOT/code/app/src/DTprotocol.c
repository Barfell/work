/****************************************************
  通信协议的文件：
1.包含解析一串字符串是否是DT格式的
2.命令任务---对接收到的任务进行相应的处理
3.各种命令处理子函数
*****************************************************
*/
#include "DTprotocol.h"
#include "LoopRamFunc.h"
#include <stdio.h>
#include <string.h>


unsigned char uart_recived_flg = 0;
extern LoopRAMType Uartloop;


//把原始数据提取出来，假如是DT命令则提取，不是则不提取  成功则返回1，不提取则返回0
//通过判断空格间隔来提取数据
unsigned char DTcmdExtract(char *dat, DTprotocolStructType *DTprotocolStructure)
{
	char temp[50]={'\0'};
	unsigned char i = 0, j = 0;
	memset(DTprotocolStructure,0,sizeof(*DTprotocolStructure));


	/*解析命令，假如合适则保存到DTprotocolStructure*/
	while(*(dat+i) != ' ')
	{
		*(temp+j) = *(dat+i);
		i++;
		j++;
		if(i > DATA_MAX_LEGTH)//空格间隔不符合
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
		i++;//跳过空格间隔
		while(*(dat+i) != ' ')
		{
			*(temp+j) = *(dat+i);
			i++;
			j++;
			if(i >DATA_MAX_LEGTH)//空格间隔不符合
			{ memset(DTprotocolStructure,0,sizeof(*DTprotocolStructure)); return 0;}
		}
		/*-------------Device_id-------------*/
		if(strncmp(temp, DEV_ID, sizeof(DEV_ID)) == 0)
		{
                                //printf("temp:%s\r\n",temp);
			/*以下为命令格式和设备id都对应的时候*/
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
					if(i > DATA_MAX_LEGTH)//空格间隔不符合
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
					if(i > DATA_MAX_LEGTH)//空格间隔不符合
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
					if(i > DATA_MAX_LEGTH)//空格间隔不符合
					{ memset(DTprotocolStructure,0,sizeof(*DTprotocolStructure)); return 0;}
				}
				/*-------------CmdPara-------------*/
                                //printf("temp:%s\r\n",temp);
				strcat(DTprotocolStructure->CmdPara, temp);
                                //printf("DTprotocolStructure.CmdPara:%s\r\n",DTprotocolStructure->CmdPara);
				return 1;
		}
		else//命令的设备id不一致
		{ memset(DTprotocolStructure,0,sizeof(*DTprotocolStructure)); return 0;}
	}
	else//不是DT格式 直接返回或者预留其他格式
	{return 0;}
}



//串口通信任务。串口接到命令后进行动作
void DTcmdTask(void)
{
  char strcmd123[100]={'\0'};
  DTprotocolStructType DTprotocoltestStructure;
  //一组数据接收完毕
  if(uart_recived_flg == 1)
      {
        uart_recived_flg = 0;
        //读取出环形缓冲的数据
        LoopRAMReadLength(strcmd123, Uartloop.LoopDatLength);
        printf("Uart recived data:%s",strcmd123);
        //属于DT格式的数据
        if(  DTcmdExtract(strcmd123,&DTprotocoltestStructure) == 1 )
        { 
          printf("%s\r\n",DTprotocoltestStructure.Header);
          printf("%s\r\n",DTprotocoltestStructure.Device_id);
          printf("%s\r\n",DTprotocoltestStructure.Cmd);
          printf("%s\r\n",DTprotocoltestStructure.CmdType);
          printf("%s\r\n",DTprotocoltestStructure.CmdPara);
        }
        //处理命令
        DTcmdProc(DTprotocoltestStructure);//处理命令
      }
}


//对命令进行处理,参数结构体都是提取成功后的(确认是DT的命令体系，且对本机操作)
void DTcmdProc(DTprotocolStructType DTprotocolStructure)
{
	/*设置参数还是获取数据*/
	/*--------------------------CONF--------------------------------*/
	if( strncmp(DTprotocolStructure.Cmd, DT_CMD_CONF, sizeof(DTprotocolStructure.Cmd)) == 0 )
	{
		if(strncmp(DTprotocolStructure.CmdType, DT_CMD_TYPE_TIME, sizeof(DTprotocolStructure.CmdType)) == 0)
		{/*时间设置DT_CMD_TYPE_TIME命令处理函数*/
			DTprotocol_TIME_handle(DTprotocolStructure.CmdPara);//设置时间函数
		}
		if(strncmp(DTprotocolStructure.CmdType, DT_CMD_TYPE_UPDATE, sizeof(DTprotocolStructure.CmdType)) == 0)
		{/*设置DT_CMD_TYPE_UPDATE命令处理函数*/
			DTprotocol_UPDATE_handle(DTprotocolStructure.CmdPara);
		}
		if(strncmp(DTprotocolStructure.CmdType, DT_CMD_TYPE_PROTOCOL, sizeof(DTprotocolStructure.CmdType)) == 0)
		{/*设置DT_CMD_TYPE_PROTOCOL命令处理函数*/
			DTprotocol_PROTOCOL_handle(DTprotocolStructure.CmdPara);
		}
		
		/* ...此处添加其他命令.. */
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




/*-------------------各个命令对应的子函数-------------------------*/
void DTprotocol_TIME_handle(char *para)
{
  printf("DTprotocol_TIME_handle run....  para is:%s\r\n",para);
}

void DTprotocol_UPDATE_handle(char *para)
{
	//复位跳转
  printf("DTprotocol_UPDATE_handle run....  para is:%s\r\n",para);
}

void DTprotocol_PROTOCOL_handle(char *para)
{
  printf("DTprotocol_PROTOCOL_handle run....  para is:%s\r\n",para);
}

