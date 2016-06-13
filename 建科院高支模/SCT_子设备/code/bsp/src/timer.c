#include "msp430.h"
#include "timer.h"

//tb0 ���͹̶�Ƶ������
void TB0_Freq(int f)
{
  P3REN  &= ~BIT5;
  P3DIR  |= BIT5;                     
  P3SEL  |= BIT5; 
  
  TBCCTL0 = OUTMOD_4;                       // toggle
  TBCCR0  = 4000000/f-1;
  TBCTL   = TBSSEL_2 + MC_1;                // SMCLK, Up to CCR0 mode
}

//taʹ��taclk��Ϊ��ʱ��ʱ��
void TimerA_TACLK(void)
{
  //p15-taclk
  P1REN &= ~BIT5;
  P1DIR &= ~BIT5; 
  P1SEL |=  BIT5;// Set P1.5to TACLK
  
  //���ò���Ƶ������ģʽ��ʱ��Ϊ�ⲿʱ��Դ TACLK
  TACTL = TASSEL_0 + MC_2 + ID_0 + TACLR;// taclk + Continuous Mode + Div0
  //�ӵ�100�����忪ʼ��ʱ
  TACCR1 = 100;//��ʼ��ʱ
  //50��������ʱ���������Լ���Ƶ����
  TACCR2 = 150;//50�������
  /*�����ж�*/
  TACCTL2 = CCIE;//��ʼ��ʱ�ж�
  TACCTL1 = CCIE;//������ʱ�ж�
  _EINT();//�����ж�
}