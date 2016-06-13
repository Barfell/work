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
    
//���ƽų�ʼ��
void VibrationIoInit(void)
{
  P9REN &= ~BIT4;
  P9DIR |= BIT4;//vw_trcn P94
  P9OUT |= BIT4;
}
//VW-TRAN   P94
//���ӷ���
void SetConnectToTran(void)
{
  P9OUT &= ~BIT4;//vw_trcn -> 0
}
//VW-TRAN   P94
//���ӽ���
void SetConnectToRec(void)
{
  P9OUT |= BIT4;//vw_trcn -> 1
}

//���ƽų�ʼ��
void FAN3122IoInit(void)
{
  P9REN &= ~BIT3;
  P9DIR |= BIT3;//VW_EN P94
  P9OUT |= BIT3;
}
//VW-TRAN   P94
//���ӷ���
void FAN3122_OFF(void)
{
  P9OUT &= ~BIT3;//VW_EN -> 0
}
//VW-TRAN   P94
//���ӽ���
void FAN3122_ON(void)
{
  P9OUT |= BIT3;//VW_EN -> 1
}



//VW-DRIVER   P35
//100 - 4000000hz
void TranFreq(int freq)
{
  u16 TimeNum=0,i=0;
  TimeNum = 15000/freq;//8������
  /*TB��Ϊ�����P35�����PWM����*/
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



//��ʼ��������
void CaptureOn(void)
{
  /*TA��ʱ��1��ʱ��ѡ��Ϊ�ⲿʱ��*/
  //p15-taclk---recive pin
  freqORtick = 1;//freq����ģʽ
  SysTickOff();
  
  
  TimerA_TACLK();
}


//�ر����岶��
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
  freqORtick = 0;//tickģʽ
}






/***************************************************
 * ��ʱ��A�жϷ�����
 ***************************************************
 */
//ccr1��ccr2��TAIFG����ж�
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
                      //TB��ʱ������Ϊ smclk  ����ģʽ ����Ƶ
                     TBCTL = TBSSEL_2 + MC_2 + ID_3;      //TB��ʼ��ʱ,ʱ��0(smclk-Continous-div0)
                     TBR = 0;
                    // printf("ccr1----20,  TAR= %d TBR= %d\r\n",TAR,TBR); //��������ķ�ʱ��Ƚ϶࣬��Ҫע�͵�
                     break;
             //ccr2
            case  4: TimeValue = TBR;
                     // printf("TAR= %d TBR= %ld\r\n",TAR,TimeValue);
                     TBR = 0;
                     TBCTL = MC_0+TBCLR;                       //TB������ʱ��ʱ��1
                     freq = 50 / ((float)TimeValue/1000000);
                     TimeValue = 0;
                     FreqMeasureFinishFlag = 1;//Ƶ�ʲɼ�����
                     //printf("freq : %f\r\n",freq);
                     CaptureOff();
                     break;
             //taifg
            case 10: //printf("Timer_A3 overflow\r\n");   // Timer_A3 overflow
                     break;
       }
//  }
}


//CCR0����ж�
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void)
{
      SysTick++;
      KeyTask();
      if(KeyCont != 0)//��������
          {
            LongKey++;
            if(LongKey == KEY_TIME)
              { LongKey = 0;JiaoZhunFlag = !JiaoZhunFlag; }
          }
      else if(KeyCont == 0)//�����ɿ�
          { LongKey = 0; }
}


