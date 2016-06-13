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
      i += 200;
    }
    DRIVER_EN_OFF;//�رշ���оƬ
    
    
    
  /*����Ƶ��-----------*/
    SetConnectToRec();
    delay_ms(20);
    //��ʼ������
    CaptureOn();
    //�ȴ��������,��ʱ�ж�Ϊ300ms
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


