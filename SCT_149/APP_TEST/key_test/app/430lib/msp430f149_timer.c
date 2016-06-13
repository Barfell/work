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
 * @brief ���ö�ʱ�� A Ϊ��ʱ����,Ĭ��ʹ�� TA0 �ж�
 * @param TimerSource ��ʱ��ʱ����Դ
 * @param TimerDivde  ��ʱ����Ƶѡ��
 * @param u16Count    ��ʱ������ֵ
 */
void TimerA_SetTimerMode(TimerSource_TypeDef TimerSource, TimerDivde_TypeDef TimerDivde,u16 u16Count)
{
    /*MC0 ѡ��������ģʽ*/
    TACTL |= TACLR + MC0 + TimerSource + TimerDivde;
    /*���� TACCR0 �ж�*/
    TACCTL0 = CCIE;
    TACCR0 = u16Count;
}

/*  TA0   TA1   TA2
    P1.1  P1.2  P1.3
    P1.5  P1.6  P1.7
TA0 ������ܵ���ռ�ձ�,��ֻ��ѡ��TA1,TA2��ΪPWM���
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
 * ��ʱ��A0�жϷ�����
 */
#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA_0_ISR(void)   //��ʱ���жϺ���
{
	Count++;
	if(Count==100)//100��Ϊ1��
  {
    Second++;
    Count=0;
    P6OUT = ~(P6OUT&BIT1);//P61ȡ����˸
  }
  while(Second>99)Second=0;//������99��
}



