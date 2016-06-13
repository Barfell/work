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





void Task485(char *dat)
{
  char retData[300] ={'\0'};
  char retTemp[150] = {'\0'};
  char time485[50] = {'\0'};//获取485传感器数据的时间戳
  unsigned char measure485Times = 0;//测量尝试次数
  char value485[100] = {'\0'};//485传感器的测量数据
  char cmd485[30] = {'\0'};//485传感器的命令
  float vol = 0.0;
  
  unsigned int wakeTime = 0;
  
  GetSensor485ID(SUB_NUM,cmd485);
  
  //printf("sensor id:%s\r\n",cmd485);
  
  
  //获取电源电压
  SDInit();
  delay_ms(1000);
  vol = Get_INNER_Voltage();
  SDOff();
  
  while(1)
  {
    if( Get485(cmd485,value485) == 1 )
      {
        GetRtc(time485);
        sprintf(retTemp,"#%s-time:%s#%s-votagle:%.2fV",MACHINE_ID,time485,MACHINE_ID,vol);
        strcat(retData,retTemp);
        memset(retTemp,0,150);
        
        wakeTime = *(unsigned char*)INTERVAL_TIME_ADDR * 256 + *(unsigned char*)(INTERVAL_TIME_ADDR+1);
        sprintf(retTemp,"#%s-interval:%dMin",MACHINE_ID,wakeTime);
        strcat(retData,retTemp);
        memset(retTemp,0,150);

        sprintf(retTemp,"#%s-CH1:%s",MACHINE_ID,value485);
        strcat(retData,retTemp);
        memset(retTemp,0,150);
        
        
        memcpy(dat,retData,strlen(retData));
        memset(time485,'\0',50);
        memset(value485,'\0',100);
        delay_ms(3000);
        break;
      }
    else
     {
        measure485Times++;
        if(measure485Times == 2)
          {
            GetRtc(time485);
            sprintf(retTemp,"#%s-time:%s#%s-votagle:%.2fV",MACHINE_ID,time485,MACHINE_ID,vol);
            strcat(retData,retTemp);
            memset(retTemp,0,150);
            wakeTime = *(unsigned char*)INTERVAL_TIME_ADDR * 256 + *(unsigned char*)(INTERVAL_TIME_ADDR+1);
            sprintf(retTemp,"#%s-interval:%dMin",MACHINE_ID,wakeTime);
            strcat(retData,retTemp);
            memset(retTemp,0,150);

            sprintf(retTemp,"#%s-CH1:%s",MACHINE_ID,value485);
            strcat(retData,retTemp);
            memset(retTemp,0,150);
            
            
            memcpy(dat,retData,strlen(retData));
            measure485Times = 0;
            memset(time485,'\0',50);
            memset(value485,'\0',100);
            break;
          }
        memset(time485,'\0',50);
        delay_ms(3000);
     }
  }
}


void FreqTask(char *dat)
{
  char retData[200] ={'\0'};
  char retTemp[150] = {'\0'};
  char timevw[50]= {'\0'};//获取VW传感器数据的时间戳
  unsigned char measureVWTime = 0;//尝试进行测量的次数
  float measureFreq = 0.0;//VW测量结果
  float vol = 0.0;//电源电压
  unsigned int wakeTime = 0;
  float VWtemp = 0.0;

  
  //获取电源电压
  SDInit();
  delay_ms(1000);
  vol = Get_INNER_Voltage();
  SDOff();
  
  VWtemp = Get_VW_Voltage();//电压
  //printf("vol:%f\r\n",VWtemp);
  VWtemp = 9950/VWtemp - 21290;//电阻
  //printf("res:%f\r\n",VWtemp);
  VWtemp = GetNTCTemperature(VWtemp);//温度
  //printf("temp:%f\r\n",VWtemp);
  
  while(1)
  {
    measureFreq = GetFreq();
    if( measureFreq != 0 )
      {
            GetRtc(timevw);
            sprintf(retTemp,"#%s-time:%s#%s-votagle:%.2fV",MACHINE_ID,timevw,MACHINE_ID,vol);
            strcat(retData,retTemp);
            memset(retTemp,0,150);
            
            wakeTime = *(unsigned char*)INTERVAL_TIME_ADDR * 256 + *(unsigned char*)(INTERVAL_TIME_ADDR+1);
            sprintf(retTemp,"#%s-interval:%dMin",MACHINE_ID,wakeTime);
            strcat(retData,retTemp);
            memset(retTemp,0,150);

            sprintf(retTemp,"#%s-CH1:F-%.2f T-%.2f",MACHINE_ID,measureFreq,VWtemp);
            strcat(retData,retTemp);
            memset(retTemp,0,150);
        memcpy(dat,retData,strlen(retData));
        break;
      }
    else
     {
        measureVWTime++;
        if(measureVWTime == 2)
          {
            GetRtc(timevw);
            sprintf(retTemp,"#%s-time:%s#%s-votagle:%.2fV",MACHINE_ID,timevw,MACHINE_ID,vol);
            strcat(retData,retTemp);
            memset(retTemp,0,150);
            
            wakeTime = *(unsigned char*)INTERVAL_TIME_ADDR * 256 + *(unsigned char*)(INTERVAL_TIME_ADDR+1);
            sprintf(retTemp,"#%s-interval:%dMin",MACHINE_ID,wakeTime);
            strcat(retData,retTemp);
            memset(retTemp,0,150);

            sprintf(retTemp,"#%s-CH1:F-%.2f T-%.2f",MACHINE_ID,measureFreq,VWtemp);
            strcat(retData,retTemp);
            memset(retTemp,0,150);
            memcpy(dat,retData,strlen(retData));
            measureVWTime = 0;
            memset(timevw,'\0',50);
            break;
          }
        delay_ms(500);
     }
  }
}




















