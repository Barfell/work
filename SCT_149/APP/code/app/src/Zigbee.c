#include "Zigbee.h"
#include "JN5139.h"
#include "kernel.h"
#include "msp430f149_uart.h"



unsigned char JN_recived_flg = 0;                                       //zigbee接收到response的标志
extern JNRAMType JNLoopRam;                                             //用于zigbee的环形缓冲
ZigbeeStatusType ZigbeeStatus = ZIGBEE_STATUS_POWER_ON;                 //刚开始是上电状态的




//zigbee模块的初始化，模块返回成功即是初始化成功
unsigned char ZigbeeInit(void)
{
#ifdef ZIGBEE_MODE_NET
    unsigned char TryTimes = 0;
    UART_Init(UART_1,UART_SouceClk_SMCLK,UART_SMCLKBaud_115200);//串口初始化
    JN5139Init();//初始化用于zigbee的环形缓冲。。。。清零
   
    /*-----------------------复位---------------------------*/
    JN5139SendString(ZIGBEE_CMD_STRING_RST);
    ZigbeeStatus = ZIGBEE_STATUS_RST;
    delay_ms(100);
    while(ZigbeeRSP() != 1)
    {
      JN5139SendString(ZIGBEE_CMD_STRING_RST);
      delay_ms(100);
      TryTimes++;
      if(TryTimes > 3)
      {TryTimes = 0;return 0;}
    }
    /*-----------------------CFG---------------------------*/
    JN5139SendString(ZIGBEE_CMD_STRING_CFG);
    ZigbeeStatus = ZIGBEE_STATUS_CFG;
    delay_ms(100);
    while(ZigbeeRSP() != 1)
    {
      JN5139SendString(ZIGBEE_CMD_STRING_CFG);
      delay_ms(100);
      TryTimes++;
      if(TryTimes > 3)
      {TryTimes = 0;return 0;}
    }
    /*------------------------INI---------------------------*/
    JN5139SendString(ZIGBEE_CMD_STRING_INI);
    ZigbeeStatus = ZIGBEE_STATUS_INI;
    delay_ms(100);
    while(ZigbeeRSP() != 1)
    {
      JN5139SendString(ZIGBEE_CMD_STRING_INI);
      delay_ms(100);
      TryTimes++;
      if(TryTimes > 3)
      {TryTimes = 0;return 0;}
    }
    /*------------------------STR---------------------------*/
    JN5139SendString(ZIGBEE_CMD_STRING_STR);
    ZigbeeStatus = ZIGBEE_STATUS_STR;
    delay_ms(200);
    while(ZigbeeRSP() != 1)
    {
      JN5139SendString(ZIGBEE_CMD_STRING_STR);
      delay_ms(100);
      TryTimes++;
      if(TryTimes > 3)
      {TryTimes = 0;return 0;}
    }
    /*------------------------NET---------------------------*/
    printf("end-device to join in net.......\r\n");
    ZigbeeStatus = ZIGBEE_STATUS_NET;
    delay_ms(1000);
    while(ZigbeeRSP() != 1)
    {
      printf("try.......%d\r\n",TryTimes);
      delay_ms(1000);
      TryTimes++;
      if(TryTimes > 15)
      {TryTimes = 0;printf("join in net failed!\r\n");return 0;}
      
    }
    ZigbeeStatus = ZIGBEE_STATUS_IDLE;
    printf("join in net succsed!\r\n");
    return 1;
#endif

#ifdef ZIGBEE_MODE_DIRECT
    UART_Init(UART_1,UART_SouceClk_SMCLK,UART_SMCLKBaud_19200);//串口初始化
    JN5139Init();//初始化用于zigbee的环形缓冲。。。。清零
    printf("ZIGBEE_MODE_DIRECT in 19200 bps.\r\n");
    return 1;
#endif
  
}





void zigbeeproc(void)
{
#ifdef ZIGBEE_MODE_NET
  char strJN[150] = {'\0'};
  if(ZigbeeStatus == ZIGBEE_STATUS_IDLE)
  {
    if(JN_recived_flg == 1)
    {
      JN_recived_flg = 0;
      JNRAMReadLength(strJN, JNLoopRam.JNDatLength);
      printf("ZIGBEE_STATUS_IDLE, zigbee return data:\r\n%s",strJN);
      memset(strJN,'\0',150);
    }
  }
#endif
  
#ifdef ZIGBEE_MODE_DIRECT
  char strJN[150] = {'\0'};
    if(JN_recived_flg == 1)
    {
      JN_recived_flg = 0;
      JNRAMReadLength(strJN, JNLoopRam.JNDatLength);
      printf("ZIGBEE_STATUS_IDLE, zigbee return data:\r\n%s",strJN);
      memset(strJN,'\0',150);
    }
#endif
}



