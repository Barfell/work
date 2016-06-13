/**********************************************
此文件用于振弦传感器的频率测量
*/

#include "Vibration.h"
#include "Freq.h"
#include "Power.h"


/*使用振弦需要的初始化*/
void FreqInit(void)
{
  VibrationIoInit();
}



/*获取振弦频率，返回频率值*/
float GetFreq(void)
{
  unsigned short        dly = 0;
  unsigned int          i=400;//400hz开始激励
  
  /*发射----------------*/
    DRIVER_EN_ON;//开启发射芯片
    SetConnectToTran();
    delay_ms(20);
    while(i<8000)
    {
      TranFreq(i);
      i += 200;
    }
    DRIVER_EN_OFF;//关闭发射芯片
    
    
    
  /*捕获频率-----------*/
    SetConnectToRec();
    delay_ms(20);
    //开始捕获波形
    CaptureOn();
    //等待测量完毕,超时判断为300ms
    while(FreqMeasureFinishFlag != 1)
    {
      delay_ms(1);
      dly++;
      if(dly > 300)
      {break;}
    }
    FreqMeasureFinishFlag = 0;
    return freq;
}


