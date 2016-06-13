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

#define DATA_MAX_LEGTH   100            //用于判定命令数据的正确性



/*DT 命令格式结构体*/
typedef struct DTprotocol{
	 char Header[5];		//命令体系/DT
	 char Device_id[20];	        //设备id
	 char Cmd[10];			//命令/CONF/READ
	 char CmdType[10];		//命令类型/TIME/UPDATE/.....
	 char CmdPara[50];		//命令参数
} DTprotocolStructType;

/*DT 升级包数据格式结构体*/
typedef struct DTpacket{
	 char Index[2];				//包头
	 char Length[4];			//此包数据长度
	 char TotalPacketNum[4];	        //总包数量
	 char CurrentPacketNum[4];	        //当前包序号
	 char Dat[4096];			//数据
	 char CRCValue;				//crc校验值
} DTpacketStructType;



//命令解析
unsigned char DTcmdExtract(char *dat, DTprotocolStructType *DTprotocolStructure);
//通信任务
void DTcmdTask(void);
//命令处理
void DTcmdProc(DTprotocolStructType DTprotocolStructure);
//处理函数
void DTprotocol_TIME_handle(char *para);
void DTprotocol_UPDATE_handle(char *para);
void DTprotocol_PROTOCOL_handle(char *para);


#endif
