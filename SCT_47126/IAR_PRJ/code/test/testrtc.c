

//低功耗以及RTC测试


#include <msp430.h>
#include "test.h"
#include "gpio.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
#include "power.h"
#include "flash.h"
#include "rtc.h"
#include <stdio.h>
void testrtc(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  PowerInit();
  PWR_ON;
  CORE_PWR_ON;
  COLL_PWR_ON;
  UARTInit(UART_0, UART_Clk_SMCLK, Baud_115200);
  rtc_init();
  delay_ms(1000);
  printf("*************** \r\n");
  printf("*************** \r\n");
  printf("*************** \r\n");
  printf("*************** \r\n");
  printf("*************** \r\n");
  printf("*************** \r\n");
  
  while(1)
  {    
    read_rtc();
    printf("app on \r\n");
    delay_ms(8000);
    
    LowPowerGPIO();
    PowerInit();
    PWR_OFF;
    CORE_PWR_OFF;
    COLL_PWR_OFF;
    ClkOff();   //进入低功耗之前要把时钟设置好
    __bis_SR_register(LPM3_bits + GIE);
    WDTCTL = WDTPW + WDTHOLD;
    delay_ms(50);
    ClkInit();  //推出低功耗后腰将时钟重新设置一下
    PowerInit();//电源控制GPIO重新初始化配置一下
    PWR_ON;
    CORE_PWR_ON;
    COLL_PWR_ON;
    UARTInit(UART_0, UART_Clk_SMCLK, Baud_115200);
    delay_ms(200);//串口初始化之后要等待一会儿，防止串口乱码
  }
}

