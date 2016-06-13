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
  VibrationIoInit();
  FAN3122IoInit();
}



/*获取振弦频率，返回频率值*/
float GetFreq(void)
{
  unsigned short        dly = 0;
  unsigned int          i = 400;//400hz开始激励
  
  /*---------发射--------------------------------------------------------*/
   FAN3122_ON();//开启发射芯片
   
    SetConnectToTran();
    delay_ms(20);
//    TB0_Freq(1600);
    while(i<6000)
    {
      TranFreq(i);
      i += 100;
    }
    delay_ms(30);
    FAN3122_OFF();
    SetConnectToRec();
    //开始捕获波形
    CaptureOn();
    //等待测量完毕,超时判断为300ms
    while(FreqMeasureFinishFlag != 1)
    {
      delay_ms(1);
      dly++;
      if(dly > 2500)
      {freq = 0;break;}
    }
    FreqMeasureFinishFlag = 0;
    SetConnectToTran();
    return freq;
}


