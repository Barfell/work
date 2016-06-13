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
#include "s485.h"
#include "ramloop.h"
#include <stdio.h>


extern LoopRAMType Uart1loop;//串口0环形缓冲(关于此处为什么不用指针的思考：指针不分配内存，定义一个结构体则会使用内存)
extern long Uart1time;

void Init485(void)
{
  LoopRAMInit(&Uart1loop);
  UARTInit(UART_1, UART_Clk_SMCLK, Baud_9600);
  _EINT();
  delay_ms(1000); 
}


unsigned char Get485(char *device, char *dat485)
{
    unsigned int retry=0;
    unsigned char ret = 0;
    UartString(UART_1,device);
    //printf("$DTLOG,010015\r\n");
    delay_ms(1000);
    while(1)
    {
      if( (Uart1loop.LoopDatLength != 0) && ( (GetTick()- Uart1time) > 5))//假如接收到DTU回复的数据
        {
          LoopRAMReadLength(&Uart1loop, dat485, Uart1loop.LoopDatLength);//读取回复的数据
          delay_ms(100);
          ret = 1;
          //printf("recived:%s\r\n",test485str);
          break;
        }
      else
        {
          retry++;
          delay_ms(10);
          if(retry == 500)
          {retry = 0;ret = 0;break;}
        }
    }
    return ret;//返回测量的结果状态，成功或者失败
}