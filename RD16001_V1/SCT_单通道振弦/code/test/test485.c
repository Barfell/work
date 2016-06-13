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


extern LoopRAMType Uart1loop;//����0���λ���(���ڴ˴�Ϊʲô����ָ���˼����ָ�벻�����ڴ棬����һ���ṹ�����ʹ���ڴ�)
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
    //if( (Uart1loop.LoopDatLength != 0) && ( (GetTick()- Uart1time) > 5))//������յ�DTU�ظ�������
    if( Uart1loop.LoopDatLength != 0)//������յ�DTU�ظ�������
      {
        LoopRAMReadLength(&Uart1loop, test485str, Uart1loop.LoopDatLength);//��ȡ�ظ�������
        delay_ms(100);
        printf("recived:%s\r\n",test485str);
        memset(test485str,'\0',100);
      }
 }
} 