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
  LoopRAMInit(&Uart1loop);
  UARTInit(UART_1, UART_Clk_SMCLK, Baud_9600);
  _EINT();
  delay_ms(1000); 
}


unsigned char Get485(char *device, char *dat485)
{
    unsigned int retry=0;
    unsigned char ret = 0;
    UartString(UART_1,device);
    //printf("$DTLOG,010015\r\n");
    delay_ms(1000);
    while(1)
    {
      if( (Uart1loop.LoopDatLength != 0) && ( (GetTick()- Uart1time) > 5))//������յ�DTU�ظ�������
        {
          LoopRAMReadLength(&Uart1loop, dat485, Uart1loop.LoopDatLength);//��ȡ�ظ�������
          delay_ms(100);
          ret = 1;
          //printf("recived:%s\r\n",test485str);
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