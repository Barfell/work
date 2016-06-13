/**********************************************
���ļ��������Ҵ�������Ƶ�ʲ���
*/

#include "Vibration.h"
#include "Freq.h"
#include "Power.h"


/*ʹ��������Ҫ�ĳ�ʼ��*/
void FreqInit(void)
{
  VibrationIoInit();
}



/*��ȡ����Ƶ�ʣ�����Ƶ��ֵ*/
float GetFreq(void)
{
  unsigned short        dly = 0;
  unsigned int          i=400;//400hz��ʼ����
  
  /*����----------------*/
   DRIVER_EN_ON;//��������оƬ
    SetConnectToTran();
    delay_ms(20);
    while(i<8000)
    {
      TranFreq(i);
      i += 100;
    }
   DRIVER_EN_OFF;//�رշ���оƬ
    
    
    
  /*����Ƶ��-----------*/
    delay_ms(10);
    SetConnectToRec();
    delay_ms(10);
    //��ʼ������
    CaptureOn();
    //�ȴ��������,��ʱ�ж�Ϊ300ms
    while(FreqMeasureFinishFlag != 1)
    {
      delay_ms(1);
      dly++;
      if(dly > 300)
      {freq = 0;break;}
    }
    FreqMeasureFinishFlag = 0;
    //SetConnectToTran();
    return freq;
}


