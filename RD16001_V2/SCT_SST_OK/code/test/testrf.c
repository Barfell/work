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

#define RF_EN_1         P4OUT |= BIT3//低功耗模式
#define RF_EN_0         P4OUT &= ~BIT3//发送数据

extern LoopRAMType Uart0loop;//串口0环形缓冲(关于此处为什么不用指针的思考：指针不分配内存，定义一个结构体则会使用内存)
extern long Uart0time;



//参数
unsigned char cmd1[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X01,0X0E,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd2[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X02,0X0E,0X00,0X00,0X00,0X0D,0X0A};
//进入模式
unsigned char cmd3[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X03,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd4[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X04,0X02,0X01,0X00,0X00,0X0D,0X0A};
unsigned char cmd5[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X05,0X02,0X00,0X00,0X00,0X0D,0X0A};
//读取上一包数据场强
unsigned char cmd6[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X06,0X02,0X00,0X00,0X00,0X0D,0X0A};
//串口速率
unsigned char cmd9[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X09,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmdA[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X0A,0X02,0X00,0X00,0X00,0X0D,0X0A};
//载波频率
unsigned char cmdB[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X0B,0X03,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmdC[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X0C,0X03,0X00,0X00,0X00,0X0D,0X0A};
//扩频因子
unsigned char cmdD[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X0D,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmdE[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X0E,0X02,0X00,0X00,0X00,0X0D,0X0A};
//扩频带宽
unsigned char cmdF[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X0F,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd10[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X10,0X02,0X00,0X00,0X00,0X0D,0X0A};
//工作模式
unsigned char cmd11[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X11,0X02,0X01,0X00,0X00,0X0D,0X0A};
unsigned char cmd12[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X12,0X02,0X00,0X00,0X00,0X0D,0X0A};
//客户ID
unsigned char cmd13[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X13,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd14[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X14,0X02,0X00,0X00,0X00,0X0D,0X0A};
//网络ID
unsigned char cmd15[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X15,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd16[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X16,0X02,0X00,0X00,0X00,0X0D,0X0A};
//发射功率
unsigned char cmd17[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X17,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd18[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X18,0X02,0X00,0X00,0X00,0X0D,0X0A};
//呼吸周期
unsigned char cmd19[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X19,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd1A[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X1A,0X02,0X00,0X00,0X00,0X0D,0X0A};
//呼吸时间
unsigned char cmd1B[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X1B,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd1C[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X1C,0X02,0X00,0X00,0X00,0X0D,0X0A};


unsigned char rf_ecc(unsigned char *buf, unsigned char length)
{
  unsigned char i   = 0;
  unsigned int  sum = 0;
  unsigned char ecc = 0;
  
  for(i =0;i<length;i++)
  {
    sum += *(buf+i);
  }
  
  ecc = sum%256;
  return ecc;
}

void cmd_init(void)
{
  cmd1[10] = rf_ecc(cmd1,10);
  cmd2[10] = rf_ecc(cmd2,10);
  cmd3[10] = rf_ecc(cmd3,10);
  cmd4[10] = rf_ecc(cmd4,10);
  cmd5[10] = rf_ecc(cmd5,10);
  cmd6[10] = rf_ecc(cmd6,10);

  cmd9[10] = rf_ecc(cmd9,10);
  cmdA[10] = rf_ecc(cmd10,10);
  cmdB[10] = rf_ecc(cmd11,10);
  cmdC[10] = rf_ecc(cmd12,10);
  cmdD[10] = rf_ecc(cmd13,10);
  cmdE[10] = rf_ecc(cmd9,10);
  cmdF[10] = rf_ecc(cmd10,10);
  cmd10[10] = rf_ecc(cmd11,10);
  cmd11[10] = rf_ecc(cmd12,10);
  cmd12[10] = rf_ecc(cmd13,10);
  cmd13[10] = rf_ecc(cmd9,10);
  cmd14[10] = rf_ecc(cmd10,10);
  cmd15[10] = rf_ecc(cmd11,10);
  cmd16[10] = rf_ecc(cmd12,10);
  cmd17[10] = rf_ecc(cmd13,10);
  cmd18[10] = rf_ecc(cmd9,10);
  cmd19[10] = rf_ecc(cmd10,10);
  cmd1A[10] = rf_ecc(cmd11,10);
  cmd1B[10] = rf_ecc(cmd12,10);
  cmd1C[10] = rf_ecc(cmd13,10);
}



/*如果模块进入了节点模式，则发送数据之前需要将EN脚拉低，然后再发送数据。*/
/*在中心模式下，必须和节点模式的模块进行通信，不能中心和中心通信*/
/*两个模块要通信的前提条件是载波频率、扩频因子、扩频带宽、网络 ID  都要相同。 */
/*模块ID 只有在节点模式下才起作用*/
/*发送带地址的数据时候每包数据的最大长度不可以超过 200  个字节。 */
/*主机和节点  呼吸时间和呼吸间隔需要设置成一样才能通信*/
void testrf(void)
{
  float f,v;
  
  WDTCTL = WDTPW + WDTHOLD;
  ClkInit();
  SysTickInit();
  PowerInit();
  PWR_ON;
  COLL_PWR_ON;
  TRAN_PWR_ON;
  
  
  P4REN &= ~BIT3;//en RF
  P4DIR |= BIT3;
  RF_EN_0;
  
  
  RFInit();
  printf("rf test\r\n");
  

  LED(1);
  delay_ms(1000);
  LED(0);
  
  
 while(1)
 {
      LowPowerGPIO();
      P4REN &= ~BIT3;//rf低功耗
      P4DIR |= BIT3;
      RF_EN_1;
      RainInit();//雨量中断
      PowerInit();
      PWR_OFF;
      COLL_PWR_OFF;
      TRAN_PWR_ON;
      ClkOff();   //进入低功耗之前要把时钟设置好
      __bis_SR_register(LPM3_bits + GIE);
      
      
      
      
      
      WDTCTL = WDTPW + WDTHOLD;
      delay_ms(500);
      ClkInit();
      delay_ms(500);
      PowerInit();
      PWR_ON;
      COLL_PWR_ON;
      TRAN_PWR_ON;
      
      
      P4REN &= ~BIT3;//en RF
      P4DIR |= BIT3;
      RF_EN_0;
      
      RFInit();
      printf("XXXXXXXXXX\r\n");
      delay_ms(1000);
      
      FreqInit();
      SDInit();
      f = GetFreq();
      v = Get_INNER_Voltage();
      printf("freq value is:%f,inner votlage is:%f\r\n",f,v);
   

      LED(1);
      delay_ms(1000);
      LED(0);
 }
  
 
} 