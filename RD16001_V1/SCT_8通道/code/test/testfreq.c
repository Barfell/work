//#include <msp430.h>
//#include "gpio.h"
//#include "uart.h"
//#include "kernel.h"
//#include "clk.h"
//#include "freq.h"
//#include "power.h"
//#include "vibration.h"
//#include "timer.h"
//
//void tblisten(void)
//{
//  TBCCTL0 = CCIE;                           // TBCCR0 interrupt enabled
//  TBCCR0 = 40000;
//  TBCTL = TBSSEL_2 + MC_1 + ID_3;                  // SMCLK, up mode    
//}
//
//int trr_s;
//int trr_e;
//int trr_times = 0;
//char trrflag = 0;
//void testfreq(void)
//{
//  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
//  ClkInit();
//  PowerInit();
//  PWR_ON;
//  CORE_PWR_ON;
//  COLL_PWR_ON;
//  
//  UARTInit(UART_0, UART_Clk_SMCLK, Baud_115200);
//  
//  
//  P1DIR  |=  BIT5;                     
//  P1SEL  |=  BIT5;//aclk
//  P1DIR  &=  ~BIT2;                     
//  P1SEL  |=  BIT2;//capture
//  //tblisten();
//  TACTL  |=  TASSEL_2 + ID_0 + MC_2 + TACLR;         //ѡ��SMCLKΪ��ʱ��ʱ�ӣ�����Ƶ������������ʽ��
//  TACCTL1 =  CAP+CM_1+CCIS_0+SCS+CCIE;               //�����ز���CCI2A���������룬ͬ����ʽ������ʽ���������жϡ�
//  _EINT();
//
//  while(1)
//  {
//    if(trrflag == 2)
//    {
//     trr_times = trr_e - trr_s;
//     printf("times :%d\r\n",trr_times);
//     trrflag = 0;
//    }
//  }
//}
//
//
//
//#pragma vector=TIMERA1_VECTOR
//__interrupt void Timer_A1(void)
//{
// switch(TAIV) 
// {
// case 2:
//   if(trrflag == 1)
//    {trr_e = TAR;trrflag = 2;}     
//   if(trrflag == 0)
//    {trr_s = TAR;trrflag = 1;}
////   
////   trr_times++;
//   break; 
// case 4: 
//     break; 
// case 10: 
//     break; 
//  }
//}
//
//
//
//
//
//
//#pragma vector=TIMERB0_VECTOR
//__interrupt void Timer_B (void)
//{
//  printf("captures:%d\r\n",trr_times);
//  trr_times = 0;
//  TACTL  |=  TASSEL_2 + ID_0 + MC_2 + TACLR;         //ѡ��SMCLKΪ��ʱ��ʱ�ӣ�����Ƶ������������ʽ��
//  TACCTL1 =  CAP+CM_1+CCIS_0+SCS+CCIE;               //�����ز���CCI2A���������룬ͬ����ʽ������ʽ���������жϡ�
//}
//

/**************************************************************************************/
/*****************************����TACLK��Ϊ��ʱ��A��ʱ�ӣ�����TA��� һ������*************************************************/
/**************************************************************************************/

//#include <msp430.h>
//#include "gpio.h"
//#include "uart.h"
//#include "kernel.h"
//#include "clk.h"
//#include "freq.h"
//#include "power.h"
//#include "vibration.h"
//#include "timer.h"
//
////?????????2016-4-5 �ⲿvbat�����󽫻ᵼ��taclk����������
//void testfreq(void)
//{
//  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
//  ClkInit();
//  PowerInit();
//  PWR_ON;
//  CORE_PWR_ON;
//  COLL_PWR_ON;
//  
//  UARTInit(UART_0, UART_Clk_SMCLK, Baud_115200);
//  TB0_Freq(8000);
//  
//  P1REN  &=  ~BIT5;
//  P1DIR  &=  ~BIT5;                     
//  P1SEL  |=  BIT5;//taclk
//  
//  P1REN  &=  ~BIT2;
//  P1DIR  |=   BIT2;         
//  P1OUT  &=  ~BIT2;
//  P1SEL  |=   BIT2;//ta1
//
//  CCR0  = 8-1;                             // PWM Period
//  CCTL1 = OUTMOD_7;                        // CCR1 reset/set
//  CCR1  = 4;                               // CCR1 PWM duty cycle
//  TACTL  |=  TASSEL_0 + ID_0 + MC_1 + TACLR;         //ѡ��TACLKΪ��ʱ��ʱ�ӣ�����Ƶ,
//  while(1)
//  {
//  }
//}
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
#include <msp430.h>
#include "gpio.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "freq.h"
#include "power.h"
#include "vibration.h"
#include "timer.h"

//?????????2016-4-5 �ⲿvbat�����󽫻ᵼ��taclk����������
void testfreq(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  ClkInit();
  PowerInit();
  PWR_ON;
  CORE_PWR_ON;
  COLL_PWR_ON;
  
  UARTInit(UART_0, UART_Clk_SMCLK, Baud_115200);
  FreqInit();
  SetConnectToTran();
  delay_ms(2000);
  printf("init ok\r\n");
  while(1)
  {
    printf("freq is:%f\r\n",GetFreq());
    delay_ms(5000);
  }
}