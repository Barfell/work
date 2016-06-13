/*_-----------------MCU��������------------------*/
#include "kernel.h"             //��������˰��ӵĸ�������,�Լ�һЩϵͳ��С������������ʱCRCУ���....
#include "msp430f149_uart.h"
#include "msp430f149_gpio.h"
#include "msp430f149_timer.h"
#include "msp430f149_adc.h"
#include "msp430f149_spi.h"
#include "msp430f149_flash.h"
/*_----------------���ܺ���---------------------*/
#include "Power.h"
#include "Freq.h"
#include "Voltage.h"
#include "Temperature.h"
#include "DTprotocol.h"
#include "LoopRamFunc.h"
/*_----------------���Ժ���---------------------*/
#include "test.h"
void testflash(void)
{
 /*************************�����ñ���*********************************/
  char RamLoopTestStr[]={"1234567890qwertyuiop[]asdfghjkl;'zxcvbnm,./"};
  char RamLoopTestDisStr[100] = {'\0'};
  char *pFlashTest;
  char FlashString[100] = {'\0'};
  
  RCC_HSECLKInit();
/*****************************��Դ����*******************************/
  PowerIoInit();        //��Դ����IO���ų�ʼ��
  POWER_MAIN_ON;        //����Դ����(�Ƿ���н�ѹ)
  POWER_MCU_ON;         //MCU��Դ����
  POWER_ZIGBEE_ON;      //ZIGBEE��Դ����
  POWER_ADC_ON;         //LTC2402�Լ����׼Դ��Դ����
  DRIVER_EN_OFF;        //���ҵ�·�ķ��䲿�ֵĿ���
  
/*****************************�������******************************/
  
#ifdef SERIAL_USE_PORT0
  UART_Init(UART_0,UART_SouceClk_SMCLK,UART_SMCLKBaud_9600);
#endif
  
#ifdef SERIAL_USE_PORT1
  UART_Init(UART_1,UART_SouceClk_SMCLK,UART_SMCLKBaud_9600);
#endif
  
  
  printf("**************************************\r\n");
  printf("flash test init ok.\r\n");
  

/*****************************flash*******************************ok*/
  printf("**************************************\r\n");
  pFlashTest = (char *)0x4000;
  strncat(FlashString, pFlashTest, sizeof("hello,world,1234567891011abcdefghijklmnopqrstuvwxyz"));
  printf("flash addr 0x4000 is:%s\r\n",FlashString);
  
  FlashInit();
  printf("Flash Init ok\r\n");
  printf("EreaseSector addr 0x4000 \r\n");
  FlashEreaseSector(0x4000);
  printf("WriteAddr @ 0x4000 HELLO WORLD\r\n");
  FlashWriteAddr(0x4000, "hello,world,1234567891011abcdefghijklmnopqrstuvwxyz", sizeof("hello,world,1234567891011abcdefghijklmnopqrstuvwxyz"));
  
  memset(FlashString, '\0', 100);
  strncat(FlashString, (char *)0x4000, sizeof("hello,world,1234567891011abcdefghijklmnopqrstuvwxyz") );
  printf("Flash addr 0x4000 is:%s\r\n",FlashString);
  
}



