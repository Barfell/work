#include "kernel.h"
#include "msp430f149_uart.h"
#include "msp430f149_gpio.h"
#include "msp430f149_timer.h"

//连接发射
void SetConnectToTran(void)
{
  P2OUT &= ~BIT4;
}
//连接接收
void SetConnectToRec(void)
{
  P2OUT |= BIT4;
}

//100 - 4000000
void TranFreq(u32 freq)
{
  u16 TimeNum=0,i=0;
  TimeNum = 8000/freq;
  TimerB_SetPWMMode(TimerSourceB_MCLK, TimerDivde_0, OUTMOD_6, TimerOutputPin_P41, 4000000/freq , 2000000/freq);
  if( TimeNum < 1 )
    {delay_ms(1);}
  else
    {
      for(i=0;i<TimeNum;i++)
        {delay_ms(1);}
    }
}



void CaptureOn(void)
{
  TimerA_TACLK();
}

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