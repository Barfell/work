#include <msp430.h>
#include "test.h"
#include "gpio.h"
#include "uart.h"
#include "freq.h"
#include "Vibration.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
#include "power.h"
#include "flash.h"
#include "rtc.h"
#include <stdio.h>

int main(void)
{

//  testrtc();  
//  testtimer();
//  testusart();
//  testsd();
//  testflash();
  testfreq();
  
  
  
  
//    WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
//  ClkInit();
//  PowerInit();
//  PWR_ON;
//  CORE_PWR_ON;
//  COLL_PWR_ON;
//  
//  UARTInit(UART_0, UART_Clk_SMCLK, Baud_115200);
//  FreqInit();
//  SetConnectToTran();
//  delay_ms(2000);
//  printf("init ok\r\n");
//  while(1)
//  {
//    SetConnectToRec();
//    delay_ms(2000);
//    SetConnectToTran();
//    delay_ms(2000);
//  }

}


