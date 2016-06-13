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
#include "dtu.h"
#include "key.h"
#include "ramloop.h"
#include <stdio.h>


extern LoopRAMType Uart0loop;//����0���λ���(���ڴ˴�Ϊʲô����ָ���˼����ָ�벻�����ڴ棬����һ���ṹ�����ʹ���ڴ�)
extern long Uart0time;




void RFInit(void)
{
  
  //�ر�DTU
  P4REN  &= ~BIT5;
  P4DIR  |=  BIT5;  
  P4OUT  &= ~BIT5;
  P4OUT  |=  BIT5;
  
  
  
  LoopRAMInit(&Uart0loop);//�������λ���
  UARTInit(UART_0, UART_Clk_SMCLK, Baud_9600);//
  
  P4DIR |= BIT1;
  P4OUT |= BIT1;//RF---->EN
    
  _EINT();
  UART0_CH_RF;//ѡ��N2
  delay_ms(1000);
  
}







