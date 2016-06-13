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






void Task485(char *dat)
{
  char retData[100] ={'\0'};
  char time485[50] = {'\0'};//��ȡ485���������ݵ�ʱ���
  unsigned char measure485Times = 0;//�������Դ���
  char value485[100] = {'\0'};//485�������Ĳ�������
  char cmd485[] = {"$DTLOG,010015\r\n"};//485������������
  float vol = 0.0;
  
  //��ȡ��Դ��ѹ
  SDInit();
  delay_ms(1000);
  while(vol == 0)
    {vol = GetSD16Voltage(4);}
  vol = vol*776.0 /26.1;
  SDOff();
  
  while(1)
  {
    if( Get485(cmd485,value485) == 1 )
      {
        GetRtc(time485);
        sprintf(retData,"#%s\r\n#votagle:%f\r\n#%s\r\n#CH1:%s\r\n",MACHINE_ID, vol, time485, value485);
        memcpy(dat,retData,sizeof(retData));
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
            sprintf(retData,"#%s\r\n#votagle:%f\r\n#%s\r\n#CH1:%s\r\n",MACHINE_ID, vol, time485, value485);
            memcpy(dat,retData,sizeof(retData));
            delay_ms(3000);
            measure485Times = 0;
            memset(time485,'\0',50);
            memset(value485,'\0',100);
            break;
          }
        memset(time485,'\0',50);
        delay_ms(5000);
     }
  }
}


void FreqTask(char *dat)
{
  char retData[100] ={'\0'};
  char timevw[50]= {'\0'};//��ȡVW���������ݵ�ʱ���
  unsigned char measureVWTime = 0;//���Խ��в����Ĵ���
  float measureFreq = 0.0;//VW�������
  float vol = 0.0;//��Դ��ѹ

  //��ȡ��Դ��ѹ
  SDInit();
  delay_ms(500);
  while(vol == 0)
    { vol = GetSD16Voltage(4); }
  vol = vol*776.0 /26.1;
  
  SDOff();
  
  while(1)
  {
    measureFreq = GetFreq();
    if( measureFreq != 0 )
      {
        GetRtc(timevw);
        sprintf(retData,"#%s\r\n#votagle:%f\r\n#%s\r\n#CH1:%0.2f\r\n",MACHINE_ID, vol,timevw, measureFreq);
        memcpy(dat,retData,sizeof(retData));
        //delay_ms(3000);
        break;
      }
    else
     {
        GetRtc(timevw);
        measureVWTime++;
        if(measureVWTime == 2)
          {
            sprintf(retData,"#%s\r\n#votagle:%f\r\n#%s\r\n#CH1:%0.2f\r\n",MACHINE_ID, vol,timevw, measureFreq);
            //printf("%s\r\n",retData);
            memcpy(dat,retData,sizeof(retData));
            //delay_ms(3000);
            measureVWTime = 0;
            memset(timevw,'\0',50);
            break;
          }
        memset(timevw,'\0',50);
        //delay_ms(5000);
     }
  }
}




/***************************************************************
                ��Ҫ������
****************************************************************
*/
void signel_Task(void)
{
  char UpLoadData[300] = {'\0'};//��Ҫ�ϴ�������
  char PROTOCOL_UpLoadData[400] = {'\0'};//������Э��Ľ�Ҫ�ϴ�������
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
    FlashWriteByte(SENSOR_ID_ADDR+0,0x0F);
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
 
  delay_ms(3000);
  while(1)
  {
      PWR_ON;
      COLL_PWR_ON;
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
                if(detectTime == 30)
                { 
                  detectTime = 0; 
                  printf("disconnect\r\n");
                  goto DISCONNECT;
                }
                delay_ms(1000);
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
      

      
      
      printf("1234576xxxxxxxxxxxxxx\r\n");
      printf("1234576xxxxxxxxxxxxxx\r\n");
      printf("1234576xxxxxxxxxxxxxx\r\n");
      
      COLL_PWR_ON;
/*---------------- ���ݲɼ�-------CH0 ------------------------------------*/
      //ͬ��ʱ��ɹ���������ʱ�䳬ʱ
      if(*(unsigned char*)(CHANNEL_TYPE_ADDR+0) == 1)//485
        {
          Init485();
          delay_ms(1000);
          Task485(UpLoadData);
        }
      if(*(unsigned char*)(CHANNEL_TYPE_ADDR+0) == 0)//vw
        {
          FreqInit();
          delay_ms(500);
          FreqTask(UpLoadData);
        }
      COLL_PWR_OFF;

      
/*---------------------------�ϴ�����-----------------------------------*/
      if( *(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 1 )//��Э�鴫��
        {
          packData(UpLoadData, getDataLength(UpLoadData,300), PROTOCOL_UpLoadData);
          UartStringLength(UART_0, PROTOCOL_UpLoadData, getDataLength(PROTOCOL_UpLoadData,400));
          memset(UpLoadData ,'\0',300);
          memset(PROTOCOL_UpLoadData ,'\0',400);
        }
      if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 0)//����Э�鴫��
        {
         // printf("%s\r\n",UpLoadData);
          UartStringLength(UART_0, UpLoadData, getDataLength(UpLoadData,300));
          memset( UpLoadData , '\0', 300 );
        }
      delay_ms(500);
    TRAN_PWR_OFF;  
      
DISCONNECT:
      /*�̶�һ��ʱ���ϴ����ݣ�����һ���ж�һ���Ƿ��Ѿ������ϴ����ݵ�ʱ��*/
      LowperMeneagement();//�͹���
      delay_ms(500);
  }
}

