#ifndef __DTPROTOCO_H_
#define __DTPROTOCO_H_

typedef struct DTprotocol{
	unsigned char Header[1];//引导符
	unsigned char Length[4];//整个数据长度      
	unsigned char Info[5];//信息头
	unsigned char PacketLength[4];//总包数
	unsigned char PacketNum[4];//当前包序号
	unsigned char Data[4096];//数据
	unsigned char CrcSum[2];//crc和
	unsigned char EndFlag[2];//终止符'\r\n'	
} DTprotocolStructType;



//命令解析
unsigned char DTcmdExtract(unsigned char *dat, DTprotocolStructType *DTprotocolStructure);
//通信任务
void DTcmdTask(void);
//命令处理
void DTcmdProc(DTprotocolStructType DTprotocolStructure);
//处理函数
void DTprotocol_TIME_handle(char *para);
void DTprotocol_UPDATE_handle(char *para);
void DTprotocol_PROTOCOL_handle(char *para);


#endif
