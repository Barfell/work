#include <msp430.h>
#include "test.h"
#include "gpio.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
#include "power.h"
#include "flash.h"
#include "dtu.h"
#include "rtc.h"
#include "key.h"
#include "s485.h"
#include "ramloop.h"
#include <stdio.h>


extern LoopRAMType Uart1loop;//����0���λ���(���ڴ˴�Ϊʲô����ָ���˼����ָ�벻�����ڴ棬����һ���ṹ�����ʹ���ڴ�)
extern long Uart1time;

void Init485(void)
{
  
  /*---------------����ѡ��--------*/
  P5REN &=  ~BIT2;
  P5DIR |=   BIT2;
  P5OUT |=   BIT2;//VW_485 SW-0-485
  /*--------------����-------------*/
  LoopRAMInit(&Uart1loop);
  UARTInit(UART_1, UART_Clk_SMCLK, Baud_9600);
  _EINT();
  delay_ms(1000); 
}


unsigned char Get485(char *device, char *dat485)
{
    unsigned int retry=0;
    unsigned char ret = 0;
    char datTemp[200] = {'\0'};
    UartString(UART_1,device);
    //printf("UART_1:%s\r\n",device);
    delay_ms(5000);
    while(1)
    {
      if( (Uart1loop.LoopDatLength != 0) && ( (GetTick()- Uart1time) > 5))//������յ�DTU�ظ�������
        {
          LoopRAMReadLength(&Uart1loop, datTemp, Uart1loop.LoopDatLength);//��ȡ�ظ�������
          memcpy(dat485,datTemp,strlen(datTemp) -2);
          memset(datTemp,0,200);
          delay_ms(100);
          ret = 1;
          break;
        }
      else
        {
          retry++;
          delay_ms(10);
          if(retry == 500)
          {retry = 0;ret = 0;break;}
        }
    }
    return ret;//���ز����Ľ��״̬���ɹ�����ʧ��
}