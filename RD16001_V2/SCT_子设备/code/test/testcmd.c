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

                ��Ҫ������
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
  

  /*Ĭ��ϵͳʱ��*/
  SetRtc(0x2016,0x04,0x11,0x01,0x23,0x59,0x48);
  
  
  /*������Դ*/
  PowerInit();
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_ON;
  
  
  /*�豸���ӷ�ʽ*/
  //Ĭ����RF�����ڳ������á�������������
  RFInit();
  _EINT();

  delay_ms(1000);
  printf("init ok.....\r\n");
  
 
  while(1)
  {      
   
      cmdTask();
  }
}

