#include <msp430.h>
#include "gpio.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
#include "power.h"
#include <stdio.h>

void testusart(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  ClkInit();
  PowerInit();
  PWR_ON;
  CORE_PWR_ON;
  COLL_PWR_ON;

  GPIOInit(P1,Pin1,Out);
  GPIOOutPut(P1,Pin1,1);
  UARTInit(UART_0, UART_Clk_SMCLK, Baud_115200);
 
 while(1)
 {
   GPIOOutPut(P1,Pin1,0);
   delay_ms(2000);
   GPIOOutPut(P1,Pin1,1);
   delay_ms(100);
   UART_SendByte(UART_0,'X');
   printf("123456789\r\n");
 }
} 