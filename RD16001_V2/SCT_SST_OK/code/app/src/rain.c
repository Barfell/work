/**************************************************
*
*�������Ƶ�һЩ����
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


//�����Ƴ�ʼ��
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
//������������
void SetRainNum(unsigned long num)
{
  SST_Sector_Erase(RAIN_COUNT_ADDR);
  SST_Word_Program(RAIN_COUNT_ADDR,num);
}
//��ȡ��������
unsigned long GetRainNum(void)
{
 return SST_Word_Read(RAIN_COUNT_ADDR);
}



//2016-04-26-19:24:55|(20byte)
//�洢�������ݣ��洢һ������������������һ��
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

//��ȡָ����������������
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
  /*������Դ*/
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
  _DINT();//���Ѻ���Ҫ���жϹرգ���ֹ�ٴν����жϣ�������д���
  P2IFG  = 0;
  LPM3_EXIT;//�˳�����
}
