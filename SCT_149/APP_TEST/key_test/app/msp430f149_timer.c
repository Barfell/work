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
 * @brief 设置定时器 A 为定时功能,默认使用 TA0 中断
 * @param TimerSource 定时器时钟来源 @TimerSource_TypeDef
 * @param TimerDivde  定时器分频选择 @TimerDivde_TypeDef
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
/**
 * @biref 设置 TimerA 输出PWM波形 
 * @param TimerSource    定时器时钟来源 @TimerSource_TypeDef
 * @param TimerDivde     定时器分频选择 @TimerDivde_TypeDef
 * @param TimerPWMMode   定时器 PWM 模式选择,方波请选择 3 或 7
 * @param TimerOutputPin 定时器 PWM 输出引脚选择. 选择 TA0 将无法调节占空比
 * @param u16Period      PWM 周期
 * @param u16Duty        PWM 有效电平
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
//        P1SEL |= BIT3;  //实验证明了 P13和P17可以同时输出
//        P1DIR |= BIT3;
        
        
        P1SEL |= BIT7;
        P1DIR |= BIT7;
        TACCR0 = u16Period;
        TACCR2 = u16Duty;
        CCTL2 =  TimerPWMMode;
    }
    
    
    
}






/**
 * @biref 设置 TimerB 输出PWM波形 
 * @param TimerSource    定时器时钟来源 @TimerSource_TypeDef
 * @param TimerDivde     定时器分频选择 @TimerDivde_TypeDef
 * @param TimerPWMMode   定时器 PWM 模式选择,方波请选择 3 或 7
 * @param TimerOutputPin 定时器 PWM 输出引脚选择. 选择 TA0 将无法调节占空比
 * @param u16Period      PWM 周期
 * @param u16Duty        PWM 有效电平
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







/*  捕获输入
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

//20ms中断一次
void KeyTimerSet(void)
{
  TACTL |= TASSEL_2 + ID_0 + MC_3;//smclk - div0 - up/down mode
  TACCR0  = 60000;
  TACCTL0  = OUTMOD_4 + CCIE;
}

void Key(void)
{
  unsigned char ReadValue  = (P1IN | 0xfe) ^ 0xff;//0xfe----p10  作为检测脚 
  Trg = ReadValue & (ReadValue ^ Cont);
  Cont = ReadValue;
}


/**
 * 定时器A0中断服务函数
 */
#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA_0_ISR(void)   //定时器中断函数
{
  Key();
}



