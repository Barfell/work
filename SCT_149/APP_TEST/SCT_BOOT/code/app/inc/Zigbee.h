#ifndef _ZIGBEE_H_
#define _ZIGBEE_H_

#define ZIGBEE_RSP_OK           "OK"
#define ZIGBEE_RSP_ERR          "ERR"
#define ZIGBEE_RSP_PKS          "PKS"
#define ZIGBEE_RSP_PKF          "PKF"
#define ZIGBEE_RSP_DLC          "DLC"



unsigned char ZigbeeInit(void)
char *ZigbeeRSP(void);



#endif