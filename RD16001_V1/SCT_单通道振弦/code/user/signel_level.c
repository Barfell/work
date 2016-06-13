#include <msp430.h>
#include "test.h"
#include "gpio.h"
#include "freq.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
#include "power.h"
#include "flash.h"
#include "rtc.h"
#include "s485.h"
#include "level.h"
#include "cmd.h"
#include "ramloop.h"
#include "key.h"
#include "dtu.h"
#include <stdio.h>



char sensorLevel[100];
char time[50];
char levelCmd[]={0x55,0xaa,0x00,0x0e,0x04,0x00,0x00};//ˮ׼�ǵ�����
unsigned int detectTime = 0;
unsigned char measureTime = 0;

void levelTask(void)
{
  while(1)
      {
        if(DtuStatu() == 1)
        {
            while(1)
            {
              if(GetLevel(levelCmd,sensorLevel) == 1)
                  {
                    GetRtc(time);
                    printf("%s\r\n",time);
                    printf("level data: %s\r\n",sensorLevel);
                    memset(time,'\0',50);
                    memset(sensorLevel,'\0',100);
                    break;
                  }
              else
                  {
                    measureTime++;
                    if(measureTime == 5)
                    {
                      measureTime = 0;
                      memset(time,'\0',50);
                      memset(sensorLevel,'\0',100);
                      break;
                    }
                    printf("measure...\r\n");
                  }
            }
          break;
        }
        else
        {
          detectTime++;
          if(detectTime == 30)
          {detectTime = 0; printf("disconnect\r\n");break;}
          delay_ms(1000);
          printf("offline...\r\n");
        }
      }
}

void signel_level(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();//ϵͳʱ��Ƭ
  PowerInit();
  PWR_ON;
  CORE_PWR_ON;
  COLL_PWR_ON;
  P1DIR |= BIT1;
  P1OUT &= ~BIT1;
  
  _EINT();
  delay_ms(1000);
  DtuInit();
  InitLevel();
  SetRtc(0x2016,0x04,0x11,0x01,0x23,0x59,0x48);//��һ���ϵ�����õ�ʱ��
  
  
  while(1)
  {
      cmdTask();
      
      levelTask();
      
      LowPowerEntry();
      delay_ms(1000);
      DtuInit();
      InitLevel();
  }
  
}


/*

0x55  0xaa  0  15  data[0]  0  0��ˮ׼�����������β�����

���У�
data[0]��ƽ��������
�������ȡdata[0]��ƽ��ֵ�����������2�����ݣ�����Ϊ�߶Ⱥ;��룬float�����ݣ�����8���ֽڡ�
���޷��������򷵻ش����롣������Ϊ5���ַ����ַ�����5���ֽڣ����������¼���״̬��
��
"E1001",̫����
"E1002",�ԱȶȲ��㣻
"E1003",û��׼,���߱��ڵ���
"E1004",��Ч��߻����̫Զ��
"E1005",���̫����
"E1006",����޷�ʶ��---��Ч������̫�٣�
"E1007",����޷�ʶ��---��Ч������̫�٣�
"E1008",����޷�ʶ��---��Ч������̫�٣�
"E1009",����޷�ʶ��---��Ч������̫�٣�
"E1010",����޷�ʶ��---��Ч������̫�٣�
"E1011",����޷�ʶ��---������Ͳ��ԣ� 
"E1012",��ֹ��
"E1013",̫����
��
����E1007����E1010�����з���Աʹ�ã����ڵ����з�������ԭ��

*/