//发送命令后zigbee模块返回发状态
unsigned char ZigbeeRSP(void)
{
  char strJN[150] = {'\0'};
  unsigned int DelayCount = 0;
  unsigned char RSP_Status = 0;
  
  
#ifdef ZIGBEE_TYPE_COORDINATOR
 switch(ZigbeeStatus)
 {
   case ZIGBEE_STATUS_POWER_ON:break;
   case ZIGBEE_STATUS_RST:break;
   case ZIGBEE_STATUS_INIT:break;
   case ZIGBEE_STATUS_WAIT_JOIN_NET:break;
   case ZIGBEE_STATUS_NET:break;
   case ZIGBEE_STATUS_IDLE:break;
   case ZIGBEE_STATUS_SEND_DATA:break;
   case ZIGBEE_STATUS_WAIT_SEND_RSP:break;
   case ZIGBEE_STATUS_SEND_DONE:break;
   default:break;
 }
#endif
 
#ifdef ZIGBEE_TYPE_END
 switch(ZigbeeStatus)
 {
   case ZIGBEE_STATUS_POWER_ON:break;
   case ZIGBEE_STATUS_RST:
        while(JN_recived_flg != 1)
        {
          DelayCount++;
          delay_ms(10);
          if(DelayCount == 60)
          {
            DelayCount = 0;
            break;
          }
        }
        JN_recived_flg = 0;
        JNRAMReadLength(strJN, JNLoopRam.JNDatLength);
        if(strncmp(strJN, "RST\r\nAT-Jenie Version 1.3 Jul  9 2008\r\n", 25) == 0)
          {       RSP_Status = 1;}
        else
          {       RSP_Status = 0;}
        printf("ZIGBEE_STATUS_RST, zigbee return data:\r\n%s",strJN);
   break;
   
   case ZIGBEE_STATUS_CFG:
       while(JN_recived_flg != 1)
          {
            DelayCount++;
            delay_ms(10);
            if(DelayCount == 60)
            {
              DelayCount = 0;
              break;
            }
          }
          JN_recived_flg = 0;
          JNRAMReadLength(strJN, JNLoopRam.JNDatLength);
          if(strncmp(strJN, "CFG,x07FFF800,0,0,5,0\r\nOK\r\n",  sizeof(ZIGBEE_CMD_STRING_CFG) + 4) == 0)
            {       RSP_Status = 1;}
          else
            {       RSP_Status = 0;}
          printf("ZIGBEE_STATUS_CFG, zigbee return data:\r\n%s",strJN);
     break;
     
   case ZIGBEE_STATUS_INI:
       while(JN_recived_flg != 1)
          {
            DelayCount++;
            delay_ms(10);
            if(DelayCount == 60)
            {
              DelayCount = 0;
              break;
            }
          }
          JN_recived_flg = 0;
          JNRAMReadLength(strJN, JNLoopRam.JNDatLength);
          if(strncmp(strJN, "INI,0,0,x12345678,0,0\r\nOK\r\n",  sizeof(ZIGBEE_CMD_STRING_INI) + 4) == 0)
            {       RSP_Status = 1;}
          else
            {       RSP_Status = 0;}
          printf("ZIGBEE_STATUS_INI, zigbee return data:\r\n%s",strJN);
     break;
     
   case ZIGBEE_STATUS_STR:
       while(JN_recived_flg != 1)
          {
            DelayCount++;
            delay_ms(10);
            if(DelayCount == 50)
            {
              DelayCount = 0;
              break;
            }
          }
          JN_recived_flg = 0;
          JNRAMReadLength(strJN, JNLoopRam.JNDatLength);
          if(strncmp(strJN, "STR,2\r\nOK\r\n",  sizeof(ZIGBEE_CMD_STRING_STR) + 4) == 0)
            {       RSP_Status = 1;}
          else
            {       RSP_Status = 0;}
          printf("ZIGBEE_STATUS_STR, zigbee return data:\r\n%s",strJN);
     break;
     
   case ZIGBEE_STATUS_NET:
        while(JN_recived_flg != 1)
          {
            DelayCount++;
            delay_ms(10);
            if(DelayCount == 100)
            {
              DelayCount = 0;
              break;
            }
          }
          JN_recived_flg = 0;
          JNRAMReadLength(strJN, JNLoopRam.JNDatLength);
          //NTU,0006066005651049035,0006066005652036001,1,43981,26
          if(strncmp(strJN, "NTU", 3) == 0)
            {       RSP_Status = 1;}
          else
            {       RSP_Status = 0;}
          printf("ZIGBEE_STATUS_NET, zigbee return data:\r\n%s",strJN);
     break;
  
   
   default:break;
 }
#endif
 
#ifdef ZIGBEE_TYPE_ROUTER
 switch(ZigbeeStatus)
 {
   case ZIGBEE_STATUS_POWER_ON:break;
   case ZIGBEE_STATUS_RST:break;
   case ZIGBEE_STATUS_INIT:break;
   case ZIGBEE_STATUS_WAIT_JOIN_NET:break;
   case ZIGBEE_STATUS_NET:break;
   case ZIGBEE_STATUS_IDLE:break;
   case ZIGBEE_STATUS_SEND_DATA:break;
   case ZIGBEE_STATUS_WAIT_SEND_RSP:break;
   case ZIGBEE_STATUS_SEND_DONE:break;
   default:break;
 }
#endif
 return RSP_Status;
}








//向zigbee模块发送一串数据
unsigned char ZigbeeSendData(char *p,unsigned int length)
{
#ifdef ZIGBEE_MODE_NET
  ///////
#endif
  
#ifdef ZIGBEE_MODE_DIRECT
  ///////
#endif
  return 0;
}