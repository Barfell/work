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
#include "stdio.h"

unsigned int NumFlag = 0;
unsigned int TimeValue1=0;
unsigned int TimeValue2=0;
unsigned  Freq = 0;


unsigned char Trg;
unsigned char Cont;
/**
 * @brief ���ö�ʱ�� A Ϊ��ʱ����,Ĭ��ʹ�� TA0 �ж�
 * @param TimerSource ��ʱ��ʱ����Դ @TimerSource_TypeDef
 * @param TimerDivde  ��ʱ����Ƶѡ�� @TimerDivde_TypeDef
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
/**
 * @biref ���� TimerA ���PWM���� 
 * @param TimerSource    ��ʱ��ʱ����Դ @TimerSource_TypeDef
 * @param TimerDivde     ��ʱ����Ƶѡ�� @TimerDivde_TypeDef
 * @param TimerPWMMode   ��ʱ�� PWM ģʽѡ��,������ѡ�� 3 �� 7
 * @param TimerOutputPin ��ʱ�� PWM �������ѡ��. ѡ�� TA0 ���޷�����ռ�ձ�
 * @param u16Period      PWM ����
 * @param u16Duty        PWM ��Ч��ƽ
 */
void TimerA_SetPWMMode(TimerSource_TypeDef TimerSource, TimerDivde_TypeDef TimerDivde,TimerPWMMode_TypeDef TimerPWMMode, TimerOutputPin_TypeDef TimerOutputPin, u16 u16Period, u16 u16Duty)
{
   TACTL |= TimerSource + TimerDivde + MC_3;
    if(TimerOutputPin == TimerOutputPin_P11)
    {
        P1SEL |= BIT1;
        P1DIR |= BIT1;
        TACCR0 = u16Period;
    }
   else if(TimerOutputPin == TimerOutputPin_P12)
    {
        P1SEL |= BIT2;
        P1DIR |= BIT2;
        TACCR0 = u16Period;
        TACCR1 = u16Duty;
        CCTL1 =  TimerPWMMode;
    }
   else if(TimerOutputPin == TimerOutputPin_P13)
    {
        P1SEL |= BIT3;
        P1DIR |= BIT3;
        TACCR0 = u16Period;
        TACCR2 = u16Duty;
        CCTL2 =  TimerPWMMode;
    }
   else if(TimerOutputPin == TimerOutputPin_P15)
    {
        P1SEL |= BIT5;
        P1DIR |= BIT5;
        TACCR0 = u16Period;
    }
   else if(TimerOutputPin == TimerOutputPin_P16)
    {
        P1SEL |= BIT6;
        P1DIR |= BIT6;
        TACCR0 = u16Period;
        TACCR1 = u16Duty;
        CCTL1 =  TimerPWMMode;
    }
   else if(TimerOutputPin == TimerOutputPin_P17)
    {
//        P1SEL |= BIT3;  //ʵ��֤���� P13��P17����ͬʱ���
//        P1DIR |= BIT3;
        
        
        P1SEL |= BIT7;
        P1DIR |= BIT7;
        TACCR0 = u16Period;
        TACCR2 = u16Duty;
        CCTL2 =  TimerPWMMode;
    }
    
    
    
}






/**
 * @biref ���� TimerB ���PWM���� 
 * @param TimerSource    ��ʱ��ʱ����Դ @TimerSource_TypeDef
 * @param TimerDivde     ��ʱ����Ƶѡ�� @TimerDivde_TypeDef
 * @param TimerPWMMode   ��ʱ�� PWM ģʽѡ��,������ѡ�� 3 �� 7
 * @param TimerOutputPin ��ʱ�� PWM �������ѡ��. ѡ�� TA0 ���޷�����ռ�ձ�
 * @param u16Period      PWM ����
 * @param u16Duty        PWM ��Ч��ƽ
 */
