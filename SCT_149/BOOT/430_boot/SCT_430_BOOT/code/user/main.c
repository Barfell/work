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
  PowerIoInit();        //电源控制IO引脚初始化
  POWER_MAIN_ON;        //主电源开关(是否进行降压)
  POWER_MCU_ON;         //MCU电源开关
  POWER_ZIGBEE_ON;      //ZIGBEE电源开关
  POWER_ADC_ON;         //LTC2402以及其基准源电源开关
  DRIVER_EN_OFF;        //振弦电路的发射部分的开关
/*****************************串口输出******************************/
  UART_Init(UART_0,UART_SouceClk_SMCLK,UART_SMCLKBaud_9600);
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

