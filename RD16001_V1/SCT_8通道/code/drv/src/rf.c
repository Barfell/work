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
#include "rf.h"
#include "ramloop.h"
#include <stdio.h>


extern LoopRAMType Uart1loop;//����0���λ���(���ڴ˴�Ϊʲô����ָ���˼����ָ�벻�����ڴ棬����һ���ṹ�����ʹ���ڴ�)
extern long Uart1time;




void RFInit(void)
{
  LoopRAMInit(&Uart1loop);
  UARTInit(UART_1, UART_Clk_SMCLK, Baud_57600);
  _EINT();
  delay_ms(1000);
}


void RFString(char *s)
{
   while(*s != '\0')
    {
      while((UC1IFG & UCA1TXIFG)==0);
      UCA1TXBUF = *s;
      while((UC1IFG & UCA1TXIFG)==0);
      s++;
    }
}




