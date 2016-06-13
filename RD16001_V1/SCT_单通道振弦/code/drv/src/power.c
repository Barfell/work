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
  P9REN &= ~BIT5;
  P9DIR |=  BIT5;                             
  P9OUT &= ~BIT5;                            
  
  P4REN &= ~BIT2;
  P4REN &= ~BIT3;
  P4DIR |= BIT3+BIT2;                             
  P4OUT &= ~BIT2;                                
  P4OUT &= ~BIT3;
}


extern LoopRAMType Uart0loop;//串口0环形缓冲(关于此处为什么不用指针的思考：指针不分配内存，定义一个结构体则会使用内存)
extern long Uart0time;


unsigned char wakeuptimes = 0;//唤醒次数，用于计算是否到达上传数据的时间间隔
unsigned char UpdateFlag = 0;

unsigned char IntervalTime = INTERVAL_TIME;

void LowPowerEntry(void)
{
    LowPowerGPIO();
    PowerInit();
    PWR_OFF;
    CORE_PWR_OFF;
    COLL_PWR_OFF;
    ClkOff();   //进入低功耗之前要把时钟设置好
    __bis_SR_register(LPM3_bits + GIE);
    WDTCTL = WDTPW + WDTHOLD;
    //clk
    ClkInit();  //推出低功耗后腰将时钟重新设置一下
    wakeuptimes ++;
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
      if(UpdateFlag != 1)
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
      CORE_PWR_ON;
      COLL_PWR_ON;
}
