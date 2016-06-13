

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
#include "dtu.h"
#include "rf.h"
#include <stdio.h>
#include <string.h>
#include "includes.h"


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
  LED(0);
  
  
  while(1)
  {
    PWR_ON;
    COLL_PWR_ON;
    TRAN_PWR_OFF;
    
    delay_ms(1000);
    RainInit();//雨量中断
    delay_ms(1000);

    LPM3;
    

    PWR_ON;
    COLL_PWR_ON;
    TRAN_PWR_ON;
    
    LED(1);
    delay_ms(1000);
    printf("init ok.....\r\n");
    delay_ms(1000);
    LED(0);
    
    delay_ms(1000);
    printf("INTERRUPT ok.....\r\n");
    delay_ms(1000);
  }
  
  
}

