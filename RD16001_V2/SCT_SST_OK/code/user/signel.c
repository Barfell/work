#include <msp430.h>
#include "test.h"
#include "cfg.h"
#include "gpio.h"
#include "freq.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
#include "power.h"
#include "flash.h"
#include "sst.h"
#include "rtc.h"
#include "s485.h"
#include "level.h"
#include "cmd.h"
#include "ramloop.h"
#include "key.h"
#include "ecc.h"
#include "dtu.h"
#include "rf.h"
#include <stdio.h>
#include "includes.h"


extern unsigned char MeasureTimeFlag;//测量数据标志






void DefalutConfig(void)
{
  if( 0xAA != *(unsigned char *)DEVICE_FIRST_TIME_POWERON_ADDR)
  {
    /*是否是第一次开机*/
    FlashInit();
    FlashEreaseSector(DEVICE_FIRST_TIME_POWERON_ADDR);
    FlashWriteByte(DEVICE_FIRST_TIME_POWERON_ADDR,0xAA);
    
    /*采集时间间隔*/
    FlashInit();
    FlashEreaseSector(INTERVAL_TIME_ADDR);
    FlashWriteByte(INTERVAL_TIME_ADDR, (unsigned char)( INTERVAL_TIME/256 ) );//高八位
    FlashWriteByte(INTERVAL_TIME_ADDR+1,(unsigned char)(INTERVAL_TIME % 256) ); //低八位
    
    /*cmd等待时间*/
    FlashInit();
    FlashEreaseSector(CMD_TIME_ADDR);
    FlashWriteByte(CMD_TIME_ADDR, CMD_TIME );
    
    
    /*默认的设备的通道类型和连接方式*/
    //默认的连接方式0x00:RF  0x01:dtu
    FlashInit();
    FlashEreaseSector(CONNECT_TYPE_ADDR);
    FlashWriteByte(CONNECT_TYPE_ADDR,0x00);
    
    //默认通道类型：0X01:vw  0X02:485
    FlashInit();
    FlashEreaseSector(CHANNEL_TYPE_ADDR);
    FlashWriteByte(CHANNEL_TYPE_ADDR+0,0x01);
    FlashWriteByte(CHANNEL_TYPE_ADDR+1,0x00);
    FlashWriteByte(CHANNEL_TYPE_ADDR+2,0x00);
    FlashWriteByte(CHANNEL_TYPE_ADDR+3,0x00);
    FlashWriteByte(CHANNEL_TYPE_ADDR+4,0x00);
    FlashWriteByte(CHANNEL_TYPE_ADDR+5,0x00);
    FlashWriteByte(CHANNEL_TYPE_ADDR+6,0x00);
    FlashWriteByte(CHANNEL_TYPE_ADDR+7,0x00);
    
    //默认通道连接485传感器的编号
    FlashInit();
    FlashEreaseSector(SENSOR_ID_ADDR);
    FlashWriteByte(SENSOR_ID_ADDR+0,0x00);
    FlashWriteByte(SENSOR_ID_ADDR+1,0x00);
    FlashWriteByte(SENSOR_ID_ADDR+2,0x00);
    FlashWriteByte(SENSOR_ID_ADDR+3,0x00);
    FlashWriteByte(SENSOR_ID_ADDR+4,0x00);
    FlashWriteByte(SENSOR_ID_ADDR+5,0x00);
    FlashWriteByte(SENSOR_ID_ADDR+6,0x00);
    FlashWriteByte(SENSOR_ID_ADDR+7,0x00);
    
    //默认上传是否带协议 0x00:unprotocol 0x01:protocol
    FlashInit();
    FlashEreaseSector(PROTOCOL_TYPE_ADDR);
    FlashWriteByte(PROTOCOL_TYPE_ADDR,0x00);  
    
    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
  }
}

void BoardInit(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();
  /*开启电源*/
  PowerInit();
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_ON;
  LED(1);
  delay_ms(1000);
  LED(0);
  SetRtc(0x2016,0x05,0x09,0x01,0x08,0x50,0x48);
}



