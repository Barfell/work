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


extern LoopRAMType Uart0loop;//串口0环形缓冲(关于此处为什么不用指针的思考：指针不分配内存，定义一个结构体则会使用内存)
extern long Uart0time;




void RFInit(void)
{
  LoopRAMInit(&Uart0loop);//创建环形缓冲
  UARTInit(UART_0, UART_Clk_SMCLK, Baud_57600);//设置dtu串口
  _EINT();
  delay_ms(1000);
}







