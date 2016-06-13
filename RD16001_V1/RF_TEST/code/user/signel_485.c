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



char time485[50] = {'\0'};
unsigned char measure485Times = 0;
char value485[100] = {'\0'};
char cmd485[] = {"$DT,100001"};

void Task485(void)
{
  while(1)
  {

    if( Get485(cmd485,value485) == 1 )
      {
        GetRtc(time485);
        printf("%s\r\n",time485);
        printf("485 is :%s\r\n",value485);
        memset(time485,'\0',50);
        memset(value485,'\0',100);
        delay_ms(3000);
        break;
      }
    else
     {
        measure485Times++;
        if(measure485Times == 5)
          {
            measure485Times = 0;
            memset(time485,'\0',50);
            memset(value485,'\0',100);
            break;
          }
        printf("measure\r\n");
        GetRtc(time485);
        printf("%s\r\n",time485);
        memset(time485,'\0',50);
        delay_ms(5000);
     }
  }
}

void signel_485(void)
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
//  delay_ms(1000);
//  Init485();
//  delay_ms(1000);
//  SetRtc(0x2016,0x04,0x11,0x01,0x23,0x59,0x48);//第一次上电后设置的时间
//  
  while(1)
  {
    delay_ms(2000);
    printf("123456789\r\n");
  }
}

