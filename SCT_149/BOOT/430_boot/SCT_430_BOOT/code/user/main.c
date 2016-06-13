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
 
/*****************************��Դ����*******************************/
  PowerIoInit();        //��Դ����IO���ų�ʼ��
  POWER_MAIN_ON;        //����Դ����(�Ƿ���н�ѹ)
  POWER_MCU_ON;         //MCU��Դ����
  POWER_ZIGBEE_ON;      //ZIGBEE��Դ����
  POWER_ADC_ON;         //LTC2402�Լ����׼Դ��Դ����
  DRIVER_EN_OFF;        //���ҵ�·�ķ��䲿�ֵĿ���
/*****************************�������******************************/
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









///*----------------���Ź��жϺ���--------------------*/
// //Watchdog Timer interrupt service routine
//#pragma vector=WDT_VECTOR
//__interrupt void watchdog_timer(void)
//{
// LPM3_EXIT;
//}

