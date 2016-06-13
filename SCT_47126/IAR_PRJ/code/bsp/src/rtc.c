#include <msp430.h>
#include "gpio.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
#include "power.h"
#include "rtc.h"
#include <stdio.h>

void rtc_init(void)
{
 BTCTL  &= ~BTSSEL;
 BTCTL  |=  BT_fCLK2_ACLK_DIV256 + BT_fCLK2_DIV128 + BTHOLD;            //����BASIC TIMER    256��Ƶ����128��Ƶ�õ�1��Ƶ�ʸ�RTC��Ϊʱ��
 IE2    &= ~BTIE;                                                       //�رջ�����ʱ���ж�
 RTCCTL  = RTCBCD+RTCMODE_3+RTCTEV_0 + RTCIE + RTCHOLD;                 // RTC enable, BCD mode,
                                                                        // alarm every Minute,
                                                                        // enable RTC interrupt
  // Init time
  RTCSEC =  0x00;                       // Set Seconds
  RTCMIN =  0x00;                       // Set Minutes
  RTCHOUR = 0x08;                       // Set Hours
  // Init date
  RTCDOW =  0x02;                       // Set DOW
  RTCDAY =  0x23;                       // Set Day
  RTCMON =  0x08;                       // Set Month
  RTCYEAR = 0x2005;                     // Set Year
  RTCCTL &= ~RTCHOLD;                   // Enable RTC
}

void read_rtc(void)
{
  printf("year:%d-",(RTCYEAR));
  printf("mon:%d-",RTCMON);
  printf("day:%d-",RTCDAY);
  printf("dow:%d-",RTCDOW);
  printf("hour:%d-",RTCHOUR);
  printf("min:%d-",RTCMIN);
  printf("sec:%d\r\n",RTCSEC);
}

#pragma vector=BASICTIMER_VECTOR
__interrupt void basic_timer(void)
{
  LPM3_EXIT;
  //printf("rtc_timer lpm3 exit\r\n");
}