void TimerB_SetPWMMode(TimerSource_TypeDef TimerSource, TimerDivde_TypeDef TimerDivde,TimerPWMMode_TypeDef TimerPWMMode, TimerOutputPin_TypeDef TimerOutputPin, u16 u16Period, u16 u16Duty)
{
  TBCTL = TimerSource + MC_3 + TimerDivde;   // TimerSource, up-down mod 
  if(TimerOutputPin == TimerOutputPin_P40)
  {
    P4DIR |= BIT0;                            
    P4SEL |= BIT0;                           
    TBCCR0 = u16Period;
    TBCCR0 = u16Duty;                              
    TBCCTL0 = TimerPWMMode;                       
  }
 else if(TimerOutputPin == TimerOutputPin_P41)
  {
    P4DIR |= BIT1;                            
    P4SEL |= BIT1;                           
    TBCCR0 = u16Period;
    TBCCR1 = u16Duty;                              
    TBCCTL1 = TimerPWMMode;                       
  }
 else if(TimerOutputPin == TimerOutputPin_P42)
  {
    P4DIR |= BIT2;                            
    P4SEL |= BIT2;                           
    TBCCR0 = u16Period;
    TBCCR2 = u16Duty;                              
    TBCCTL2 = TimerPWMMode;                       
  }
 else if(TimerOutputPin == TimerOutputPin_P43)
  {
    P4DIR |= BIT3;                            
    P4SEL |= BIT3;                           
    TBCCR0 = u16Period;
    TBCCR3 = u16Duty;                              
    TBCCTL3 = TimerPWMMode;                      
  }
 else if(TimerOutputPin == TimerOutputPin_P44)
  {
    P4DIR |= BIT4;                            
    P4SEL |= BIT4;                           
    TBCCR0 = u16Period;
    TBCCR4 = u16Duty;                              
    TBCCTL4 = TimerPWMMode;                       
  }
 else if(TimerOutputPin == TimerOutputPin_P45)
  {
    P4DIR |= BIT5;                            
    P4SEL |= BIT5;                           
    TBCCR0 = u16Period;
    TBCCR5 = u16Duty;                              
    TBCCTL5 = TimerPWMMode;                       
  }
 else if(TimerOutputPin == TimerOutputPin_P46)
  {
    P4DIR |= BIT6;                            
    P4SEL |= BIT6;                           
    TBCCR0 = u16Period;
    TBCCR6 = u16Duty;                             
    TBCCTL6 = TimerPWMMode;                     
  }
}







/*  ��������
    TA0   TA1   TA2
    P1.1  P1.2  P1.3
    P1.5  P1.6  P1.7
 */
void TimerA_CaptureMode(TimerSource_TypeDef TimerSource, TimerDivde_TypeDef TimerDivde, TimerOutputPin_TypeDef TimerOutputPin, TimerEdge_TypeDef TimerEdge)
{
    TACTL = TimerSource + MC_2 + TimerDivde;                  // TimerSource + Continuous Mode +TimerDivde
    //p11-p13
    if(TimerOutputPin == TimerOutputPin_P11)
    {
      P1DIR &= ~0x02; 
      P1DIR = 0;
      P1SEL |= 0x02;                             // Set P1.1 to TA0
      CCTL0 = TimerEdge + SCS + CCIS_0 + CAP + CCIE; // dge + Capture Mode + Interrupt
    }
    else if(TimerOutputPin == TimerOutputPin_P12)
    {
     P1DIR &= ~0x04;     
      P1DIR = 0;   
      P1SEL |= BIT2;                             
      CCTL1 = TimerEdge + SCS + CCIS_0 + CAP + CCIE; 
    }
   else if(TimerOutputPin == TimerOutputPin_P13)
    {
      P1DIR &= ~0x08;        
      P1DIR = 0;
      P1SEL |= BIT3;                             
      CCTL2 = TimerEdge + SCS + CCIS_0 + CAP + CCIE; 
    }
    //p15-p17
    else if(TimerOutputPin == TimerOutputPin_P15)
    {
      P1DIR &= ~0x20;        
      P1DIR = 0;
      P1SEL |= BIT5;                             
      CCTL0 = TimerEdge + SCS + CCIS_0 + CAP + CCIE;
    }
    else if(TimerOutputPin == TimerOutputPin_P16)
    {
      P1DIR &= ~0x40;        
      P1DIR = 0;
      P1SEL |= BIT6;                             
      CCTL1 = TimerEdge + SCS + CCIS_0 + CAP + CCIE;
    }
    else if(TimerOutputPin == TimerOutputPin_P17)
    {
      P1DIR &= ~0x80;        
      P1DIR = 0;
      P1SEL |= BIT7;      
      CCTL2 = TimerEdge + SCS + CCIS_0 + CAP + CCIE;
    }
}

//20ms�ж�һ��
void KeyTimerSet(void)
{
  TACTL |= TASSEL_2 + ID_0 + MC_3;//smclk - div0 - up/down mode
  TACCR0  = 60000;
  TACCTL0  = OUTMOD_4 + CCIE;
}

void Key(void)
{
  unsigned char ReadValue  = (P1IN | 0xfe) ^ 0xff;//0xfe----p10  ��Ϊ���� 
  Trg = ReadValue & (ReadValue ^ Cont);
  Cont = ReadValue;
}


/**
 * ��ʱ��A0�жϷ�����
 */
#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA_0_ISR(void)   //��ʱ���жϺ���
{
  Key();
}



