#include <msp430.h>
#include "test.h"
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
#include "dtu.h"
#include "rf.h"
#include <stdio.h>



char sensorCH8[100];
char timeCH8[50];
char CH8Cmd[]={0x55,0xaa,0x00,0x0e,0x04,0x00,0x00};//ˮ׼�ǵ�����
unsigned int detectCH8Times = 0;
unsigned char measureCH8Time = 0;

extern LoopRAMType Uart1loop;//����0���λ���(���ڴ˴�Ϊʲô����ָ���˼����ָ�벻�����ڴ棬����һ���ṹ�����ʹ���ڴ�)
extern long Uart1time;


unsigned char SyncTime(char *device)
{
    unsigned int retry=0;
    unsigned char ret = 0;
    char syncResult[50]={'\0'};
    RFString(device);
    //printf("$DTLOG,010015\r\n");
    delay_ms(1000);
    while(1)
    {
      if( (Uart1loop.LoopDatLength != 0) && ( (GetTick()- Uart1time) > 5))      //������յ�DTU�ظ�������
        {
          LoopRAMReadLength(&Uart1loop, syncResult, Uart1loop.LoopDatLength);   //��ȡ�ظ�������
          if(strstr(syncResult, "$DTLOG,010015,TIME,OK") != 0)                  //�ӵ�����ȷ�Ļظ�
          { memset(syncResult,'\0',50); ret = 1;break; }
          else
          { memset(syncResult,'\0',50); ret = 0;break; }
        }
      else//3s��û������
        {
          retry++;
          delay_ms(10);
          if(retry == 300)
          { memset(syncResult,'\0',50); retry = 0; ret = 0; break; }
        }
    }
    return ret;//���ز����Ľ��״̬���ɹ�����ʧ��
}



void TaskCH8(void)
{
  while(1)
  {
    if( DtuStatu() == 1 )
    {
      if(SyncTime("$DTDTLOG,010015\r\n") == 1)
      {
        /*
        //����
        //��ȡ�ֻ�����        
        //�ϴ���������
        */
        break;
      }
    }
    else
    {
      detectCH8Times++;
      if(detectCH8Times == 30)
      {detectCH8Times = 0; printf("disconnect\r\n");break;}
      delay_ms(1000);
      printf("offline...\r\n");
    }
  }
}







void ch8_dtu_rf(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();//ϵͳʱ��Ƭ
  PowerInit();
  PWR_ON;
  CORE_PWR_ON;
  COLL_PWR_ON;
  P1DIR |= BIT1;
  P1OUT &= ~BIT1;
  
  
  delay_ms(1000);
  DtuInit();//�ⷢDTU      usart0
  Init485();//485 ���� RF  usart1
  FreqInit();//����
  SetRtc(0x2016,0x04,0x11,0x01,0x23,0x59,0x48);//��һ���ϵ�����õ�ʱ��
  
  
  while(1)
  {
      cmdTask();
      
      TaskCH8();
      
      LowPowerEntry();
      delay_ms(1000);
      DtuInit();//�ⷢDTU      usart0
      Init485();//485 ���� RF  usart1
      FreqInit();//����
  }
  
}


