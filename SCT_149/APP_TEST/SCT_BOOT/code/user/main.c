/*


  ----------------10KByte------------- *  ------------------50KByte-----
 *************************************************************************
*                                      *                                  *
*            BOOT                      *             PROGRAM              *
*                                      *                                  *
 *************************************************************************
  -------------------------------------60KByte--------------------------
0x1000-----------------------------------------------------------------0xffff

*/
/*_-----------------MCU外设驱动------------------*/
#include "kernel.h"             //里面包含了板子的各种配置,以及一些系统的小函数，比如延时CRC校验等....
#include "msp430f149_uart.h"
#include "msp430f149_gpio.h"
#include "msp430f149_adc.h"
#include "msp430f149_flash.h"
/*_----------------器件驱动---------------------*/
#include "Power.h"
#include "JN5139.h"
#include "LTC2402.h"
#include "Beep.h"
/*_----------------功能函数---------------------*/
#include "Voltage.h"
#include "DTprotocol.h"
#include "LoopRamFunc.h"
/*_----------------测试函数---------------------*/
#include "test.h"


void SystemInitialization(void);


void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  SystemInitialization();
  while(1)
  {
      DTcmdTask();
  }
}












/**********************************sct各个模块的初始化等操作************************************/
void SystemInitialization(void)
{
 //测试用变量
  char RamLoopTestStr[]={"1234567890qwertyuiop[]asdfghjkl;'zxcvbnm,./"};
  char RamLoopTestDisStr[100] = {'\0'};
  char *pFlashTest;
  char FlashString[100] = {'\0'};
  double Temperature = 3.2;
  
  RCC_HSECLKInit();
/*****************************电源控制*******************************/
  PowerIoInit();        //电源控制IO引脚初始化
  POWER_MAIN_ON;        //主电源开关(是否进行降压)
  POWER_MCU_ON;         //MCU电源开关
  POWER_ZIGBEE_ON;      //ZIGBEE电源开关
  POWER_ADC_ON;         //LTC2402以及其基准源电源开关
  DRIVER_EN_OFF;        //振弦电路的发射部分的开关
  
/*****************************串口输出*******************************ok*/
#if (SERIAL_USE_PORT == UART_0)
  UART_Init(UART_0,UART_SouceClk_SMCLK,UART_SMCLKBaud_9600);
#elif (SERIAL_USE_PORT == UART_1)
  UART_Init(UART_1,UART_SouceClk_SMCLK,UART_SMCLKBaud_9600);
#endif
  LoopRAMInit();        //用于串口通信的环形缓冲初始化
  printf("**************************************\r\n");
  printf("Uart init ok.\r\n");
  
  
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
//  pFlashTest = (char *)0xf700;
//  strncat(FlashString, pFlashTest, sizeof("hello,world"));
//  printf("flash addr 0xfe00 is:%s\r\n",FlashString);
//  
//  FlashInit();
//  printf("Flash Init ok\r\n");
//  printf("EreaseSector addr 0xf700 \r\n");
//  FlashEreaseSector(0xf700);
//  printf("WriteAddr @ 0xf700 HELLO WORLD\r\n");
//  FlashWriteAddr(0xf700, "hello,world", 11);
//  
//  memset(FlashString, '\0', 100);
//  strncat(FlashString, (char *)0xf700, sizeof("hello,world") );
//  printf("Flash addr 0xfe00 is:%s\r\n",pFlashTest);
  
}






/*----------------看门狗中断函数--------------------*/
// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
 LPM3_EXIT;
}