//获取子设备的编号ID
//SCT16001
//获取子设备的设备ID
void GetSubDeviceID(unsigned char ch, char *IDstring)
{
  char DeviceID[20] = {'\0'};
  char temString[20] = {'\0'};
  unsigned char ID = 0;
  
  strcat(DeviceID,"SCT16");
  
  switch(ch)
  {
    case 1: ID = *(unsigned char*)(SUB_DEVICE_ID+0);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 2: ID = *(unsigned char*)(SUB_DEVICE_ID+1);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 3: ID = *(unsigned char*)(SUB_DEVICE_ID+2);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 4: ID = *(unsigned char*)(SUB_DEVICE_ID+3);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 5: ID = *(unsigned char*)(SUB_DEVICE_ID+4);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 6: ID = *(unsigned char*)(SUB_DEVICE_ID+5);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 7: ID = *(unsigned char*)(SUB_DEVICE_ID+6);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 8: ID = *(unsigned char*)(SUB_DEVICE_ID+7);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
  default:sprintf(temString, "000");break;
  }
  strcat(DeviceID,temString);
  strcat(IDstring,DeviceID);
}



//获取485传感器的编号ID
//$DTLOG,010001
//获取传感器的ID
void GetSensor485ID(unsigned char ch, char *IDstring)
{
  char DeviceID[20]  = {'\0'};
  char temString[20]  = {'\0'};
  unsigned char ID   = 0;
  strcat(DeviceID,"$DTLOG,010");
  
  switch(ch)
  {
    case 1: ID = *(unsigned char*)(SENSOR_ID_ADDR+0);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 2: ID = *(unsigned char*)(SENSOR_ID_ADDR+1);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 3: ID = *(unsigned char*)(SENSOR_ID_ADDR+2);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 4: ID = *(unsigned char*)(SENSOR_ID_ADDR+3);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 5: ID = *(unsigned char*)(SENSOR_ID_ADDR+4);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 6: ID = *(unsigned char*)(SENSOR_ID_ADDR+5);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 7: ID = *(unsigned char*)(SENSOR_ID_ADDR+6);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
    case 8: ID = *(unsigned char*)(SENSOR_ID_ADDR+7);
            if(ID > 99)
              {sprintf(temString, "%d", ID);}
            else if( 99 > ID && ID >9)
              {sprintf(temString, "0%d", ID);}
            else
              {sprintf(temString, "00%d", ID);}
            break;
  default:sprintf(temString, "000");break;
  }
  strcat(DeviceID,temString);
  strcat(DeviceID,"\r\n");
  strcat(IDstring,DeviceID);
}



//根据子设备ID唤醒子设备，然后等待子设备回传的数据








#ifdef _LOWPOWER_MODE_

//----------------------单点模式定时上发---------------------------------------

/*
  分两种模式：
    1.休眠模式
    2.在线模式
*/

