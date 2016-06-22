#include <msp430.h>
#include "test.h"
#include "cfg.h"
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
#include "rain.h"
#include "cmd.h"
#include "ramloop.h"
#include "key.h"
#include "ecc.h"
#include "dtu.h"
#include "rf.h"
#include <stdio.h>
#include <string.h>
#include "includes.h"


extern LoopRAMType Uart0loop;//串口0环形缓冲(关于此处为什么不用指针的思考：指针不分配内存，定义一个结构体则会使用内存)
extern long Uart0time;

void testdtu(void)
{
  char UpLoadData[300] = {'\0'};//将要上传的数据
  char PROTOCOL_UpLoadData[400] = {'\0'};//打包后带协议的将要上穿的数
  unsigned char detectTime = 0;//dtu断线时间

  
  

  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();//系统时间片
  PowerInit();
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_ON;
  LED(1); 
  while(1)
  {
/*------------------等待连接到DTU---------------------------*/
      LED(1);
      DtuInit();
      LED(0);
      delay_ms(5000);
      while(1)
      {
        if(DtuStatu() == 1)//连上服务器
          {
             LED(1);delay_ms(5000);break;
          }
        if(DtuStatu() == 0)//没有连上服务器
          {
            LED(0);
            delay_ms(1000);
            detectTime++;
            if(detectTime == 180)
            {
              detectTime = 0; 
              break;
            }
            delay_ms(1000);
          }
      }
      
      LED(1);
      delay_ms(5000);
      LED(0);
      
/*---------------------------上传数据----------------------*/
      if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 1)//加协议传输
        {
          packData(UpLoadData, getDataLength(UpLoadData,300), PROTOCOL_UpLoadData);
          UartStringLength(UART_0, PROTOCOL_UpLoadData, getDataLength(PROTOCOL_UpLoadData,400));
          memset(UpLoadData ,'\0',300);
          memset(PROTOCOL_UpLoadData ,'\0',400);
        }
      if(*(unsigned char*)(PROTOCOL_TYPE_ADDR+0) == 0)//不加协议传输
        {
         // printf("%s\r\n",UpLoadData);
          UartStringLength(UART_0, UpLoadData, getDataLength(UpLoadData,300));
          memset( UpLoadData , '\0', 300 );
        }
      delay_ms(500);      
  }
}

