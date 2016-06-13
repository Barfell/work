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

extern unsigned char UartFinishFlag;
extern LoopRAMType Uartloop;

//DT RD15001 CONF UPDATE 2016-01-15-09:05:09
//把原始数据提取出来，假如是DT命令则提取，不是则不提取  成功则返回1，不提取则返回0
//通过判断空格间隔来提取数据
unsigned char DTcmdExtract(unsigned char *dat, DTprotocolStructType *DTprotocolStructure)
{
	unsigned char i = 0;
	if( ( *(dat + 0) == 0xF1) && sizeof(dat) >= 22)//这段数据是数据包的开始
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



//串口通信任务。串口接到命令后进行动作
void DTcmdTask(void)
{
  
}


//对命令进行处理,参数结构体都是提取成功后的(确认是DT的命令体系，且对本机操作)
void DTcmdProc(DTprotocolStructType DTprotocolStructure)
{
	
}




/*-------------------各个命令对应的子函数-------------------------*/
void DTprotocol_TIME_handle(char *para)
{
  printf("DTprotocol_TIME_handle run....  para is:%s\r\n",para);
}

void DTprotocol_UPDATE_handle(char *para)
{
  printf("DTprotocol_UPDATE_handle run....  para is:%s\r\n",para);
  
  //FirmwareUpdate();           //复位跳转到BOOT  
}

void DTprotocol_PROTOCOL_handle(char *para)
{
  printf("DTprotocol_PROTOCOL_handle run....  para is:%s\r\n",para);
}

