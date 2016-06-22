/**************************************************
*
*�����Ҵ��������г�ʼ������������ȡ�ȵ�
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


/*ʹ��������Ҫ�ĳ�ʼ��*/
void FreqInit(void)
{
  /*---------------����ѡ��--------*/
  P5REN &=  ~BIT1;
  P5DIR |=   BIT1;
  P5OUT &=   ~BIT1;//VW 485      SW-0(FREQ)

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

    while(i<6000)
    {
      TranFreq(i);
      i += 100;
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

//��ȡͨ��ch���������ݣ����浽dat�У��������ݳ���
unsigned char Get_Freq_CH(unsigned char ch, char *dat)
{
  char retData[100] ={'\0'};
  char timevw[50]= {'\0'};//��ȡVW���������ݵ�ʱ���
  unsigned char len = 0;
  unsigned char measureVWTime = 0;//���Խ��в����Ĵ���
  float measureFreq = 0.0;//VW�������
  float vol = 0.0;//��Դ��ѹ
  float VWtemp = 0.0;

  
  CH_Select(ch);
  //��ȡ��Դ��ѹ
  SDInit();
  delay_ms(500);
  while(vol == 0)
    { vol = GetSD16Voltage(4); }
  vol = vol*776.0 /26.1;
  
  //�������¶�
  VWtemp = Get_VW_Voltage();//��ѹ
  VWtemp = 9950/VWtemp - 21290;//����
  VWtemp = GetNTCTemperature(VWtemp);//�¶�
  
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

