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







/***************************************************************

                主要的任务
****************************************************************
*/
void testcmd(void)
{
  char UpLoadData[300] = {'\0'};
  char PROTOCOL_UpLoadData[400] = {'\0'};
  
  unsigned char detectTime = 0;
  
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();
  

  /*默认系统时间*/
  SetRtc(0x2016,0x04,0x11,0x01,0x23,0x59,0x48);
  
  
  /*开启电源*/
  PowerInit();
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_ON;
  
  
  /*设备连接方式*/
  //默认是RF，用于出场设置。或者主机设置
  RFInit();
  _EINT();

  delay_ms(1000);
  printf("init ok.....\r\n");
  
 
  while(1)
  {      
   
      cmdTask();
  }
}

