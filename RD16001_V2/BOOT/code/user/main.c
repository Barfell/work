#include "kernel.h"             
#include "msp430f149_uart.h"
#include "msp430f149_gpio.h"
#include "msp430f149_flash.h"
#include "Power.h"
#include "DTprotocol.h"
#include "LoopRamFunc.h"
#include "Boot.h"
#include "msp430f149_wdt.h"

void SysInit(void)
{
 
/*****************************电源控制*******************************/
COLL_PWR_ON;
PWR_ON;
TRAN_PWR_ON;
/*****************************串口输出******************************/
  FlashInit();
}


void main(void)
{
  RCC_HSECLKInit();
  WatchDogOn();
  SysInit();
  BootProc();
}









///*----------------看门狗中断函数--------------------*/
// //Watchdog Timer interrupt service routine
//#pragma vector=WDT_VECTOR
//__interrupt void watchdog_timer(void)
//{
// LPM3_EXIT;
//}

