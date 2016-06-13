#include <msp430.h>
#include "test.h"
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
#include "ramloop.h"
#include "key.h"
#include "dtu.h"
#include <stdio.h>

void PowerInit(void)
{
  P9REN &= ~BIT5;
  P9DIR |=  BIT5;                             
  P9OUT &= ~BIT5;                            
  
  P4REN &= ~BIT2;
  P4REN &= ~BIT3;
  P4DIR |= BIT3+BIT2;                             
  P4OUT &= ~BIT2;                                
  P4OUT &= ~BIT3;
}


extern LoopRAMType Uart0loop;//����0���λ���(���ڴ˴�Ϊʲô����ָ���˼����ָ�벻�����ڴ棬����һ���ṹ�����ʹ���ڴ�)
extern long Uart0time;

void LowPowerEntry(void)
{
    LowPowerGPIO();
    PowerInit();
    PWR_OFF;
    CORE_PWR_OFF;
    COLL_PWR_OFF;
    ClkOff();   //����͹���֮ǰҪ��ʱ�����ú�
    __bis_SR_register(LPM3_bits + GIE);
    WDTCTL = WDTPW + WDTHOLD;
    //clk
    ClkInit();  //�Ƴ��͹��ĺ�����ʱ����������һ��
    SysTickInit();
    //moudles
    delay_ms(1000);
    PowerInit();//��Դ����GPIO���³�ʼ������һ��
    //power
    PWR_ON;
    CORE_PWR_ON;
    COLL_PWR_ON;
    
    delay_ms(1000);
}