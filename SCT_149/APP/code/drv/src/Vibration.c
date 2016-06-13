#include "kernel.h"
#include "msp430f149_uart.h"
#include "msp430f149_gpio.h"
#include "msp430f149_timer.h"

unsigned char   FreqMeasureFinishFlag = 0;
unsigned long   TimeValue = 0;
float            freq = 0;
    
//控制脚初始化
void VibrationIoInit(void)
{
  P1DIR |= BIT2;//vw_trcn P12
  P1OUT |= BIT2;
}


//VW-TRAN   P12
//连接发射
void SetConnectToTran(void)
{
  P1OUT &= ~BIT2;//vw_trcn -> 0
}

//连接接收
void SetConnectToRec(void)
{
  P1OUT |= BIT2;//vw_trcn -> 1
}




//VW-DRIVER   P41
//100 - 4000000hz
void TranFreq(u32 freq)
{
  u16 TimeNum=0,i=0;
  TimeNum = 8000/freq;//8个脉冲
  /*TB作为输出，P41脚输出PWM波形*/
  TimerB_SetPWMMode(TimerSourceB_MCLK, TimerDivde_0, OUTMOD_6, TimerOutputPin_P41, 4000000/freq , 2000000/freq);
  if( TimeNum < 1 )
    {delay_ms(1);}
  else
    {
      for(i=0;i<TimeNum;i++)
        {delay_ms(1);}
    }
  
  P4SEL &= ~BIT1;//激发一次后关闭PWM
  P4DIR |= BIT1;                            
  P4OUT &= ~BIT1;//输出‘1’
}



//开始捕获脉冲
void CaptureOn(void)
{
  /*TA定时器1的时钟选择为外部时钟*/
  //p10-taclk---recive pin
  TimerA_TACLK();
}


//关闭脉冲捕获
void CaptureOff(void)
{
  P1DIR |= 0x01; 
  P1SEL &= ~0x01; 
  P1OUT &= ~0x01;
  
  TACCTL0 &= ~CCIE;
  TACCTL2 &= ~CCIE;
  TACCTL1 &= ~CCIE; 
  TACCR0 = 0;
  TACCR1 = 0;
  TACCR2 = 0;
  TACTL = MC_0 + TACLR;
}





/***************************************************
 * 定时器A中断服务函数
 ***************************************************
 */
//ccr1、ccr2、TAIFG溢出中断
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void)
{
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
           printf("TAR= %d TBR= %d\r\n",TAR,TimeValue);
           TBR = 0;
           TBCTL = MC_0+TBCLR;                       //TB结束计时，时间1
           freq = 50 / ((float)TimeValue/1000000);
           TimeValue = 0;
           FreqMeasureFinishFlag = 1;//频率采集结束
           //printf("freq : %f\r\n",freq);
           CaptureOff();
           break;
   //taifg
  case 10: printf("Timer_A3 overflow\r\n");   // Timer_A3 overflow
           break;
 }
}


//CCR0溢出中断
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void)
{
  printf("ccr0-----50000(0)\r\n");
}

