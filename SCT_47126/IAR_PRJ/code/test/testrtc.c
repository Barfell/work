

//�͹����Լ�RTC����


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
    ClkOff();   //����͹���֮ǰҪ��ʱ�����ú�
    __bis_SR_register(LPM3_bits + GIE);
    WDTCTL = WDTPW + WDTHOLD;
    delay_ms(50);
    ClkInit();  //�Ƴ��͹��ĺ�����ʱ����������һ��
    PowerInit();//��Դ����GPIO���³�ʼ������һ��
    PWR_ON;
    CORE_PWR_ON;
    COLL_PWR_ON;
    UARTInit(UART_0, UART_Clk_SMCLK, Baud_115200);
    delay_ms(200);//���ڳ�ʼ��֮��Ҫ�ȴ�һ�������ֹ��������
  }
}

