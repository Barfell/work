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
#include "rain.h"
#include "ramloop.h"
#include "key.h"
#include "ecc.h"
#include "sst.h"
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
  unsigned char flashtemp[50]={0};
  
  unsigned long Jedec = 0;
  unsigned char CHPIP_ID = 0;
  
  
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
  
  SST_init();
  SST_Chip_Erase();
  
  

  while(1)
  {
      SST_Chip_Erase();
      SST_Word_Program(RAIN_COUNT_ADDR,0);//初始化雨量条数。刚开始为0
      
      Jedec = SST_Jedec_ID_Read();
      CHPIP_ID = SST_Read_ID(0x01);
      printf("JEDECID:%d\r\n",Jedec);
      printf("CHPIP_ID:%d\r\n",CHPIP_ID);
    
    
      StoreRain();
      delay_ms(1000);
      StoreRain();
      ReadRain(RAIN_CONTENT_ADDR,flashtemp,2);
      printf("rain:%s\r\n",flashtemp);
      
      memset(flashtemp,0,50);
      delay_ms(3000);
  }
}

