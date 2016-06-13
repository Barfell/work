#include "kernel.h"
#include "msp430f149_uart.h"
#include "msp430f149_gpio.h"
#include "msp430f149_timer.h"
#include "freq.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  RCC_HSECLKInit();
  P2DIR |= BIT4;
 //RCC_LSECLKInit();// 外部低速时钟为主频
 //RCC_DCOCLKInit(7,3);//3.2Mhz  ACLK = LFXT1, MCLK = DCO, SMCLK = DCO
  
  
  
  /*串口测试*/
  UART_Init(UART_0,UART_SouceClk_SMCLK,UART_SMCLKBaud_9600);//设置串口
  printf("hello\r\n");
  
  

  
 /*将ACLK进行输出到P20   P1.4-SMCLK*/
//    P2DIR = 0x01;                             // P2.0-ACLK
//    P2SEL |= 0x01;
//    BCSCTL1 |= DIVA_3;                        // ACLK/2 --- 32.768khz
//    P1DIR = BIT4;                             // P1.4-SMCLK
//    P1SEL |= BIT4;
  
  //mclk为定时器时钟，0分频，PWM output mode: 6 - PWM toggle/set ，输出引脚，占空比
  //TimerA_SetPWMMode(TimerSourceA_TACLK, ID_0, OUTMOD_4, TimerOutputPin_P13, 80 , 40);//输出pwm
  //TimerA_CaptureMode(TimerSourceA_MCLK, TimerDivde_0, TimerOutputPin_P11,  TimerEdge_RISE);//输入捕获模式(只有P11测试有效)   smclk = 8mhz   timA clk = 8/2 = 4mhz
  //TimerB_SetPWMMode(TimerSourceB_MCLK, TimerDivde_0, OUTMOD_6, TimerOutputPin_P42, 2400 , 1200);//输出pwm
  //TimerA_TACLK();//p12-pwm   p10-taclk
  //TimerA_TACLK();
  //_EINT();
  while(1)
  {
  SetConnectToTran();
  delay_ms(20);
  TranFreq(400);
  TranFreq(600);
  TranFreq(800);
  TranFreq(1000);
  TranFreq(1200);
  TranFreq(1400);
  TranFreq(1600);
  TranFreq(1800);
  TranFreq(2000);
  TranFreq(2200);
  TranFreq(2400);
  TranFreq(2600);
  TranFreq(2800);
  TranFreq(3000);
  TranFreq(3200);
  TranFreq(3400);
  TranFreq(3600);
  TranFreq(3800);
  TranFreq(4000);
  TranFreq(4200);
  TranFreq(4400);
  TranFreq(4600);
  TranFreq(4800);
  TranFreq(5000);
//  TranFreq(5200);
//  TranFreq(5400);
//  TranFreq(5600);
//  TranFreq(5800);
//  TranFreq(6000);
//  TranFreq(6200);
//  TranFreq(6400);
//  TranFreq(6600);
//  TranFreq(6800);
//  TranFreq(7000);
//  TranFreq(7200);
//  TranFreq(7400);
//  TranFreq(7600);
//  TranFreq(7800);
  SetConnectToRec();
  delay_ms(20);
 
  
  
  
  CaptureOn();
  delay_ms(5000);
  }
} 







// Watchdog Timer interrupt service routine
//#pragma vector=WDT_VECTOR
//__interrupt void watchdog_timer(void)
//{
// LPM3_EXIT;
//}

