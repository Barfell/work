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
char levelCmd[]={0x55,0xaa,0x00,0x0e,0x04,0x00,0x00};//水准仪的命令
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
  SysTickInit();//系统时间片
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
  SetRtc(0x2016,0x04,0x11,0x01,0x23,0x59,0x48);//第一次上电后设置的时间
  
  
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

0x55  0xaa  0  15  data[0]  0  0：水准测量——单次测量。

其中：
data[0]：平均次数。
测量结果取data[0]次平均值后输出，返回2个数据（依次为高度和距离，float型数据），共8个字节。
若无法测量，则返回错误码。错误码为5个字符的字符串（5个字节），共有以下几种状态：
（
"E1001",太暗；
"E1002",对比度不足；
"E1003",没对准,或标尺被遮挡；
"E1004",无效标尺或距离太远；
"E1005",标尺太近；
"E1006",标尺无法识别---有效的条码太少；
"E1007",标尺无法识别---有效的条码太少；
"E1008",标尺无法识别---有效的条码太少；
"E1009",标尺无法识别---有效的条码太少；
"E1010",标尺无法识别---有效的条码太少；
"E1011",标尺无法识别---标尺类型不对； 
"E1012",终止；
"E1013",太亮。
）
其中E1007……E1010，是研发人员使用，用于调试中分析故障原因。

*/
