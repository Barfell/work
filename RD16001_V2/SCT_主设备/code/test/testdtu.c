#include <msp430.h>
#include "test.h"
#include "cfg.h"
#include "gpio.h"
#include "freq.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
#include "power.h"
#include "flash.h"
#include "rtc.h"
#include "s485.h"
#include "level.h"
#include "rain.h"
#include "cmd.h"
#include "ramloop.h"
#include "key.h"
#include "ecc.h"
#include "dtu.h"
#include "rf.h"
#include <stdio.h>
#include <string.h>
#include "includes.h"


extern LoopRAMType Uart0loop;//����0���λ���(���ڴ˴�Ϊʲô����ָ���˼����ָ�벻�����ڴ棬����һ���ṹ�����ʹ���ڴ�)
extern long Uart0time;

void testdtu(void)
{
  char UpLoadData[300] = {'\0'};//��Ҫ�ϴ�������
  char PROTOCOL_UpLoadData[400] = {'\0'};//������Э��Ľ�Ҫ�ϴ�����
  unsigned char detectTime = 0;//dtu����ʱ��

  
  

  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();//ϵͳʱ��Ƭ
  PowerInit();
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_ON;
  LED(1); 
  while(1)
  {
/*------------------�ȴ����ӵ�DTU---------------------------*/
      LED(1);
      DtuInit();
      LED(0);
      delay_ms(5000);
      while(1)
      {
        if(DtuStatu() == 1)//���Ϸ�����
          {
             LED(1);delay_ms(5000);break;
          }
        if(DtuStatu() == 0)//û�����Ϸ�����
          {
            LED(0);
            delay_ms(1000);
            detectTime++;
            if(detectTime == 180)
            {
              detectTime = 0; 
              break;
            }
            delay_ms(1000);
          }
      }
      
      LED(1);
      delay_ms(5000);
      LED(0);
      
/*---------------------------�ϴ�����----------------------*/
      if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 1)//��Э�鴫��
        {
          packData(UpLoadData, getDataLength(UpLoadData,300), PROTOCOL_UpLoadData);
          UartStringLength(UART_0, PROTOCOL_UpLoadData, getDataLength(PROTOCOL_UpLoadData,400));
          memset(UpLoadData ,'\0',300);
          memset(PROTOCOL_UpLoadData ,'\0',400);
        }
      if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 0)//����Э�鴫��
        {
         // printf("%s\r\n",UpLoadData);
          UartStringLength(UART_0, UpLoadData, getDataLength(UpLoadData,300));
          memset( UpLoadData , '\0', 300 );
        }
      delay_ms(500);      
  }
}

