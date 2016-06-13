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
//��ȡ��������ID
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
  char time485[50] = {'\0'};//��ȡ485���������ݵ�ʱ���
  unsigned char measure485Times = 0;//�������Դ���
  char value485[100] = {'\0'};//485�������Ĳ�������
  char cmd485[30] = {'\0'};//485������������
  float vol = 0.0;
  
  unsigned int wakeTime = 0;
  
  GetSensor485ID(SUB_NUM,cmd485);
  
  //printf("sensor id:%s\r\n",cmd485);
  
  
  //��ȡ��Դ��ѹ
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
  char timevw[50]= {'\0'};//��ȡVW���������ݵ�ʱ���
  unsigned char measureVWTime = 0;//���Խ��в����Ĵ���
  float measureFreq = 0.0;//VW�������
  float vol = 0.0;//��Դ��ѹ
  unsigned int wakeTime = 0;
  float VWtemp = 0.0;

  
  //��ȡ��Դ��ѹ
  SDInit();
  delay_ms(1000);
  vol = Get_INNER_Voltage();
  SDOff();
  
  VWtemp = Get_VW_Voltage();//��ѹ
  //printf("vol:%f\r\n",VWtemp);
  VWtemp = 9950/VWtemp - 21290;//����
  //printf("res:%f\r\n",VWtemp);
  VWtemp = GetNTCTemperature(VWtemp);//�¶�
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
                ��Ҫ������
****************************************************************
*/
void signel_Task(void)
{
  char UpLoadData[500] = {'\0'};//��Ҫ�ϴ�������
  char PROTOCOL_UpLoadData[600] = {'\0'};//������Э��Ľ�Ҫ�ϴ�������
  unsigned char detectTime = 0;//dtu����ʱ��
  
  
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();
  //Ĭ��ϵͳʱ��
  SetRtc(0x2016,0x05,0x09,0x01,0x08,0x50,0x48);
  
  if( 0xAA != *(unsigned char *)DEVICE_FIRST_TIME_POWERON_ADDR)
  {
    /*�Ƿ��ǵ�һ�ο���*/
    FlashInit();
    FlashEreaseSector(DEVICE_FIRST_TIME_POWERON_ADDR);
    FlashWriteByte(DEVICE_FIRST_TIME_POWERON_ADDR,0xAA);
    
    /*�ɼ�ʱ����*/
    FlashInit();
    FlashEreaseSector(INTERVAL_TIME_ADDR);
    FlashWriteByte(INTERVAL_TIME_ADDR, (unsigned char)( INTERVAL_TIME/256 ) );//�߰�λ
    FlashWriteByte(INTERVAL_TIME_ADDR+1,(unsigned char)(INTERVAL_TIME % 256) ); //�Ͱ�λ
    
    /*cmd�ȴ�ʱ��*/
    FlashInit();
    FlashEreaseSector(CMD_TIME_ADDR);
    FlashWriteByte(CMD_TIME_ADDR, CMD_TIME );
    
    
    /*Ĭ�ϵ��豸��ͨ�����ͺ����ӷ�ʽ*/
    //Ĭ�ϵ����ӷ�ʽ0x00:RF  0x01:dtu
    FlashInit();
    FlashEreaseSector(CONNECT_TYPE_ADDR);
    FlashWriteByte(CONNECT_TYPE_ADDR,0x00);
    
    //Ĭ��ͨ�����ͣ�0X00:vw  0X01:485
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
    
    //Ĭ��ͨ������485�������ı��
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
    
    //Ĭ���ϴ��Ƿ��Э�� 0x00:unprotocol 0x01:protocol
    FlashInit();
    FlashEreaseSector(PROTOCOL_TYPE_ADDR);
    FlashWriteByte(PROTOCOL_TYPE_ADDR,0x00);  
    
    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  /*������Դ*/
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
/*--------------------- ��ʼ��ͨ��ģ�� -----------------------------------*/
      if(*(unsigned char*)(CONNECT_TYPE_ADDR+0) == 1)//DTU
        {
          _EINT();
          DtuInit();
          while(1)
          {
            if(DtuStatu() == 1)//���Ϸ�����
              { break; }
            if(DtuStatu() == 0)//û�����Ϸ�����
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
/*-------------ͬ��ʱ����ߵȴ���������---------------------------------*/
      cmdTask();
      

      
      PWR_ON;
      COLL_PWR_ON;
      TRAN_PWR_OFF;
/*---------------- ���ݲɼ�-------CH0 ----------------------------------*/
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
/*---------------------------�ϴ�����-----------------------------------*/
      if( *(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 1 )//��Э�鴫��
        {
          packData(UpLoadData, getDataLength(UpLoadData,300), PROTOCOL_UpLoadData);
          UartStringLength(UART_0, PROTOCOL_UpLoadData, getDataLength(PROTOCOL_UpLoadData,600));
          memset(UpLoadData ,'\0',500);
          memset(PROTOCOL_UpLoadData ,'\0',600);
        }
      if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 0)//����Э�鴫��
        {
          UartStringLength(UART_0, UpLoadData, getDataLength(UpLoadData,500));
          memset( UpLoadData , '\0', 500 );
        }
      delay_ms(1000);
    TRAN_PWR_OFF;  
      
DISCONNECT:
      /*�̶�һ��ʱ���ϴ����ݣ�����һ���ж�һ���Ƿ��Ѿ������ϴ����ݵ�ʱ��*/
      LowperMeneagement();//�͹���
      delay_ms(500);
  }
}

