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


extern LoopRAMType Uart0loop;//串口0环形缓冲(关于此处为什么不用指针的思考：指针不分配内存，定义一个结构体则会使用内存)
extern long Uart0time;

char teststr[100];




/*
//////////////////////////////////////////////////
hac-lbee-v3.2   ap=0(透传不带校验值)  20dBm 38400bps   (9.1v)
不连接模块：  14.5ma
连接不发射：  31.1ma
连接发射：   最大38.1ma
/////////////////////////////////////////////////
hac_uh480p 9600bps  (9.1v)
不连接模块：  14.5ma
连接不发射：  27.8ma
连接发射：   最大35.5ma
/////////////////////////////////////////////////
YL_800T 9600bps  (9.1v)
不连接模块：  14.5ma
连接不发射：  22.1ma
连接发射：   最大74.5ma
/////////////////////////////////////////////////
YL_10T 9600bps  (9.1v)
不连接模块：  14.5ma
连接不发射：  17.1ma
连接发射：   最大24.5ma

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
//        LoopRAMReadLength(&Uart0loop, teststr, Uart0loop.LoopDatLength);//读取回复的数据
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