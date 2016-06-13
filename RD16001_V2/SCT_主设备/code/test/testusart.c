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
  COLL_PWR_ON;
  TRAN_PWR_ON;
  
  P5DIR |= BIT5;
  P5OUT |= BIT5;//LED
  
  UARTInit(UART_0, UART_Clk_SMCLK, Baud_115200);
 
 while(1)
 {
   P5OUT |= BIT5;
   delay_ms(2000);
   P5OUT &= ~BIT5;
   delay_ms(200);
   UART_SendByte(UART_0,'X');
   printf("123456789\r\n");
 }
} 