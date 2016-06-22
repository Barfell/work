/**************************************************
*
*对485传感器的操作，初始化，测量，获取等等
*-----针对大铁自家的传感器模块
***************************************************
*/
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
#include "cfg.h"
#include "key.h"
#include "s485.h"
#include "ecc.h"
#include "ramloop.h"
#include <stdio.h>


extern LoopRAMType Uart1loop;//串口0环形缓冲(关于此处为什么不用指针的思考：指针不分配内存，定义一个结构体则会使用内存)
extern long Uart1time;

void Init485(void)
{
  /*---------------功能选择--------*/
  P5REN &=  ~BIT1;
  P5DIR |=   BIT1;
  P5OUT |=   BIT1;//VW 485     SW-1(485)
  /*--------------串口-------------*/
  LoopRAMInit(&Uart1loop);
  UARTInit(UART_1, UART_Clk_SMCLK, Baud_9600);
  _EINT();
  delay_ms(1000); 
}

//device命令，dat485返回数据
unsigned char Get485(char *device, char *dat485)
{
    unsigned int retry=0;
    unsigned char ret = 0;
    char datTemp[200] = {'\0'};
    UartString(UART_1,device);
    //printf("UART_1:%s\r\n",device);
    delay_ms(5000);
    while(1)
    {
      if( (Uart1loop.LoopDatLength != 0) && ( (GetTick()- Uart1time) > 5))//假如接收到DTU回复的数据
        {
          LoopRAMReadLength(&Uart1loop, datTemp, Uart1loop.LoopDatLength);//读取回复的数据
          memcpy(dat485,datTemp,getDataLength(datTemp,200) -2);
          memset(datTemp,0,200);
          delay_ms(100);
          ret = 1;
          break;
        }
      else
        {
          retry++;
          delay_ms(10);
          if(retry == 500)
          {retry = 0;ret = 0;break;}
        }
    }
    return ret;//返回测量的结果状态，成功或者失败
}



//获取通道ch的485数据，保存到dat中，返回数据长度
unsigned char Get_485_CH(unsigned char ch, char *cmd, char *dat)
{
  char retData[100] ={'\0'};
  char time485[50] = {'\0'};//获取485传感器数据的时间戳
  unsigned char len = 0;
  unsigned char measure485Times = 0;//测量尝试次数
  char value485[100] = {'\0'};//485传感器的测量数据
  char cmd485[50] = {'\0'};//485传感器的命令
  float vol = 0.0;
  
  
  strcat(cmd485,cmd);
  
  
  CH_Select(ch);
  //获取电源电压
  SDInit();
  delay_ms(1000);
  while(vol == 0)
    {vol = GetSD16Voltage(4);}
  vol = vol*776.0 /26.1;
  SDOff();
  //获取传感器数据
  while(1)
  {
    if( Get485(cmd485,value485) == 1 )
      {
        GetRtc(time485);
        sprintf(retData,"#%s\r\n#votagle:%f\r\n#%s\r\n#CH1:%s\r\n",MACHINE_ID, vol, time485, value485);
        len = sizeof(retData);
        memcpy(dat,retData,len);
        memset(time485,'\0',50);
        memset(value485,'\0',100);
        delay_ms(3000);
        break;
      }
    else
     {
        measure485Times++;
        if(measure485Times == 2)
          {
            GetRtc(time485);
            sprintf(retData,"#%s\r\n#votagle:%f\r\n#%s\r\n#CH1:%s\r\n",MACHINE_ID, vol, time485, value485);
            len = sizeof(retData);
            memcpy(dat,retData,len);
            delay_ms(3000);
            measure485Times = 0;
            memset(time485,'\0',50);
            memset(value485,'\0',100);
            break;
          }
        memset(time485,'\0',50);
        delay_ms(5000);
     }
  }
  return len;
}