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


extern LoopRAMType Uart1loop;//串口0环形缓冲(关于此处为什么不用指针的思考：指针不分配内存，定义一个结构体则会使用内存)
extern long Uart1time;
char test485str[100];
void test485(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();
  PowerInit();
  
  
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_ON;
//  LoopRAMInit(&Uart1loop);
//  UARTInit(UART_1, UART_Clk_SMCLK, Baud_9600);
  
  
  Init485();
  
  _EINT();
  RFInit();
  
  delay_ms(2000);
  printf("123456789\r\n");
  printf("485 test\r\n");
// while(1)
// {
//    UartString(UART_1,"$DTLOG,010015\r\n");
//    printf("$DTLOG,010015\r\n");
//    delay_ms(8000);
//    if( Uart1loop.LoopDatLength != 0)
//      {
//        LoopRAMReadLength(&Uart1loop, test485str, Uart1loop.LoopDatLength);//读取回复的数据
//        delay_ms(100);
//        printf("recived:%s\r\n",test485str);
//        memset(test485str,'\0',100);
//      }
// }
  
  
  while(1)
  {
    while( Get485("$DTLOG,010015\r\n",test485str) == 0);
    printf("485:%s\r\n",test485str);
    memset(test485str,0,100);
    delay_ms(2000);
  }
} 