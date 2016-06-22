#include <msp430.h>
#include "gpio.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "flash.h"
#include "timer.h"
#include "power.h"
#include <stdio.h>

void testflash(void)
{
  char *pFlashTest;
  char FlashString[100] = {'\0'};
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  ClkInit();
  PowerInit();
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_ON;

  GPIOInit(P1,Pin1,Out);
  GPIOOutPut(P1,Pin1,1);
  UARTInit(UART_0, UART_Clk_SMCLK, Baud_115200);
  
  printf("**************************************\r\n");
  pFlashTest = (char *)0x4000;
  strncat(FlashString, pFlashTest, sizeof("hello,world,1234567891011abcdefghijklmnopqrstuvwxyz"));
  printf("flash addr 0x4000 is:%s\r\n",FlashString);
  FlashInit();
  printf("Flash Init ok\r\n");
  printf("EreaseSector addr 0x4000 \r\n");
  FlashEreaseSector(0x4000);
  printf("WriteAddr @ 0x4000 'HELLO WORLD'\r\n");
  FlashWriteAddr(0x4000, "hello,world,1234567891011abcdefghijklmnopqrstuvwxyz", sizeof("hello,world,1234567891011abcdefghijklmnopqrstuvwxyz"));
  memset(FlashString, '\0', 100);
  strncat(FlashString, (char *)0x4000, sizeof("hello,world,1234567891011abcdefghijklmnopqrstuvwxyz") );
  printf("Flash addr 0x4000 is:%s\r\n",FlashString);
}