/*
此文件用于振弦传感器的频率测量
*/

#include "Vibration.h"
#include "Freq.h"
#include "kernel.h"
#include "timer.h"


/*使用振弦需要的初始化*/
void FreqInit(void)
{
  /*---------------功能选择--------*/
  P5REN &=  ~BIT2;
  P5DIR |=   BIT2;
  P5OUT &=   ~BIT2;//VW_485 SW-0(FREQ)

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

    while(i<4000)
    {
      TranFreq(i);
      i += 50;
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


