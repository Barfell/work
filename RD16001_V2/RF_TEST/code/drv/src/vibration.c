#include "vibration.h"
#include "msp430.h"
#include "timer.h"
#include "kernel.h"
#include "key.h"


long SysTick = 0;
unsigned int LongKey = 0;
unsigned char JiaoZhunFlag = 0;
unsigned char freqORtick = 0;

unsigned char   FreqMeasureFinishFlag = 0;
unsigned long   TimeValue = 0;
float            freq = 0;
    
//控制脚初始化
void VibrationIoInit(void)
{
  P9REN &= ~BIT4;
  P9DIR |= BIT4;//vw_trcn P94
  P9OUT |= BIT4;
}
//VW-TRAN   P94
//连接发射
void SetConnectToTran(void)
{
  P9OUT &= ~BIT4;//vw_trcn -> 0
}
//VW-TRAN   P94
//连接接收
void SetConnectToRec(void)
{
  P9OUT |= BIT4;//vw_trcn -> 1
}

//控制脚初始化
void FAN3122IoInit(void)
{
  P9REN &= ~BIT3;
  P9DIR |= BIT3;//VW_EN P94
  P9OUT |= BIT3;
}
//VW-TRAN   P94
//连接发射
void FAN3122_OFF(void)
{
  P9OUT &= ~BIT3;//VW_EN -> 0
}
//VW-TRAN   P94
//连接接收
void FAN3122_ON(void)
{
  P9OUT |= BIT3;//VW_EN -> 1
}



//VW-DRIVER   P35
//100 - 4000000hz
void TranFreq(int freq)
{
  u16 TimeNum=0,i=0;
  TimeNum = 15000/freq;//8个脉冲
  /*TB作为输出，P35脚输出PWM波形*/
  TB0_Freq(freq);
  if( TimeNum < 1 )
    {delay_ms(1);}
  else
    {
      for(i=0;i<TimeNum;i++)
        {delay_ms(1);}
    }
  
  P3SEL  &= ~BIT5;
  P3DIR  |= BIT5;
  P3OUT  &= ~BIT5;
   
}



//开始捕获脉冲
void CaptureOn(void)
{
  /*TA定时器1的时钟选择为外部时钟*/
  //p15-taclk---recive pin
  freqORtick = 1;//freq测量模式
  SysTickOff();
  
  
  TimerA_TACLK();
}


//关闭脉冲捕获
void CaptureOff(void)
{
  P1DIR |= BIT5; 
  P1SEL &= ~BIT5; 
  P1OUT &= ~BIT5;
  
  TACCTL0 &= ~CCIE;
  TACCTL2 &= ~CCIE;
  TACCTL1 &= ~CCIE; 
  TACCR0 = 0;
  TACCR1 = 0;
  TACCR2 = 0;
  TACTL = MC_0 + TACLR;
  
  SysTickInit();
  freqORtick = 0;//tick模式
}






/***************************************************
 * 定时器A中断服务函数
 ***************************************************
 */
//ccr1、ccr2、TAIFG溢出中断
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void)
{
//  //tick
//  if(freqORtick == 0)
//  {
//      
//  }
  //freq
//  else if(freqORtick == 1)
//  {
        switch( TAIV )
        {
              //ccr1
            case  2: TBR = 0;
                      //TB定时器设置为 smclk  连续模式 不分频
                     TBCTL = TBSSEL_2 + MC_2 + ID_3;      //TB开始计时,时间0(smclk-Continous-div0)
                     TBR = 0;
                    // printf("ccr1----20,  TAR= %d TBR= %d\r\n",TAR,TBR); //这个函数耗费时间比较多，需要注释掉
                     break;
             //ccr2
            case  4: TimeValue = TBR;
                     // printf("TAR= %d TBR= %ld\r\n",TAR,TimeValue);
                     TBR = 0;
                     TBCTL = MC_0+TBCLR;                       //TB结束计时，时间1
                     freq = 50 / ((float)TimeValue/1000000);
                     TimeValue = 0;
                     FreqMeasureFinishFlag = 1;//频率采集结束
                     //printf("freq : %f\r\n",freq);
                     CaptureOff();
                     break;
             //taifg
            case 10: //printf("Timer_A3 overflow\r\n");   // Timer_A3 overflow
                     break;
       }
//  }
}


//CCR0溢出中断
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void)
{
      SysTick++;
      KeyTask();
      if(KeyCont != 0)//按键按下
          {
            LongKey++;
            if(LongKey == KEY_TIME)
              { LongKey = 0;JiaoZhunFlag = !JiaoZhunFlag; }
          }
      else if(KeyCont == 0)//按键松开
          { LongKey = 0; }
}


