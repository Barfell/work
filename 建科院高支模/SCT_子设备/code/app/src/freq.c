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
  /*---------------����ѡ��--------*/
  P5REN &=  ~BIT2;
  P5DIR |=   BIT2;
  P5OUT &=   ~BIT2;//VW_485 SW-0(FREQ)

  VibrationIoInit();//VW_TRAN (���䲨�λ��ǽ��ղ��ε�ѡ��)
  FAN3122IoInit();//VW_EN�����䲨��ʱ�������߹رշ���оƬ��
}



/*��ȡ����Ƶ�ʣ�����Ƶ��ֵ*/
float GetFreq(void)
{
  unsigned short        dly = 0;
  unsigned int          i = 400;//400hz��ʼ����
  
  freq = 0.0;//��ȡ��Ƶ��

    FAN3122_ON();//��������оƬ
   
    SetConnectToTran();
    delay_ms(20);

    while(i<4000)
    {
      TranFreq(i);
      i += 50;
    }
    delay_ms(30);
    FAN3122_OFF();
    
    //��ʼ������
    SetConnectToRec();
    CaptureOn();
    while(FreqMeasureFinishFlag != 1)
    {
      delay_ms(1);
      dly++;
      if(dly > 2500)
      { freq = 0; dly = 0; break; }
    }
    //��һ�β�������Ƶ����Ϊ���䣬�ٴμ���
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


