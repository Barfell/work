#include "DTprotocol.h"
#include <stdio.h>
#include <string.h>





//把原始数据提取出来，假如是DT命令则提取，不是则不提取  成功则返回1，不提取则返回0
//通过判断空格间隔来提取数据
unsigned char DTcmdExtract(char *dat, DTprotocolStructType DTprotocolStructure)
{
	char temp[50]={'\0'};
	unsigned char i = 0, j = 0;
	memset(&DTprotocolStructure,0,sizeof(DTprotocolStructure));


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
		strcat(DTprotocolStructure.Header, temp);
		memset(temp,'\0',50);
		j = 0;
		i++;//跳过空格间隔
		while(*(dat+i) != ' ')
		{
			*(temp+j) = *(dat+i);
			i++;
			j++;
			if(i >DATA_MAX_LEGTH)//空格间隔不符合
			{ memset(&DTprotocolStructure, 0, sizeof(DTprotocolStructure)); return 0;}
		}
		/*-------------Device_id-------------*/
		if(strncmp(temp, DEV_ID, sizeof(DEV_ID)) == 0)
		{
			/*以下为命令格式和设备id都对应的时候*/
				strcat(DTprotocolStructure.Device_id, temp);
				memset(temp,'\0',50);
				j = 0;
				i++;
				while(*(dat+i) != ' ')
				{
					*(temp+j) = *(dat+i);
					i++;
					j++;
					if(i > DATA_MAX_LEGTH)//空格间隔不符合
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
					if(i > DATA_MAX_LEGTH)//空格间隔不符合
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
					if(i > DATA_MAX_LEGTH)//空格间隔不符合
					{ memset(&DTprotocolStructure, 0, sizeof(DTprotocolStructure)); return 0;}
				}
				/*-------------CmdPara-------------*/
				strcat(DTprotocolStructure.CmdPara, temp);
				return 1;
		}
		else//命令的设备id不一致
		{ memset(&DTprotocolStructure, 0, sizeof(DTprotocolStructure)); return 0;}
	}
	else//不是DT格式 直接返回或者预留其他格式
	{return 0;}
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
	
}

void DTprotocol_UPDATE_handle(char *para)
{
	//复位跳转
}

void DTprotocol_PROTOCOL_handle(char *para)
{
	
}

