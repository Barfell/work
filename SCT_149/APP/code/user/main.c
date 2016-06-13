/*_-----------------MCU外设驱动------------------*/
#include "kernel.h"             //里面包含了板子的各种配置,以及一些系统的小函数，比如延时CRC校验等....
#include "msp430f149_uart.h"
#include "msp430f149_gpio.h"
#include "msp430f149_timer.h"
#include "msp430f149_adc.h"
#include "msp430f149_spi.h"
#include "msp430f149_flash.h"
#include "msp430f149_wdt.h"
/*_----------------器件驱动---------------------*/
#include "Vibration.h"
#include "Power.h"
#include "JN5139.h"
#include "LTC2402.h"
#include "Beep.h"
/*_----------------功能函数---------------------*/
#include "Freq.h"
#include "Voltage.h"
#include "Temperature.h"
#include "DTprotocol.h"
#include "LoopRamFunc.h"
/*_----------------测试函数---------------------*/
#include "test.h"


void HardWareInit(void);
void MoudleTest(void);


void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  
  RCC_HSECLKInit();
  
//  WatchDogOff();
//  
//  HardWareInit();
//  LoopRAMInit();
//  FlashInit();
//  printf("***********************************\r\n");
//  printf("***************enter app***********\r\n");
//  printf("*****************DT****************\r\n");
//  while(1)
//  {
//   DTcmdTask();
//  }
  testfreq();
}


void HardWareInit(void)
{
  /*****************************电源控制*******************************/
  PowerIoInit();        //电源控制IO引脚初始化
  POWER_MAIN_ON;        //主电源开关(是否进行降压)
  POWER_MCU_ON;         //MCU电源开关
  POWER_ZIGBEE_ON;      //ZIGBEE电源开关
  POWER_ADC_ON;         //LTC2402以及其基准源电源开关
  DRIVER_EN_OFF;        //振弦电路的发射部分的开关
  /*****************************串口输出******************************/
  #ifdef SERIAL_USE_PORT0
  UART_Init(UART_0,UART_SouceClk_SMCLK,UART_SMCLKBaud_9600);
  #endif
  #ifdef SERIAL_USE_PORT1
  UART_Init(UART_1,UART_SouceClk_SMCLK,UART_SMCLKBaud_9600);
  #endif

}


void MoudleTest(void)
{
 /*************************测试用变量*********************************/
  char RamLoopTestStr[]={"1234567890qwertyuiop[]asdfghjkl;'zxcvbnm,./"};
  char RamLoopTestDisStr[100] = {'\0'};
  char *pFlashTest;
  char FlashString[100] = {'\0'};
  double Temperature = 0.0;
  
/*****************************振弦传感器*****************************/
  printf("**************************************\r\n");
  FreqInit();
  printf("Vibration sensor init ok.\r\n");
  printf("Freq is %f\r\n", GetFreq() );
  
  
  
/*****************************温度传感器*****************************/
  delay_ms(5000);
  printf("**************************************\r\n");
  printf("\r\n");
 // 由于spi和uart不能共用，所以必须单独使用
  TemperatureInit();
  Temperature = LTC2402_GetResistance();
  SpiToUart();
#ifdef SERIAL_USE_PORT0
  UART_Init(UART_0,UART_SouceClk_SMCLK,UART_SMCLKBaud_9600);
#endif
  
#ifdef SERIAL_USE_PORT1
  UART_Init(UART_1,UART_SouceClk_SMCLK,UART_SMCLKBaud_9600);
#endif
  printf("Temperature sensor init ok.\r\n");
  printf("Temperature is %f\r\n", Temperature );
  
  
  
  
  
/*****************************内部电压*******************************ok*/
  printf("**************************************\r\n");
  VoltageInit();
  printf("MCU Voltage sensor init ok.\r\n");
  printf("MCU Voltage is %f\r\n", GetVoltage() );
  
  
  
  
/*****************************循环缓冲*******************************ok*/
  printf("**************************************\r\n");
  LoopRAMInit();
  printf("LoopRAM Init ok\r\n");
  LoopRAMWriteLength(RamLoopTestStr, sizeof(RamLoopTestStr));
  LoopRAMReadLength(RamLoopTestDisStr, sizeof(RamLoopTestStr));
  printf("Ramloop test data is:<<< %s >>>\r\n",RamLoopTestDisStr);
  
  
  
/*****************************flash*******************************ok*/
//  printf("**************************************\r\n");
//  pFlashTest = (char *)0x4000;
//  strncat(FlashString, pFlashTest, sizeof("hello,world,1234567891011abcdefghijklmnopqrstuvwxyz"));
//  printf("flash addr 0x4000 is:%s\r\n",FlashString);
//  
//  FlashInit();
//  printf("Flash Init ok\r\n");
//  printf("EreaseSector addr 0x4000 \r\n");
//  FlashEreaseSector(0x4000);
//  printf("WriteAddr @ 0x4000 HELLO WORLD\r\n");
//  FlashWriteAddr(0x4000, "hello,world,1234567891011abcdefghijklmnopqrstuvwxyz", sizeof("hello,world,1234567891011abcdefghijklmnopqrstuvwxyz"));
//  
//  memset(FlashString, '\0', 100);
//  strncat(FlashString, (char *)0x4000, sizeof("hello,world,1234567891011abcdefghijklmnopqrstuvwxyz") );
//  printf("Flash addr 0x4000 is:%s\r\n",FlashString);
  
  
  /**************************zigbee***************************************/
  //  if(ZigbeeInit() == 1)
//  {printf("Zigbee Init ok....\r\n");}
  
}













///*----------------看门狗中断函数--------------------*/
// //Watchdog Timer interrupt service routine
//#pragma vector=WDT_VECTOR
//__interrupt void watchdog_timer(void)
//{
// LPM3_EXIT;
//}