//1.休眠模式
void singel(void)
{
  /*各种初始化*/
  char UpLoadData[600] = {'\0'};//将要上传的数据
  char recTemp[100]={'\0'};
  char PROTOCOL_UpLoadData[700] = {'\0'};//打包后带协议的将要上穿的数据
  unsigned char detectTime = 0;//dtu断线时间
  unsigned char channelType = 0;//传感器类型
  unsigned char ch = 0;
  char cmd485[50] = {'\0'};
  
  BoardInit();
  DefalutConfig();
  while(1)
  {
  /****************************DTU初始化****************************/
    _EINT();
    DtuInit();
    while(1)
    {
      if(DtuStatu() == 1)//连上服务器
        { break; }
      if(DtuStatu() == 0)//没有连上服务器
        {
          detectTime++;
          if(detectTime == 30)
          {
            detectTime = 0; 
            printf("disconnect\r\n");
            //300s后还是没有连上服务器
          }
          delay_ms(1000);
        }
    }
  /************************cmd接收时间，用于在线配置*****************/
    cmdTask();
  /*****************根据传感器类型，进行采集数据*********************/
    for(ch=0; ch < 8;ch++)
    {
        channelType = *(unsigned char*)(CHANNEL_TYPE_ADDR+ch);
        switch(channelType)
        {
          case 0x01://振弦
                FreqInit();
                delay_ms(500);
                Get_Freq_CH(ch+1,recTemp);
            break;
          case 0x02://485传感器
                GetSensor485ID(ch,cmd485);
                Init485();
                delay_ms(1000);
                Get_485_CH(ch+1,cmd485,recTemp);
                memset(cmd485,0,50);
            break;
          case 0x00:break;
          default:break;
        }
        strcat(UpLoadData,recTemp);
        memset(recTemp,0,100);
    }
  /*****************是否在线，不在线则存储起来***********************/
    if(DtuStatu() == 0)
    {
      /*存储数据*/
    }
  /*****************在线则将数据上发*********************************/
    //flash是否存有数据，先判断有没有数据在flash里面，大于数据包长度则进行分包上传
    if(DtuStatu() == 1)
    {
        if( *(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 1 )//加协议传输
          {
            packData(UpLoadData, getDataLength(UpLoadData,600), PROTOCOL_UpLoadData);
            UartStringLength(UART_0, PROTOCOL_UpLoadData, getDataLength(PROTOCOL_UpLoadData,700));
            memset(UpLoadData ,'\0',600);
            memset(PROTOCOL_UpLoadData ,'\0',700);
          }
        if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 0)//不加协议传输
          {
            UartStringLength(UART_0, UpLoadData, getDataLength(UpLoadData,600));
            memset( UpLoadData , '\0', 600 );
          }
        delay_ms(500);
    }
  /*****************进入休眠模式，等待定时唤醒***********************/
    LowperMeneagement();
  }
}
#endif











#ifdef _ONLINE_MODE_
//2.在线模式
void singel(void)
{
  /*各种初始化*/
  char UpLoadData[600] = {'\0'};//将要上传的数据
  char recTemp[100]={'\0'};
  char PROTOCOL_UpLoadData[700] = {'\0'};//打包后带协议的将要上穿的数据
  unsigned char detectTime = 0;//dtu断线时间
  unsigned char channelType = 0;//传感器类型
  unsigned char ch = 0;
  char cmd485[50] = {'\0'};
  
  BoardInit();
  DefalutConfig();
  /*DTU初始化*/
DTU_INIT:
  _EINT();
  DtuInit();
  while(1)
  {
    if(DtuStatu() == 1)//连上服务器
      { break; }
    if(DtuStatu() == 0)//没有连上服务器
      {
        detectTime++;
        if(detectTime == 30)
        { 
          detectTime = 0; 
          printf("disconnect\r\n");
          goto DTU_INIT;
        }
        delay_ms(1000);
      }
  }
  while(1)
  {
    if(MeasureTimeFlag == 1)//采集时间到了
    {
      MeasureTimeFlag = 0;
      /**********************根据传感器类型，进行采集数据********************/
        for(ch=0; ch < 8;ch++)
        {
            channelType = *(unsigned char*)(CHANNEL_TYPE_ADDR+ch);
            switch(channelType)
            {
              case 0x01://振弦
                    FreqInit();
                    delay_ms(500);
                    Get_Freq_CH(ch+1,recTemp);
                break;
              case 0x02://485传感器
                    GetSensor485ID(ch,cmd485);
                    Init485();
                    delay_ms(1000);
                    Get_485_CH(ch+1,cmd485,recTemp);
                    memset(cmd485,0,50);
                break;
              case 0x00:break;
              default:break;
            }
            strcat(UpLoadData,recTemp);
            memset(recTemp,0,100);
        }
      /*********************是否在线，不在线则存储起来*********************/
       
        if(DtuStatu() == 0)
        {
          /*存储*/
          goto DTU_INIT;
        }
      //在线则将数据上发
        // 先判断有没有数据在flash里面，大于数据包长度则进行分包上传
        if(DtuStatu() == 1)
        {
            if( *(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 1 )//加协议传输
              {
                packData(UpLoadData, getDataLength(UpLoadData,300), PROTOCOL_UpLoadData);
                UartStringLength(UART_0, PROTOCOL_UpLoadData, getDataLength(PROTOCOL_UpLoadData,400));
                memset(UpLoadData ,'\0',300);
                memset(PROTOCOL_UpLoadData ,'\0',400);
              }
            if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 0)//不加协议传输
              {
                UartStringLength(UART_0, UpLoadData, getDataLength(UpLoadData,300));
                memset( UpLoadData , '\0', 300 );
              }
            delay_ms(500);
        }
    }
    else//采集时间没有到
    {
      if(DtuStatu() == 1)
        {
          /*********************cmd接收时间，用于在线配置*********************/
          cmdTask();
        }
      else
      {goto DTU_INIT;}
    }
  }
}
#endif





