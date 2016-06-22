/**************************************************
*
*对振弦传感器进行初始化，测量，获取等等
*
***************************************************
*/

#include "Vibration.h"
#include "Freq.h"
#include "cfg.h"
#include "power.h"
#include "kernel.h"
#include "timer.h"
#include <msp430.h>
#include "test.h"
#include "gpio.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
#include "power.h"
#include "flash.h"
#include "dtu.h"
#include "sd.h"
#include "rtc.h"
#include "sensor.h"
#include "cfg.h"
#include "key.h"
#include "s485.h"
#include "ecc.h"
#include "ramloop.h"
#include <stdio.h>


/*使用振弦需要的初始化*/
void FreqInit(void)
{
  /*---------------功能选择--------*/
  P5REN &=  ~BIT1;
  P5DIR |=   BIT1;
  P5OUT &=   ~BIT1;//VW 485      SW-0(FREQ)

  VibrationIoInit();//VW_TRAN (发射波形还是接收波形的选择)
  FAN3122IoInit();//VW_EN（发射波形时候开启或者关闭发射芯片）
}



/*获取振弦频率，返回频率值*/
float GetFreq(void)
{
  unsigned short        dly = 0;
  unsigned int          i = 400;//400hz开始激励
  
  freq = 0.0;//获取的频率

    FAN3122_ON();//开启发射芯片
   
    SetConnectToTran();
    delay_ms(20);

    while(i<6000)
    {
      TranFreq(i);
      i += 100;
    }
    delay_ms(30);
    FAN3122_OFF();
    
    //开始捕获波形
    SetConnectToRec();
    CaptureOn();
    while(FreqMeasureFinishFlag != 1)
    {
      delay_ms(1);
      dly++;
      if(dly > 2500)
      { freq = 0; dly = 0; break; }
    }
    //第一次测量到的频率作为发射，再次激励
      if(FreqMeasureFinishFlag ==1)
      {
        FreqMeasureFinishFlag = 0;
        
        CaptureOff();
        FAN3122_ON();
        SetConnectToTran();
         delay_ms(20);
        TranFreq((int)freq);
        delay_ms(10);
        FAN3122_OFF();
        SetConnectToRec();
        CaptureOn();
        while(FreqMeasureFinishFlag != 1)
        {
          delay_ms(1);
          dly++;
          if(dly > 2500)
          {freq = 0;dly = 0;break;}
        }
      }
    FreqMeasureFinishFlag = 0;
    CaptureOff();
    
    return freq;
}

//获取通道ch的振弦数据，保存到dat中，返回数据长度
unsigned char Get_Freq_CH(unsigned char ch, char *dat)
{
  char retData[100] ={'\0'};
  char timevw[50]= {'\0'};//获取VW传感器数据的时间戳
  unsigned char len = 0;
  unsigned char measureVWTime = 0;//尝试进行测量的次数
  float measureFreq = 0.0;//VW测量结果
  float vol = 0.0;//电源电压
  float VWtemp = 0.0;

  
  CH_Select(ch);
  //获取电源电压
  SDInit();
  delay_ms(500);
  while(vol == 0)
    { vol = GetSD16Voltage(4); }
  vol = vol*776.0 /26.1;
  
  //传感器温度
  VWtemp = Get_VW_Voltage();//电压
  VWtemp = 9950/VWtemp - 21290;//电阻
  VWtemp = GetNTCTemperature(VWtemp);//温度
  
  SDOff();
  
  while(1)
  {
    
    measureFreq = GetFreq();
    if( measureFreq != 0 )
      {
        GetRtc(timevw);
        sprintf(retData,"#%s\r\n#votagle:%f\r\n#%s\r\n#CH1:f-%0.2f t-%0.2f\r\n",MACHINE_ID, vol,timevw, measureFreq,VWtemp);
        len = sizeof(retData);
        memcpy(dat,retData,len);
        //delay_ms(3000);
        break;
      }
    else
     {
        GetRtc(timevw);
        measureVWTime++;
        if(measureVWTime == 2)
          {
            sprintf(retData,"#%s\r\n#votagle:%f\r\n#%s\r\n#CH1:%0.2f\r\n",MACHINE_ID, vol,timevw, measureFreq);
            len = sizeof(retData);
            //printf("%s\r\n",retData);
            memcpy(dat,retData,len);
            //delay_ms(3000);
            measureVWTime = 0;
            memset(timevw,'\0',50);
            break;
          }
        memset(timevw,'\0',50);
        //delay_ms(5000);
     }
  }
  
  return len;
}

