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
#include "ramloop.h"
#include "key.h"
#include "dtu.h"
#include "cfg.h"
#include <stdio.h>



void PowerInit(void)
{
  P1REN &= ~BIT0;
  P1DIR |=  BIT0;                             
  P1OUT &= ~BIT0;     //PWR_CN    
  
  P9REN &= ~BIT5;
  P9DIR |=  BIT5;                             
  P9OUT &= ~BIT5;     //COLL_PWR_CN    
  
  P4REN &= ~BIT4;
  P4DIR |=  BIT4;                             
  P4OUT &= ~BIT4;     //TRAN_PWR_CN    
  
}


extern LoopRAMType Uart0loop;//串口0环形缓冲(关于此处为什么不用指针的思考：指针不分配内存，定义一个结构体则会使用内存)
extern long Uart0time;


unsigned int wakeuptimes = 0;//唤醒次数，用于计算是否到达上传数据的时间间隔
unsigned char UpdateFlag = 0;

unsigned int IntervalTime = (unsigned int)INTERVAL_TIME;

void LowPowerEntry(void)
{
    LowPowerGPIO();
    PowerInit();
    PWR_OFF;
    COLL_PWR_OFF;
    TRAN_PWR_OFF;
    ClkOff();   //进入低功耗之前要把时钟设置好
    __bis_SR_register(LPM3_bits + GIE);
    WDTCTL = WDTPW + WDTHOLD;
    delay_ms(150);
    //clk
    ClkInit();  //推出低功耗后腰将时钟重新设置一下
    wakeuptimes ++;
    IntervalTime = *(unsigned char*)INTERVAL_TIME_ADDR * 256 + *(unsigned char*)(INTERVAL_TIME_ADDR+1);
    if(wakeuptimes == IntervalTime)//到达间隔时间了
      {
        UpdateFlag = 1;
        wakeuptimes = 0;
      }
    else//还没有达到间隔时间
      {
        UpdateFlag = 0;
      }
}

void LowperMeneagement(void)
{
 update_loop:
      LowPowerEntry();
      if(UpdateFlag == 0)
      {
        goto update_loop;
      }
      
      UpdateFlag = 0;
      SysTickInit();
      //moudles
      delay_ms(1000);
      PowerInit();//电源控制GPIO重新初始化配置一下
      //power
      PWR_ON;
}

void LED(unsigned char x)
{
  if(x == 1)
  {
    P5REN &= ~BIT5;
    P5DIR |= BIT5;
    P5OUT |= BIT5;
  }
  if(x == 0)
  {
    P5REN &= ~BIT5;
    P5DIR |= BIT5;
    P5OUT &= ~BIT5;
  }
}


void CH_Select(unsigned char ch)
{
  P3REN &= ~BIT1;
  P3REN &= ~BIT2;
  P3REN &= ~BIT3;
  P3REN &= ~BIT4;
  P3REN &= ~BIT6;
  P3REN &= ~BIT7;
  P5REN &= ~BIT3;
  P5REN &= ~BIT4;
  
  P3DIR |= BIT1;
  P3DIR |= BIT2;
  P3DIR |= BIT3;
  P3DIR |= BIT4;
  P3DIR |= BIT6;
  P3DIR |= BIT7;
  P5DIR |= BIT3;
  P5DIR |= BIT4;
  
  P3OUT &= ~BIT1;
  P3OUT &= ~BIT2;
  P3OUT &= ~BIT3;
  P3OUT &= ~BIT4;
  P3OUT &= ~BIT6;
  P3OUT &= ~BIT7;
  P5OUT &= ~BIT3;
  P5OUT &= ~BIT4;
  
  switch(ch)
  {
  case 1:
    P3OUT |= BIT1;
    P3OUT &= ~BIT2;
    P3OUT &= ~BIT3;
    P3OUT &= ~BIT4;
    P3OUT &= ~BIT6;
    P3OUT &= ~BIT7;
    P5OUT &= ~BIT3;
    P5OUT &= ~BIT4;
    break;
  case 2:
    P3OUT &= ~BIT1;
    P3OUT |= BIT2;
    P3OUT &= ~BIT3;
    P3OUT &= ~BIT4;
    P3OUT &= ~BIT6;
    P3OUT &= ~BIT7;
    P5OUT &= ~BIT3;
    P5OUT &= ~BIT4;
    break;
  case 3:
    P3OUT &= ~BIT1;
    P3OUT &= ~BIT2;
    P3OUT |= BIT3;
    P3OUT &= ~BIT4;
    P3OUT &= ~BIT6;
    P3OUT &= ~BIT7;
    P5OUT &= ~BIT3;
    P5OUT &= ~BIT4;
    break;
 case 4:
    P3OUT &= ~BIT1;
    P3OUT &= ~BIT2;
    P3OUT &= ~BIT3;
    P3OUT |= BIT4;
    P3OUT &= ~BIT6;
    P3OUT &= ~BIT7;
    P5OUT &= ~BIT3;
    P5OUT &= ~BIT4;
    break;
 case 5:
    P3OUT &= ~BIT1;
    P3OUT &= ~BIT2;
    P3OUT &= ~BIT3;
    P3OUT &= ~BIT4;
    P3OUT |= BIT6;
    P3OUT &= ~BIT7;
    P5OUT &= ~BIT3;
    P5OUT &= ~BIT4;
    break;
 case 6:
    P3OUT &= ~BIT1;
    P3OUT &= ~BIT2;
    P3OUT &= ~BIT3;
    P3OUT &= ~BIT4;
    P3OUT &= ~BIT6;
    P3OUT |= BIT7;
    P5OUT &= ~BIT3;
    P5OUT &= ~BIT4;
    break;
 case 7:
    P3OUT &= ~BIT1;
    P3OUT &= ~BIT2;
    P3OUT &= ~BIT3;
    P3OUT &= ~BIT4;
    P3OUT &= ~BIT6;
    P3OUT &= ~BIT7;
    P5OUT &= ~BIT3;
    P5OUT |= BIT4;
    break;
 case 8:
    P3OUT &= ~BIT1;
    P3OUT &= ~BIT2;
    P3OUT &= ~BIT3;
    P3OUT &= ~BIT4;
    P3OUT &= ~BIT6;
    P3OUT &= ~BIT7;
    P5OUT |= BIT3;
    P5OUT &= ~BIT4;
    break;
  default:break;
  }
}

