#include <msp430.h>
#include "test.h"
#include "gpio.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
#include "power.h"
#include "flash.h"
#include "dtu.h"
#include "rtc.h"
#include "rf.h"
#include "s485.h"
#include "key.h"
#include "ramloop.h"
#include <stdio.h>


extern LoopRAMType Uart0loop;//����0���λ���(���ڴ˴�Ϊʲô����ָ���˼����ָ�벻�����ڴ棬����һ���ṹ�����ʹ���ڴ�)
extern long Uart0time;

char teststr[100];




/*
//////////////////////////////////////////////////
hac-lbee-v3.2   ap=0(͸������У��ֵ)  20dBm 38400bps   (9.1v)
������ģ�飺  14.5ma
���Ӳ����䣺  31.1ma
���ӷ��䣺   ���38.1ma
/////////////////////////////////////////////////
hac_uh480p 9600bps  (9.1v)
������ģ�飺  14.5ma
���Ӳ����䣺  27.8ma
���ӷ��䣺   ���35.5ma
/////////////////////////////////////////////////
YL_800T 9600bps  (9.1v)
������ģ�飺  14.5ma
���Ӳ����䣺  22.1ma
���ӷ��䣺   ���74.5ma
/////////////////////////////////////////////////
YL_10T 9600bps  (9.1v)
������ģ�飺  14.5ma
���Ӳ����䣺  17.1ma
���ӷ��䣺   ���24.5ma

*/
void testrf(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();
  PowerInit();
  
  
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_ON;
  
  _EINT();
  RFInit();
  
  P4DIR |= BIT1;
  P4OUT |= BIT1;
  
  delay_ms(5000);
  LED(1);
  printf("rf test\r\n");
  delay_ms(1000);
  LED(0);
  printf("rf test\r\n");
  delay_ms(1000);
  LED(1);
  printf("rf test\r\n");
  delay_ms(1000);
  LED(0);
  delay_ms(1000);
  //LED(1);
  
 while(1)
 {
//    if( Uart0loop.LoopDatLength != 0 && ( (GetTick()- Uart0time) > 8)  )
//      {
//        LoopRAMReadLength(&Uart0loop, teststr, Uart0loop.LoopDatLength);//��ȡ�ظ�������
//        printf("%s\r\n",teststr);
//        memset(teststr,'\0',100);
//      }
//    delay_ms(100);
   
  delay_ms(3000);
  LED(1);
  printf("rf test\r\n");
  printf("rf test\r\n");
  printf("rf test\r\n");
  printf("rf test\r\n");
  printf("rf test\r\n");
  printf("rf test\r\n");
  printf("rf test\r\n");
  delay_ms(100);
  
  
  LED(0);
 }
  
 
} 