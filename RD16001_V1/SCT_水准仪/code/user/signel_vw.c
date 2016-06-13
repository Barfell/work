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



char timevw[50];
unsigned char measureVWTime = 0;
float measureFreq;


void FreqTask(void)
{
  while(1)
  {
    measureFreq = GetFreq();
    if( measureFreq != 0 )
      {
        GetRtc(timevw);
        printf("%s\r\n",timevw);
        printf("freq is :%0.2f\r\n",measureFreq);
        delay_ms(3000);
        break;
      }
    else
     {
        measureVWTime++;
        if(measureVWTime == 5)
          {
            measureVWTime = 0;
            memset(timevw,'\0',50);
            break;
          }
        printf("measure\r\n");
        GetRtc(timevw);
        printf("%s\r\n",timevw);
        memset(timevw,'\0',50);
        delay_ms(5000);
     }
  }
}

void signel_vw(void)
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
  
  RFInit();
  _EINT();
  delay_ms(1000);
  FreqInit();
  delay_ms(1000);
  SetRtc(0x2016,0x04,0x11,0x01,0x23,0x59,0x48);//第一次上电后设置的时间
  
  while(1)
  {
      cmdTask();
      
      FreqTask();
      
      LowPowerEntry();
      
      Init485();
      RFInit();
      _EINT();
      delay_ms(1000);
  }
}

