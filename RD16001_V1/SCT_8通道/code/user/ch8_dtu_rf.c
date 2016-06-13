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
char CH8Cmd[]={0x55,0xaa,0x00,0x0e,0x04,0x00,0x00};//水准仪的命令
unsigned int detectCH8Times = 0;
unsigned char measureCH8Time = 0;

extern LoopRAMType Uart1loop;//串口0环形缓冲(关于此处为什么不用指针的思考：指针不分配内存，定义一个结构体则会使用内存)
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
      if( (Uart1loop.LoopDatLength != 0) && ( (GetTick()- Uart1time) > 5))      //假如接收到DTU回复的数据
        {
          LoopRAMReadLength(&Uart1loop, syncResult, Uart1loop.LoopDatLength);   //读取回复的数据
          if(strstr(syncResult, "$DTLOG,010015,TIME,OK") != 0)                  //接到的正确的回复
          { memset(syncResult,'\0',50); ret = 1;break; }
          else
          { memset(syncResult,'\0',50); ret = 0;break; }
        }
      else//3s后没有数据
        {
          retry++;
          delay_ms(10);
          if(retry == 300)
          { memset(syncResult,'\0',50); retry = 0; ret = 0; break; }
        }
    }
    return ret;//返回测量的结果状态，成功或者失败
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
        //测量
        //获取分机数据        
        //上传到服务器
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
  SysTickInit();//系统时间片
  PowerInit();
  PWR_ON;
  CORE_PWR_ON;
  COLL_PWR_ON;
  P1DIR |= BIT1;
  P1OUT &= ~BIT1;
  
  
  delay_ms(1000);
  DtuInit();//外发DTU      usart0
  Init485();//485 或者 RF  usart1
  FreqInit();//振弦
  SetRtc(0x2016,0x04,0x11,0x01,0x23,0x59,0x48);//第一次上电后设置的时间
  
  
  while(1)
  {
      cmdTask();
      
      TaskCH8();
      
      LowPowerEntry();
      delay_ms(1000);
      DtuInit();//外发DTU      usart0
      Init485();//485 或者 RF  usart1
      FreqInit();//振弦
  }
  
}


