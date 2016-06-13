/*
���ļ��������Ҵ�������Ƶ�ʲ���
*/

#include "Vibration.h"
#include "Freq.h"
#include "kernel.h"
#include "timer.h"


/*ʹ��������Ҫ�ĳ�ʼ��*/
void FreqInit(void)
{
  VibrationIoInit();
  FAN3122IoInit();
}



/*��ȡ����Ƶ�ʣ�����Ƶ��ֵ*/
float GetFreq(void)
{
  unsigned short        dly = 0;
  unsigned int          i = 400;//400hz��ʼ����
  
  /*---------����--------------------------------------------------------*/
   FAN3122_ON();//��������оƬ
   
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
    //��ʼ������
    CaptureOn();
    //�ȴ��������,��ʱ�ж�Ϊ300ms
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


