/**************************************************
*
*对雨量计的一些操作
*
***************************************************
*/
#include "msp430.h"
#include <stdio.h>
#include <string.h>
#include "clk.h"
#include "rain.h"
#include "rtc.h"
#include "rf.h"
#include "sst.h"
#include "power.h"
#include "cfg.h"
#include "flash.h"
#include "kernel.h"


//雨量计初始化
void RainInit(void)
{
  P2IFG  = 0;
  P2REN  &= ~BIT7;
  P2DIR  &= ~BIT7;
  P2SEL  &= ~BIT7;
  P2IES  |= BIT7;      //L---H
  P2IFG  = 0;           //CLEAR FLAGS
  P2IE  |=  BIT7;       //ENABLE
  P2IFG  = 0;           //CLEAR FLAGS
  _EINT();              //GLOABLE INTERRUPT
}
//设置雨量条数
void SetRainNum(unsigned long num)
{
  SST_Sector_Erase(RAIN_COUNT_ADDR);
  SST_Word_Program(RAIN_COUNT_ADDR,num);
}
//获取雨量条数
unsigned long GetRainNum(void)
{
 return SST_Word_Read(RAIN_COUNT_ADDR);
}



//2016-04-26-19:24:55|(20byte)
//存储雨量数据，存储一条，雨量条数就增加一条
void StoreRain(void)
{
  unsigned long WriteAddr = 0;
  unsigned long RainNum = 0;
  char rainTime[25];
  
  RainNum = GetRainNum();
  WriteAddr = RainNum*20 + RAIN_CONTENT_ADDR;
  
  GetRtc(rainTime);
  SST_Length_Program(WriteAddr,(unsigned char*)rainTime,20);
  
  SetRainNum(RainNum+1);
}

//读取指定条数的雨量数据
void ReadRain(unsigned long Dst, unsigned char *buf, unsigned char num)
{
  unsigned long RainNum = 0;
  RainNum = GetRainNum();
  if((RainNum > 0) && (RainNum >= num))
  {
    SST_Length_Read(Dst,buf,20*num);
  }
}


void recordRain(void)
{
  unsigned char i;
  unsigned char flashtemp[100]= {0};
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
  printf("num:%d\r\n",i);
  ReadRain(RAIN_CONTENT_ADDR,flashtemp,i);
  printf("rain:%s\r\n",flashtemp);
  memset(flashtemp,0,100);
  delay_ms(1000);
}



#pragma vector=PORT2_VECTOR
__interrupt void gpio1_int(void)
{
  _DINT();//唤醒后需要把中断关闭，防止再次进入中断，造成运行错误
  P2IFG  = 0;
  LPM3_EXIT;//退出休眠
}
