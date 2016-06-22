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


extern unsigned char MeasureTimeFlag;//�������ݱ�־






void DefalutConfig(void)
{
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
    
    //Ĭ��ͨ�����ͣ�0X01:vw  0X02:485
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
}

void BoardInit(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();
  /*������Դ*/
  PowerInit();
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_ON;
  LED(1);
  delay_ms(1000);
  LED(0);
  SetRtc(0x2016,0x05,0x09,0x01,0x08,0x50,0x48);
}



//��ȡ���豸�ı��ID
//SCT16001
//��ȡ���豸���豸ID
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



//��ȡ485�������ı��ID
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



//�������豸ID�������豸��Ȼ��ȴ����豸�ش�������








#ifdef _LOWPOWER_MODE_

//----------------------����ģʽ��ʱ�Ϸ�---------------------------------------

/*
  ������ģʽ��
    1.����ģʽ
    2.����ģʽ
*/

//1.����ģʽ
void singel(void)
{
  /*���ֳ�ʼ��*/
  char UpLoadData[600] = {'\0'};//��Ҫ�ϴ�������
  char recTemp[100]={'\0'};
  char PROTOCOL_UpLoadData[700] = {'\0'};//������Э��Ľ�Ҫ�ϴ�������
  unsigned char detectTime = 0;//dtu����ʱ��
  unsigned char channelType = 0;//����������
  unsigned char ch = 0;
  char cmd485[50] = {'\0'};
  
  BoardInit();
  DefalutConfig();
  while(1)
  {
  /****************************DTU��ʼ��****************************/
    _EINT();
    DtuInit();
    while(1)
    {
      if(DtuStatu() == 1)//���Ϸ�����
        { break; }
      if(DtuStatu() == 0)//û�����Ϸ�����
        {
          detectTime++;
          if(detectTime == 30)
          {
            detectTime = 0; 
            printf("disconnect\r\n");
            //300s����û�����Ϸ�����
          }
          delay_ms(1000);
        }
    }
  /************************cmd����ʱ�䣬������������*****************/
    cmdTask();
  /*****************���ݴ��������ͣ����вɼ�����*********************/
    for(ch=0; ch < 8;ch++)
    {
        channelType = *(unsigned char*)(CHANNEL_TYPE_ADDR+ch);
        switch(channelType)
        {
          case 0x01://����
                FreqInit();
                delay_ms(500);
                Get_Freq_CH(ch+1,recTemp);
            break;
          case 0x02://485������
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
  /*****************�Ƿ����ߣ���������洢����***********************/
    if(DtuStatu() == 0)
    {
      /*�洢����*/
    }
  /*****************�����������Ϸ�*********************************/
    //flash�Ƿ�������ݣ����ж���û��������flash���棬�������ݰ���������зְ��ϴ�
    if(DtuStatu() == 1)
    {
        if( *(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 1 )//��Э�鴫��
          {
            packData(UpLoadData, getDataLength(UpLoadData,600), PROTOCOL_UpLoadData);
            UartStringLength(UART_0, PROTOCOL_UpLoadData, getDataLength(PROTOCOL_UpLoadData,700));
            memset(UpLoadData ,'\0',600);
            memset(PROTOCOL_UpLoadData ,'\0',700);
          }
        if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 0)//����Э�鴫��
          {
            UartStringLength(UART_0, UpLoadData, getDataLength(UpLoadData,600));
            memset( UpLoadData , '\0', 600 );
          }
        delay_ms(500);
    }
  /*****************��������ģʽ���ȴ���ʱ����***********************/
    LowperMeneagement();
  }
}
#endif











#ifdef _ONLINE_MODE_
//2.����ģʽ
void singel(void)
{
  /*���ֳ�ʼ��*/
  char UpLoadData[600] = {'\0'};//��Ҫ�ϴ�������
  char recTemp[100]={'\0'};
  char PROTOCOL_UpLoadData[700] = {'\0'};//������Э��Ľ�Ҫ�ϴ�������
  unsigned char detectTime = 0;//dtu����ʱ��
  unsigned char channelType = 0;//����������
  unsigned char ch = 0;
  char cmd485[50] = {'\0'};
  
  BoardInit();
  DefalutConfig();
  /*DTU��ʼ��*/
DTU_INIT:
  _EINT();
  DtuInit();
  while(1)
  {
    if(DtuStatu() == 1)//���Ϸ�����
      { break; }
    if(DtuStatu() == 0)//û�����Ϸ�����
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
    if(MeasureTimeFlag == 1)//�ɼ�ʱ�䵽��
    {
      MeasureTimeFlag = 0;
      /**********************���ݴ��������ͣ����вɼ�����********************/
        for(ch=0; ch < 8;ch++)
        {
            channelType = *(unsigned char*)(CHANNEL_TYPE_ADDR+ch);
            switch(channelType)
            {
              case 0x01://����
                    FreqInit();
                    delay_ms(500);
                    Get_Freq_CH(ch+1,recTemp);
                break;
              case 0x02://485������
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
      /*********************�Ƿ����ߣ���������洢����*********************/
       
        if(DtuStatu() == 0)
        {
          /*�洢*/
          goto DTU_INIT;
        }
      //�����������Ϸ�
        // ���ж���û��������flash���棬�������ݰ���������зְ��ϴ�
        if(DtuStatu() == 1)
        {
            if( *(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 1 )//��Э�鴫��
              {
                packData(UpLoadData, getDataLength(UpLoadData,300), PROTOCOL_UpLoadData);
                UartStringLength(UART_0, PROTOCOL_UpLoadData, getDataLength(PROTOCOL_UpLoadData,400));
                memset(UpLoadData ,'\0',300);
                memset(PROTOCOL_UpLoadData ,'\0',400);
              }
            if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 0)//����Э�鴫��
              {
                UartStringLength(UART_0, UpLoadData, getDataLength(UpLoadData,300));
                memset( UpLoadData , '\0', 300 );
              }
            delay_ms(500);
        }
    }
    else//�ɼ�ʱ��û�е�
    {
      if(DtuStatu() == 1)
        {
          /*********************cmd����ʱ�䣬������������*********************/
          cmdTask();
        }
      else
      {goto DTU_INIT;}
    }
  }
}
#endif





#ifdef _SUB_DEVICE_
//����ģʽ�µ����豸�Ĺ���
void singel(void)
{
 /*************************************�ϵ�����***************************************/
  while(1)
  {
    /*************************************����ģʽ�ȴ�������***************************/
  
    /*************************************���Ѻ����ݻش������豸**********************/
    
    
  }
}

#endif


#ifdef _MAIN_DEVICE_
//����ģʽ�µ����豸�Ĺ���
void singel(void)
{
  /*���ֳ�ʼ��*/
  char UpLoadData[600] = {'\0'};//��Ҫ�ϴ�������
  char recTemp[100]={'\0'};
  char PROTOCOL_UpLoadData[700] = {'\0'};//������Э��Ľ�Ҫ�ϴ�������
  unsigned char detectTime = 0;//dtu����ʱ��
  unsigned char channelType = 0;//����������
  unsigned char ch = 0;
  char cmd485[50] = {'\0'};
  char subID[50] = {'\0'};
  
  BoardInit();
  DefalutConfig();
  while(1)
  {
  /****************************DTU��ʼ��****************************/
    _EINT();
    DtuInit();
    while(1)
    {
      if(DtuStatu() == 1)//���Ϸ�����
        { break; }
      if(DtuStatu() == 0)//û�����Ϸ�����
        {
          detectTime++;
          if(detectTime == 30)
          {
            detectTime = 0; 
            printf("disconnect\r\n");
            //300s����û�����Ϸ�����
          }
          delay_ms(1000);
        }
    }
  /************************cmd����ʱ�䣬������������*****************/
    cmdTask();
  /*****************���ݴ��������ͣ����вɼ�����*********************/
    for(ch=0; ch < 8;ch++)
    {
        channelType = *(unsigned char*)(CHANNEL_TYPE_ADDR+ch);
        switch(channelType)
        {
          case 0x01://����
                FreqInit();
                delay_ms(500);
                Get_Freq_CH(ch+1,recTemp);
            break;
          case 0x02://485������
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
  /************************�������豸���ȴ������ݻش�*****************/
    GetSubDeviceID(ch,subID);
    
    for(ch=0; ch < 8;ch++)
    {
      if(*(unsigned char*)(CHANNEL_TYPE_ADDR+ch) != 0 )
      {
        GetSubDeviceID(ch,subID);
        //�������豸���ȴ����ݻش�
        strcat(UpLoadData,recTemp);
        memset(recTemp,0,100);
      }  
    }
    
  /*****************�Ƿ����ߣ���������洢����***********************/
    if(DtuStatu() == 0)
    {
      /*�洢����*/
    }
  /*****************�����������Ϸ�*********************************/
    //flash�Ƿ�������ݣ����ж���û��������flash���棬�������ݰ���������зְ��ϴ�
    if(DtuStatu() == 1)
    {
        if( *(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 1 )//��Э�鴫��
          {
            packData(UpLoadData, getDataLength(UpLoadData,600), PROTOCOL_UpLoadData);
            UartStringLength(UART_0, PROTOCOL_UpLoadData, getDataLength(PROTOCOL_UpLoadData,700));
            memset(UpLoadData ,'\0',600);
            memset(PROTOCOL_UpLoadData ,'\0',700);
          }
        if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 0)//����Э�鴫��
          {
            UartStringLength(UART_0, UpLoadData, getDataLength(UpLoadData,600));
            memset( UpLoadData , '\0', 600 );
          }
        delay_ms(500);
    }
  /*****************��������ģʽ���ȴ���ʱ����***********************/
    LowperMeneagement();
  }
}

#endif