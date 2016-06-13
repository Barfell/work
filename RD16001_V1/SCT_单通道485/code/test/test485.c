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
  PowerInit();
  PWR_ON;
  CORE_PWR_ON;
  COLL_PWR_ON;
  LoopRAMInit(&Uart1loop);
  UARTInit(UART_1, UART_Clk_SMCLK, Baud_9600);
  UARTInit(UART_0, UART_Clk_SMCLK, Baud_115200);
  _EINT();
  
  delay_ms(2000);
  printf("123456789\r\n");
  printf("485 test\r\n");
 while(1)
 {
    UartString(UART_1,"$DTLOG,010015\r\n\r\n");
    printf("$DTLOG,010015\r\n");
    delay_ms(5000);
    delay_ms(5000);
    //if( (Uart1loop.LoopDatLength != 0) && ( (GetTick()- Uart1time) > 5))//假如接收到DTU回复的数据
    if( Uart1loop.LoopDatLength != 0)//假如接收到DTU回复的数据
      {
        LoopRAMReadLength(&Uart1loop, test485str, Uart1loop.LoopDatLength);//读取回复的数据
        delay_ms(100);
        printf("recived:%s\r\n",test485str);
        memset(test485str,'\0',100);
      }
 }
} 