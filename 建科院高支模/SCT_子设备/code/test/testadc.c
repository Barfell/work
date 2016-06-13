#include <msp430.h>
#include "gpio.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
#include "rf.h"
#include "freq.h"
#include "power.h"
#include "sd.h"
#include <stdio.h>

float res = 0.0;
float voltage = 0.0;
void testsd(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  ClkInit();
  PowerInit();
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_ON;
  FreqInit();
  
  _EINT();
  RFInit();
  LED(1);
  delay_ms(1000);
  printf("init ok.....\r\n");
  delay_ms(1000);
  LED(0);
 
  SDInit();
  delay_ms(1000);
  printf("adc test...\r\n");
  while(1)
  {
    voltage = GetSD16Voltage(1);
    printf("ch1-v:%f v\r\n",voltage);
    voltage = GetSD16Voltage(2);
    printf("ch2-v:%f v\r\n",voltage);
    voltage = GetSD16Voltage(3);
    printf("ch3-v:%f v\r\n",voltage);
    voltage = GetSD16Voltage(4);
    printf("ch4-v:%f v\r\n",voltage);
    voltage = GetSD16Voltage(5);
    printf("ch5-v:%f v\r\n",voltage);
    printf("-----------------------------------\r\n");
    
//    res = (5-voltage)/(5-11*voltage) - 1;  //R = (5-V)/(5-11V) - 1
//    printf("ch5-res:%f om\r\n",res);
    delay_ms(5000);
  }
  
} 