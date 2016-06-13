#ifndef _ZIGBEE_H_
#define _ZIGBEE_H_

/******zigbee MAC:*********************************************/
#define ZIGBEE_MAC_CHAR "123456677868235554"

/******zigbee���ͣ�coordinate��router��end-device**************/
//#define ZIGBEE_TYPE_COORDINATOR
//#define ZIGBEE_TYPE_ROUTER
#define ZIGBEE_TYPE_END

/*********************ģʽ��ֱͨ\����**************************/
//#define ZIGBEE_MODE_DIRECT
#define ZIGBEE_MODE_NET

/*********************zigbee״̬     **************************/
#ifdef ZIGBEE_TYPE_COORDINATOR
typedef enum{
  ZIGBEE_STATUS_POWER_ON,               //�ϵ�״̬
  ZIGBEE_STATUS_RST,                    //��λ״̬
  ZIGBEE_STATUS_CFG,
  ZIGBEE_STATUS_INI,
  ZIGBEE_STATUS_STR,
  ZIGBEE_STATUS_INIT,                   //��ʼ��״̬
  ZIGBEE_STATUS_WAIT_JOIN_NET,          //�ȴ���������״̬
  ZIGBEE_STATUS_NET,                    //�Ѿ����뵽����״̬
  ZIGBEE_STATUS_IDLE,                   //����״̬
  ZIGBEE_STATUS_SEND_DATA,              //��������״̬
  ZIGBEE_STATUS_WAIT_SEND_RSP,          //���� ���ݺ�ȴ���Ӧ״̬
  ZIGBEE_STATUS_SEND_DONE,              //�������
} ZigbeeStatusType;
#endif

#ifdef ZIGBEE_TYPE_ROUTER
typedef enum{
  ZIGBEE_STATUS_POWER_ON,               //�ϵ�״̬
  ZIGBEE_STATUS_RST,                    //��λ״̬
  ZIGBEE_STATUS_CFG,
  ZIGBEE_STATUS_INI,
  ZIGBEE_STATUS_STR,
  ZIGBEE_STATUS_INIT,                   //��ʼ��״̬
  ZIGBEE_STATUS_WAIT_JOIN_NET,          //�ȴ���������״̬
  ZIGBEE_STATUS_NET,                    //�Ѿ����뵽����״̬
  ZIGBEE_STATUS_IDLE,                   //����״̬
  ZIGBEE_STATUS_SEND_DATA,              //��������״̬
  ZIGBEE_STATUS_WAIT_SEND_RSP,          //���� ���ݺ�ȴ���Ӧ״̬
  ZIGBEE_STATUS_SEND_DONE,              //�������
} ZigbeeStatusType;
#endif

#ifdef ZIGBEE_TYPE_END
typedef enum{
  ZIGBEE_STATUS_POWER_ON,               //�ϵ�״̬
  ZIGBEE_STATUS_RST,                    //��λ״̬
  ZIGBEE_STATUS_CFG,
  ZIGBEE_STATUS_INI,
  ZIGBEE_STATUS_STR,
  ZIGBEE_STATUS_INIT,                   //��ʼ��״̬
  ZIGBEE_STATUS_WAIT_JOIN_NET,          //�ȴ���������״̬
  ZIGBEE_STATUS_NET,                    //�Ѿ����뵽����״̬
  ZIGBEE_STATUS_IDLE,                   //����״̬
  ZIGBEE_STATUS_SEND_DATA,              //��������״̬
  ZIGBEE_STATUS_WAIT_SEND_RSP,          //���� ���ݺ�ȴ���Ӧ״̬
  ZIGBEE_STATUS_SEND_DONE,              //�������
} ZigbeeStatusType;
#endif

/*********************zigbee������****************************/
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

