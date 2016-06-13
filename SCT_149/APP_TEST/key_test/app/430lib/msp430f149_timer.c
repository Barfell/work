/**
 * @file  msp430f149_timer.c
 * @author  wf
 * @version V1.0
 * @date  2015-11-20
 * @brief 
 */

/**
 * @versionnote
 * version    V1.0
 * +  2015-11-20
 * +  file create
 */
#include "msp430f149_timer.h"

u8 Count =0;
u8 Second = 0;

/**
 * @brief 设置定时器 A 为定时功能,默认使用 TA0 中断
 * @param TimerSource 定时器时钟来源
 * @param TimerDivde  定时器分频选择
 * @param u16Count    定时器计数值
 */
void TimerA_SetTimerMode(TimerSource_TypeDef TimerSource, TimerDivde_TypeDef TimerDivde,u16 u16Count)
{
    /*MC0 选择增计数模式*/
    TACTL |= TACLR + MC0 + TimerSource + TimerDivde;
    /*允许 TACCR0 中断*/
    TACCTL0 = CCIE;
    TACCR0 = u16Count;
}

/*  TA0   TA1   TA2
    P1.1  P1.2  P1.3
    P1.5  P1.6  P1.7
TA0 输出不能调整占空比,故只可选择TA1,TA2作为PWM输出
 */

void TImerA_SetSquareWaveMode(TimerSource_TypeDef TimerSource, TimerDivde_TypeDef TimerDivde,TimerPWM_TypeDef TimerPWM, TimerOutputPin_TypeDef TimerOutputPin, u16 u16Period, u16 u16Duty)
{
    TACTL |= TACLR + TimerPWM + TimerSource + TimerDivde;
    if(TimerOutputPin == TimerOutputPin_P11)
    {
        P1SEL |= BIT1;
        P1DIR |= BIT1;
        CCR0 = u16Period;
    }
    if(TimerOutputPin == TimerOutputPin_P12)
    {
      
    }
    if(TimerOutputPin == TimerOutputPin_P13)
    {
      
    }
    if(TimerOutputPin == TimerOutputPin_P15)
    {
      
    }
    if(TimerOutputPin == TimerOutputPin_P16)
    {
      
    }
    if(TimerOutputPin == TimerOutputPin_P17)
    {
      
    }
}

//void TimerA_SetPWMMode
/**
 * 定时器A0中断服务函数
 */
#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA_0_ISR(void)   //定时器中断函数
{
	Count++;
	if(Count==100)//100次为1秒
  {
    Second++;
    Count=0;
    P6OUT = ~(P6OUT&BIT1);//P61取反闪烁
  }
  while(Second>99)Second=0;//最大计数99秒
}



