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
#include "includes.h"
#include "sst25vf064c.h"







/***************************************************************
                主要的任务
****************************************************************
*/
void testsst25(void)
{
  char flashtemp[100]={0};
  long Jedec = 0;
  
  
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();
  //默认系统时间
  SetRtc(0x2016,0x05,0x09,0x01,0x08,0x50,0x48);
  
  
  
  /*开启电源*/
  PowerInit();
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_ON;
  
  RFInit();
  delay_ms(1000);
  printf("sst25vf064c test...\r\n");
  

 
  while(1)
  {
    SST25VF064Init();
    
    printf("sst25vf064c erase...\r\n");
    
    FlashChipErase();
    
    Jedec = JedecIDRead();
    
    printf("%ld\r\n",Jedec);
    
    printf("sst25vf064c write...\r\n");
    
    ExternFlashPageProgram(3,"12345678xxxxx",13);
    
    flashtemp[0] = Read(3);
    flashtemp[1] = Read(4);
    flashtemp[2] = Read(5);
    flashtemp[3] = Read(6);
    flashtemp[4] = Read(7);
    
    printf("read:%s\r\n",flashtemp);
    
    memset(flashtemp,0,100);
    Jedec = 0;
    
    delay_ms(3000);
  }
}

