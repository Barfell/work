#include "msp430.h"
#include "timer.h"

//tb0 发送固定频率脉冲
void TB0_Freq(int f)
{
  P3REN  &= ~BIT5;
  P3DIR  |= BIT5;                     
  P3SEL  |= BIT5; 
  
  TBCCTL0 = OUTMOD_4;                       // toggle
  TBCCR0  = 4000000/f-1;
  TBCTL   = TBSSEL_2 + MC_1;                // SMCLK, Up to CCR0 mode
}

//ta使用taclk作为定时器时钟
void TimerA_TACLK(void)
{
  //p15-taclk
  P1REN &= ~BIT5;
  P1DIR &= ~BIT5; 
  P1SEL |=  BIT5;// Set P1.5to TACLK
  
  //设置不分频，持续模式，时钟为外部时钟源 TACLK
  TACTL = TASSEL_0 + MC_2 + ID_0 + TACLR;// taclk + Continuous Mode + Div0
  //从第100个脉冲开始计时
  TACCR1 = 100;//开始计时
  //50个脉冲后计时结束，可以计算频率了
  TACCR2 = 150;//50个脉冲后
  /*允许中断*/
  TACCTL2 = CCIE;//开始计时中断
  TACCTL1 = CCIE;//结束计时中断
  _EINT();//开总中断
}