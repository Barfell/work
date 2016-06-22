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
#include "rain.h"
#include "cmd.h"
#include "ramloop.h"
#include "key.h"
#include "ecc.h"
#include "sst.h"
#include "dtu.h"
#include "rf.h"
#include <stdio.h>
#include <string.h>
#include "includes.h"

unsigned char flashtemp[100]={0};
unsigned char i = 0;
void testrain(void)
{
  
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  /*开启电源*/
  PowerInit();
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_ON;
  RFInit();
  LED(1);
  delay_ms(1000);
  printf("rf init ok.....\r\n");
  printf("Rain test .....\r\n");
  LED(0);
  
  SST_init();
  SST_Chip_Erase();
  SST_Word_Program(RAIN_COUNT_ADDR,0);
  SetRtc(0x2016,0x05,0x09,0x01,0x08,0x50,0x48);
  
  RainInit();//雨量中断
  delay_ms(2000);
  while(1)
  {
    while(1)
    {
      LowPowerGPIO();
      RainInit();//雨量中断
      PowerInit();
      PWR_OFF;
      COLL_PWR_OFF;
      TRAN_PWR_OFF;
      ClkOff();   //进入低功耗之前要把时钟设置好
      __bis_SR_register(LPM3_bits + GIE);
      WDTCTL = WDTPW + WDTHOLD;
      ClkInit();
      /*开启电源*/
      PowerInit();
      PWR_ON;
      COLL_PWR_ON;
      TRAN_PWR_ON;
      RFInit();
      printf("wakeup\r\n");
      SST_init();
      StoreRain();
      delay_ms(1000);
      i = GetRainNum();
      if(i == 4)
        {break;}
    }
    printf("num:%d\r\n",i);
    ReadRain(RAIN_CONTENT_ADDR,flashtemp,i);
    printf("rain:%s\r\n",flashtemp);
    memset(flashtemp,0,100);
    delay_ms(3000);
  }
  
}

