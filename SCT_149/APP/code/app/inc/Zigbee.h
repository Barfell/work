#ifndef _ZIGBEE_H_
#define _ZIGBEE_H_

/******zigbee MAC:*********************************************/
#define ZIGBEE_MAC_CHAR "123456677868235554"

/******zigbee类型：coordinate、router、end-device**************/
//#define ZIGBEE_TYPE_COORDINATOR
//#define ZIGBEE_TYPE_ROUTER
#define ZIGBEE_TYPE_END

/*********************模式：直通\组网**************************/
//#define ZIGBEE_MODE_DIRECT
#define ZIGBEE_MODE_NET

/*********************zigbee状态     **************************/
#ifdef ZIGBEE_TYPE_COORDINATOR
typedef enum{
  ZIGBEE_STATUS_POWER_ON,               //上电状态
  ZIGBEE_STATUS_RST,                    //复位状态
  ZIGBEE_STATUS_CFG,
  ZIGBEE_STATUS_INI,
  ZIGBEE_STATUS_STR,
  ZIGBEE_STATUS_INIT,                   //初始化状态
  ZIGBEE_STATUS_WAIT_JOIN_NET,          //等待加入网络状态
  ZIGBEE_STATUS_NET,                    //已经加入到网络状态
  ZIGBEE_STATUS_IDLE,                   //空闲状态
  ZIGBEE_STATUS_SEND_DATA,              //发送数据状态
  ZIGBEE_STATUS_WAIT_SEND_RSP,          //发送 数据后等待回应状态
  ZIGBEE_STATUS_SEND_DONE,              //发送完毕
} ZigbeeStatusType;
#endif

#ifdef ZIGBEE_TYPE_ROUTER
typedef enum{
  ZIGBEE_STATUS_POWER_ON,               //上电状态
  ZIGBEE_STATUS_RST,                    //复位状态
  ZIGBEE_STATUS_CFG,
  ZIGBEE_STATUS_INI,
  ZIGBEE_STATUS_STR,
  ZIGBEE_STATUS_INIT,                   //初始化状态
  ZIGBEE_STATUS_WAIT_JOIN_NET,          //等待加入网络状态
  ZIGBEE_STATUS_NET,                    //已经加入到网络状态
  ZIGBEE_STATUS_IDLE,                   //空闲状态
  ZIGBEE_STATUS_SEND_DATA,              //发送数据状态
  ZIGBEE_STATUS_WAIT_SEND_RSP,          //发送 数据后等待回应状态
  ZIGBEE_STATUS_SEND_DONE,              //发送完毕
} ZigbeeStatusType;
#endif

#ifdef ZIGBEE_TYPE_END
typedef enum{
  ZIGBEE_STATUS_POWER_ON,               //上电状态
  ZIGBEE_STATUS_RST,                    //复位状态
  ZIGBEE_STATUS_CFG,
  ZIGBEE_STATUS_INI,
  ZIGBEE_STATUS_STR,
  ZIGBEE_STATUS_INIT,                   //初始化状态
  ZIGBEE_STATUS_WAIT_JOIN_NET,          //等待加入网络状态
  ZIGBEE_STATUS_NET,                    //已经加入到网络状态
  ZIGBEE_STATUS_IDLE,                   //空闲状态
  ZIGBEE_STATUS_SEND_DATA,              //发送数据状态
  ZIGBEE_STATUS_WAIT_SEND_RSP,          //发送 数据后等待回应状态
  ZIGBEE_STATUS_SEND_DONE,              //发送完毕
} ZigbeeStatusType;
#endif

/*********************zigbee各命令****************************/
#ifdef ZIGBEE_TYPE_END
  #define ZIGBEE_CMD_STRING_RST "RST\r\n"
  #define ZIGBEE_CMD_STRING_CFG "CFG,x07FFF800,0,0,5,0\r\n"
  #define ZIGBEE_CMD_STRING_INI "INI,0,0,x12345678,0,0\r\n"
  #define ZIGBEE_CMD_STRING_STR "STR,2\r\n"
#endif

#ifdef ZIGBEE_TYPE_ROUTER
  #define ZIGBEE_CMD_STRING_RST "RST\r\n"
  #define ZIGBEE_CMD_STRING_CFG "CFG,x07FFF800,0,0,5,0\r\n"
  #define ZIGBEE_CMD_STRING_INI "INI,xABCD,0,x12345678,0,1\r\n"
  #define ZIGBEE_CMD_STRING_STR "STR,2\r\n"
#endif

#ifdef ZIGBEE_TYPE_COORDINATOR
  #define ZIGBEE_CMD_STRING_RST "RST\r\n"
  #define ZIGBEE_CMD_STRING_CFG "CFG,x07FFF800,0,0,5,0\r\n"
  #define ZIGBEE_CMD_STRING_INI "INI,xABCD,0,x12345678,0,1\r\n"
  #define ZIGBEE_CMD_STRING_STR "STR,2\r\n"
#endif







#define ZIGBEE_RSP_OK           "OK"
#define ZIGBEE_RSP_ERR          "ERR"
#define ZIGBEE_RSP_PKS          "PKS"
#define ZIGBEE_RSP_PKF          "PKF"
#define ZIGBEE_RSP_DLC          "DLC"



unsigned char ZigbeeInit(void);
void zigbeeproc(void);
unsigned char ZigbeeRSP(void);



#endif

