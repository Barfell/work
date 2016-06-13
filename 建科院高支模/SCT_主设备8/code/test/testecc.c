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
#include "ecc.h"
#include "key.h"
#include "ramloop.h"
#include <stdio.h>



void testecc(void)
{
  
  char data[200] = {"abcdefghijklmnopqrstuvwxyz\r\n"};
  char pdata[250] = {'\0'};
  
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  PowerInit();
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_ON;
  UARTInit(UART_0, UART_Clk_SMCLK, Baud_9600);
  _EINT();
  
  delay_ms(2000);
  printf("ecc test.......\r\n");
  
  
  
  
 while(1)
 {
  // printf("data:%s\r\n", data);
   //printf("datalength:%d\r\n", getDataLength(data,200));
   packData(data, getDataLength(data,200), pdata);
   UartStringLength(UART_0, pdata, getDataLength(pdata,250));
   delay_ms(8000);
 }
 
 
} 