#ifdef _SUB_DEVICE_
//组网模式下的子设备的工作
void singel(void)
{
 /*************************************上电配置***************************************/
  while(1)
  {
    /*************************************休眠模式等待被唤醒***************************/
  
    /*************************************唤醒后将数据回传到主设备**********************/
    
    
  }
}

#endif


#ifdef _MAIN_DEVICE_
//组网模式下的主设备的工作
void singel(void)
{
  /*各种初始化*/
  char UpLoadData[600] = {'\0'};//将要上传的数据
  char recTemp[100]={'\0'};
  char PROTOCOL_UpLoadData[700] = {'\0'};//打包后带协议的将要上穿的数据
  unsigned char detectTime = 0;//dtu断线时间
  unsigned char channelType = 0;//传感器类型
  unsigned char ch = 0;
  char cmd485[50] = {'\0'};
  char subID[50] = {'\0'};
  
  BoardInit();
  DefalutConfig();
  while(1)
  {
  /****************************DTU初始化****************************/
    _EINT();
    DtuInit();
    while(1)
    {
      if(DtuStatu() == 1)//连上服务器
        { break; }
      if(DtuStatu() == 0)//没有连上服务器
        {
          detectTime++;
          if(detectTime == 30)
          {
            detectTime = 0; 
            printf("disconnect\r\n");
            //300s后还是没有连上服务器
          }
          delay_ms(1000);
        }
    }
  /************************cmd接收时间，用于在线配置*****************/
    cmdTask();
  /*****************根据传感器类型，进行采集数据*********************/
    for(ch=0; ch < 8;ch++)
    {
        channelType = *(unsigned char*)(CHANNEL_TYPE_ADDR+ch);
        switch(channelType)
        {
          case 0x01://振弦
                FreqInit();
                delay_ms(500);
                Get_Freq_CH(ch+1,recTemp);
            break;
          case 0x02://485传感器
                GetSensor485ID(ch,cmd485);
                Init485();
                delay_ms(1000);
                Get_485_CH(ch+1,cmd485,recTemp);
                memset(cmd485,0,50);
            break;
          case 0x00:break;
          default:break;
        }
        strcat(UpLoadData,recTemp);
        memset(recTemp,0,100);
    }
  /************************唤醒子设备，等待其数据回传*****************/
    GetSubDeviceID(ch,subID);
    
    for(ch=0; ch < 8;ch++)
    {
      if(*(unsigned char*)(CHANNEL_TYPE_ADDR+ch) != 0 )
      {
        GetSubDeviceID(ch,subID);
        //唤醒子设备，等待数据回传
        strcat(UpLoadData,recTemp);
        memset(recTemp,0,100);
      }  
    }
    
  /*****************是否在线，不在线则存储起来***********************/
    if(DtuStatu() == 0)
    {
      /*存储数据*/
    }
  /*****************在线则将数据上发*********************************/
    //flash是否存有数据，先判断有没有数据在flash里面，大于数据包长度则进行分包上传
    if(DtuStatu() == 1)
    {
        if( *(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 1 )//加协议传输
          {
            packData(UpLoadData, getDataLength(UpLoadData,600), PROTOCOL_UpLoadData);
            UartStringLength(UART_0, PROTOCOL_UpLoadData, getDataLength(PROTOCOL_UpLoadData,700));
            memset(UpLoadData ,'\0',600);
            memset(PROTOCOL_UpLoadData ,'\0',700);
          }
        if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 0)//不加协议传输
          {
            UartStringLength(UART_0, UpLoadData, getDataLength(UpLoadData,600));
            memset( UpLoadData , '\0', 600 );
          }
        delay_ms(500);
    }
  /*****************进入休眠模式，等待定时唤醒***********************/
    LowperMeneagement();
  }
}

#endif