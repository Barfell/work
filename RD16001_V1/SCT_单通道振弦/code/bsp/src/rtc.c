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
 BTCTL  |=  BT_fCLK2_ACLK_DIV256 + BT_fCLK2_DIV128 + BTHOLD;            //设置BASIC TIMER    256分频后再128分频得到1秒频率给RTC作为时钟
 IE2    &= ~BTIE;                                                       //关闭基本定时器中断
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

void GetRtc(char *rtcdata)
{
  char timestring[50];
  char stringyear[3]     ={'\0'};
  char stringmounth[3]   ={'\0'};
  char stringdate[3]     ={'\0'};
  char stringdow[3]     ={'\0'};
  char stringhour[3]     ={'\0'};
  char stringmin[3]      ={'\0'};
  char stringsec[3]      ={'\0'};
  hextostr(stringyear,(unsigned char)RTCYEAR);
  hextostr(stringmounth,RTCMON);
  hextostr(stringdate,  RTCDAY);
  hextostr(stringdow,  RTCDOW);
  hextostr(stringhour,  RTCHOUR);
  hextostr(stringmin,   RTCMIN);
  hextostr(stringsec,   RTCSEC);
  sprintf(timestring,"RTC:  20%s-%s-%s  %s:%s:%s   weekend:%s",stringyear,stringmounth,
                      stringdate,stringhour,stringmin,stringsec,stringdow);
  memcpy(rtcdata,timestring,strlen(timestring));
  
}

void SetRtc(
            unsigned int year,
            unsigned char mounth,
            unsigned char day,
            unsigned char dow,
            unsigned char hour,
            unsigned char min,
            unsigned char sec
             )
{
  BTCTL  &= ~BTSSEL;
  BTCTL  |=  BT_fCLK2_ACLK_DIV256 + BT_fCLK2_DIV128 + BTHOLD;            //设置BASIC TIMER    256分频后再128分频得到1秒频率给RTC作为时钟
  IE2    &= ~BTIE;                                                       //关闭基本定时器中断
  RTCCTL  = RTCBCD+RTCMODE_3+RTCTEV_0 + RTCIE + RTCHOLD;                 // RTC enable, BCD mode, // RTCBCD+
                                                                      // alarm every Minute,
                                                                      // enable RTC interrupt
  // Init time
  RTCSEC =  sec;                       // Set Seconds
  RTCMIN =  min;                       // Set Minutes
  RTCHOUR = hour;                       // Set Hours
  // Init date
  RTCDOW =  dow;                       // Set DOW
  RTCDAY =  day;                       // Set Day
  RTCMON =  mounth;                       // Set Month
  RTCYEAR = year;                     // Set Year
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