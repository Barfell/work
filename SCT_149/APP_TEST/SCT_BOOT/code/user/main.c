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
/*_-----------------MCU��������------------------*/
#include "kernel.h"             //��������˰��ӵĸ�������,�Լ�һЩϵͳ��С������������ʱCRCУ���....
#include "msp430f149_uart.h"
#include "msp430f149_gpio.h"
#include "msp430f149_adc.h"
#include "msp430f149_flash.h"
/*_----------------��������---------------------*/
#include "Power.h"
#include "JN5139.h"
#include "LTC2402.h"
#include "Beep.h"
/*_----------------���ܺ���---------------------*/
#include "Voltage.h"
#include "DTprotocol.h"
#include "LoopRamFunc.h"
/*_----------------���Ժ���---------------------*/
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












/**********************************sct����ģ��ĳ�ʼ���Ȳ���************************************/
void SystemInitialization(void)
{
 //�����ñ���
  char RamLoopTestStr[]={"1234567890qwertyuiop[]asdfghjkl;'zxcvbnm,./"};
  char RamLoopTestDisStr[100] = {'\0'};
  char *pFlashTest;
  char FlashString[100] = {'\0'};
  double Temperature = 3.2;
  
  RCC_HSECLKInit();
/*****************************��Դ����*******************************/
  PowerIoInit();        //��Դ����IO���ų�ʼ��
  POWER_MAIN_ON;        //����Դ����(�Ƿ���н�ѹ)
  POWER_MCU_ON;         //MCU��Դ����
  POWER_ZIGBEE_ON;      //ZIGBEE��Դ����
  POWER_ADC_ON;         //LTC2402�Լ����׼Դ��Դ����
  DRIVER_EN_OFF;        //���ҵ�·�ķ��䲿�ֵĿ���
  
/*****************************�������*******************************ok*/
#if (SERIAL_USE_PORT == UART_0)
  UART_Init(UART_0,UART_SouceClk_SMCLK,UART_SMCLKBaud_9600);
#elif (SERIAL_USE_PORT == UART_1)
  UART_Init(UART_1,UART_SouceClk_SMCLK,UART_SMCLKBaud_9600);
#endif
  LoopRAMInit();        //���ڴ���ͨ�ŵĻ��λ����ʼ��
  printf("**************************************\r\n");
  printf("Uart init ok.\r\n");
  
  
/*****************************�ڲ���ѹ*******************************ok*/
  printf("**************************************\r\n");
  VoltageInit();
  printf("MCU Voltage sensor init ok.\r\n");
  printf("MCU Voltage is %f\r\n", GetVoltage() );
  
/*****************************ѭ������*******************************ok*/
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






/*----------------���Ź��жϺ���--------------------*/
// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
 LPM3_EXIT;
}