/***************************************************************
                主要的任务
****************************************************************
*/
void signel_Task(void)
{
  char UpLoadData[500] = {'\0'};//将要上传的数据
  char PROTOCOL_UpLoadData[600] = {'\0'};//打包后带协议的将要上穿的数据
  unsigned char detectTime = 0;//dtu断线时间
  
  
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();
  //默认系统时间
  SetRtc(0x2016,0x05,0x09,0x01,0x08,0x50,0x48);
  
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
    
    //默认通道类型：0X00:vw  0X01:485
    FlashInit();
    FlashEreaseSector(CHANNEL_TYPE_ADDR);
    FlashWriteByte(CHANNEL_TYPE_ADDR+0,0x00);
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
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  /*开启电源*/
  PowerInit();
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_OFF;
  LED(1);
  delay_ms(2000);
  LED(0);

  while(1)
  {
      PWR_ON;
      COLL_PWR_OFF;
      TRAN_PWR_ON;
/*--------------------- 初始化通信模块 -----------------------------------*/
      if(*(unsigned char*)(CONNECT_TYPE_ADDR+0) == 1)//DTU
        {
          _EINT();
          DtuInit();
          while(1)
          {
            if(DtuStatu() == 1)//连上服务器
              { break; }
            if(DtuStatu() == 0)//没有连上服务器
              {
                delay_ms(1000);
                detectTime++;
                if(detectTime == 180)
                { 
                  detectTime = 0; 
                  goto DISCONNECT;
                }
              }
          }
        }
      if(*(unsigned char*)(CONNECT_TYPE_ADDR+0) == 0)//RF
        {
          RFInit();
          delay_ms(1000);
        }
       

    //fe 53 43 54 31 36 30 30 33 0f 20 16 05 13 05 08 50 00 fe
/*-------------同步时间或者等待其他命令---------------------------------*/
      cmdTask();
      

      
      PWR_ON;
      COLL_PWR_ON;
      TRAN_PWR_OFF;
/*---------------- 数据采集-------CH0 ----------------------------------*/
      if(*(unsigned char*)(CHANNEL_TYPE_ADDR+SUB_NUM-1) == 1)//485
        {
          Init485();
          Task485(UpLoadData);
        }
      if(*(unsigned char*)(CHANNEL_TYPE_ADDR+SUB_NUM-1) == 0)//vw
        {
          FreqInit();
          FreqTask(UpLoadData);
        }

      
      
      
      
      
      PWR_ON;
      COLL_PWR_OFF;
      TRAN_PWR_ON;
      RFInit();
      delay_ms(1000);
/*---------------------------上传数据-----------------------------------*/
      if( *(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 1 )//加协议传输
        {
          packData(UpLoadData, getDataLength(UpLoadData,300), PROTOCOL_UpLoadData);
          UartStringLength(UART_0, PROTOCOL_UpLoadData, getDataLength(PROTOCOL_UpLoadData,600));
          memset(UpLoadData ,'\0',500);
          memset(PROTOCOL_UpLoadData ,'\0',600);
        }
      if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 0)//不加协议传输
        {
          UartStringLength(UART_0, UpLoadData, getDataLength(UpLoadData,500));
          memset( UpLoadData , '\0', 500 );
        }
      delay_ms(1000);
    TRAN_PWR_OFF;  
      
DISCONNECT:
      /*固定一段时间上传数据，唤醒一次判断一次是否已经到达上传数据的时间*/
      LowperMeneagement();//低功耗
      delay_ms(500);
  }
}

