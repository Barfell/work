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







void Task485(char *dat)
{
  char retData[100] ={'\0'};
  //485
  char time485[50] = {'\0'};//��ȡ485���������ݵ�ʱ���
  unsigned char measure485Times = 0;//�������Դ���
  char value485[100] = {'\0'};//485�������Ĳ�������
  char cmd485[] = {"$DT,100001"};//485������������

  while(1)
  {
    if( Get485(cmd485,value485) == 1 )
      {
        GetRtc(time485);
        sprintf(retData,"#%s\r\n#%s-CH1:%s",time485,SCT_TYPE,value485);
        printf("%s\r\n",retData);
        memcpy(dat,retData,sizeof(retData));
        memset(time485,'\0',50);
        memset(value485,'\0',100);
        delay_ms(3000);
        break;
      }
    else
     {
        GetRtc(time485);
        printf("%s\r\n",time485);
        measure485Times++;
        if(measure485Times == 2)
          {
            sprintf(retData,"#%s\r\n#%s-CH1:%s", time485, SCT_TYPE, value485);
            printf("%s\r\n",retData);
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

  while(1)
  {
    measureFreq = GetFreq();
    if( measureFreq != 0 )
      {
        GetRtc(timevw);
        sprintf(retData,"#%s\r\n#%s-CH1:%0.2f",timevw,SCT_TYPE,measureFreq);
        memcpy(dat,retData,sizeof(retData));
        delay_ms(3000);
        break;
      }
    else
     {
        GetRtc(timevw);
        measureVWTime++;
        if(measureVWTime == 2)
          {
            sprintf(retData,"#%s\r\n#%s-CH1:%0.2f",timevw,SCT_TYPE,measureFreq);
            //printf("%s\r\n",retData);
            memcpy(dat,retData,sizeof(retData));
            delay_ms(3000);
            measureVWTime = 0;
            memset(timevw,'\0',50);
            break;
          }
        memset(timevw,'\0',50);
        delay_ms(5000);
     }
  }
}




/***************************************************************

                ��Ҫ������
****************************************************************
*/
void signel_Task(void)
{
  char UpLoadData[300] = {'\0'};
  char PROTOCOL_UpLoadData[400] = {'\0'};
  
  unsigned char detectTime = 0;
  
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();//ϵͳʱ��Ƭ
  
  /*Ĭ�ϵ��豸��ͨ�����ͺ����ӷ�ʽ*/
  //Ĭ�ϵ��ǣ�RF  8CH VW
  FlashInit();
  FlashEreaseSector(CONNECT_TYPE_ADDR);
  FlashWriteByte(CONNECT_TYPE_ADDR,0x00);
  //Ĭ��ͨ�����ͣ�
  FlashEreaseSector(CHANNEL_TYPE_ADDR);
  FlashWriteByte((int)CHANNEL_TYPE_ADDR+0,0x00);
  FlashWriteByte((int)CHANNEL_TYPE_ADDR+1,0x00);
  FlashWriteByte((int)CHANNEL_TYPE_ADDR+2,0x00);
  FlashWriteByte((int)CHANNEL_TYPE_ADDR+3,0x00);
  FlashWriteByte((int)CHANNEL_TYPE_ADDR+4,0x00);
  FlashWriteByte((int)CHANNEL_TYPE_ADDR+5,0x00);
  FlashWriteByte((int)CHANNEL_TYPE_ADDR+6,0x00);
  FlashWriteByte((int)CHANNEL_TYPE_ADDR+7,0x00);
  //Ĭ���ϴ��Ƿ��Э��
  FlashEreaseSector(PROTOCOL_TYPE_ADDR);
  FlashWriteByte(PROTOCOL_TYPE_ADDR,0x01);  
  /*Ĭ��ϵͳʱ��*/
  SetRtc(0x2016,0x04,0x11,0x01,0x23,0x59,0x48);
  
  
  /*������Դ*/
  PowerInit();
  PWR_ON;
  CORE_PWR_ON;
  COLL_PWR_ON;
  
  
  /*�豸���ӷ�ʽ*/
  //Ĭ����RF�����ڳ������á�������������
  RFInit();
  _EINT();

  delay_ms(1000);
  printf("init ok.....\r\n");
  
 
  while(1)
  {      
      /*-----------------��ʼ��ͨ��ģ��----*/
      if(*(unsigned char*)(CONNECT_TYPE_ADDR+0) == 1)//DTU
        {
          _EINT();
          DtuInit();
          while(1)
          {
            if(DtuStatu() == 1)//���Ϸ�����
              { break;}
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
          _EINT();
          RFInit();
        }
      delay_ms(1000);
      
      /*�ȴ�����ȴ�������ʱ��ͬ����Ϣ*/
      cmdTask();
      
      
      /*--------------���ݲɼ�-------CH0-------*/
      if(*(unsigned char*)(CHANNEL_TYPE_ADDR+0) == 1)//485
      {
        Init485();
        delay_ms(1000);
        Task485(UpLoadData);
      }
      if(*(unsigned char*)(CHANNEL_TYPE_ADDR+0) == 0)//vw
      {
        FreqInit();
        delay_ms(2000);
        FreqTask(UpLoadData);
      }
      /*-------------�ϴ�����---------------*/
      if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 1)//�� Э�鴫��
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
        memset(UpLoadData ,'\0',300);
      }
      
      delay_ms(1000);
      
DISCONNECT:      
      /*�̶�һ��ʱ���ϴ����ݣ�����һ���ж�һ���Ƿ��Ѿ������ϴ����ݵ�ʱ��*/
      LowperMeneagement();//�͹���
      delay_ms(1000);
  }
  
  
  
}

