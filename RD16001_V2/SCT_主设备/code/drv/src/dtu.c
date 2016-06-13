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
#include "rtc.h"
#include "key.h"
#include "ramloop.h"
#include <stdio.h>

#define DTU_UART        UART_0
#define DTU_OFF        P4OUT|=BIT5
#define DTU_ON         P4OUT&=~BIT5


extern LoopRAMType Uart0loop;//串口0环形缓冲(关于此处为什么不用指针的思考：指针不分配内存，定义一个结构体则会使用内存)
extern long Uart0time;


unsigned char DtuCMD(char *s)
{
  unsigned char cmd_flag   = 0;//命令是否成功
  unsigned char retrytimes = 40;//尝试命令的次数
  char recivedstr[180];//命令返回的数据
  
  while(retrytimes--)
  {
    UartString(UART_0,s);//发送命令   
    
    
    if(memcmp(s, "AT+SAVEPARAM\r\n", 14) == 0)
      { delay_ms(5000);}
    delay_ms(300);
    
    
    
    if( (Uart0loop.LoopDatLength != 0) && ( (GetTick()-Uart0time) > 2) )//假如接收到DTU回复的数据   && ( (GetTick()-Uart0time) > 2)
    {
      LoopRAMReadLength(&Uart0loop, recivedstr, Uart0loop.LoopDatLength);//读取回复的数据
            
      if(strstr(recivedstr, "OK") != 0)
        { cmd_flag =1; retrytimes=40; delay_ms(500);break; }
      memset(recivedstr,'\0',180);
    }
    
    
    //没有接收到则等待500ms后再发送
    delay_ms(500);
  }
//  if(retrytimes == 0)//命令一直没有成功，重启
//    {/*重启*/}
  
  return cmd_flag;
  
}


void DtuInit(void)
{
  /*初始化dtu的gpio*/
  P4REN  &= ~BIT6;//DCD P46
  P4DIR  &= ~BIT6;
  P4REN  &= ~BIT5;//ONOFF P45
  P4DIR  |=  BIT5;  
  P4OUT  &= ~BIT5;
  
  DTU_OFF;
  delay_ms(1000);
  LoopRAMInit(&Uart0loop);//创建环形缓冲
  UARTInit(UART_0, UART_Clk_SMCLK, Baud_57600);//设置dtu串口
  _EINT();
  
  UART0_CH_DTU;//选择DTU
  
  delay_ms(1000);
  DTU_ON;//开启dtu
  delay_ms(5000);
  delay_ms(8000);
  delay_ms(8000);
  delay_ms(8000);
  delay_ms(8000);
  delay_ms(8000);
  delay_ms(8000);
  delay_ms(8000);

  if(DtuStatu() == 0)
    {
      while(DtuCMD("+++") == 0);
      delay_ms(1000);
      while(DtuCMD("AT+LOGIN=admin\r\n") == 0);
      delay_ms(1000);
      while(DtuCMD("AT+SETPARAM=RTUPMPL,1024\r\n") == 0);
      while(DtuCMD("AT+SETPARAM=OPPDIO,OFF\r\n") == 0);
      while(DtuCMD("AT+SETPARAM=RTUPDPTI,50\r\n") == 0);
      while(DtuCMD("AT+SETPARAM=CHPCT,TCP\r\n") == 0);
      while(DtuCMD("AT+SETPARAM=CHPDTUP,4003\r\n") == 0);
      while(DtuCMD("AT+SETPARAM=CHPDSCIP,183.233.190.96\r\n") == 0);
      while(DtuCMD("AT+SETPARAM=CHPDSCD,\r\n") == 0);
      while(DtuCMD("AT+SETPARAM=CHPDSCP,6254\r\n") == 0);
      while(DtuCMD("AT+SAVEPARAM\r\n") == 0);  
      UartString(UART_0,"AT+RESET\r\n");
      delay_ms(1000);
    }
}


unsigned char DtuStatu(void)
{
  unsigned char Statu = 0;
  if(P4IN & BIT6 )
    { Statu = 1; }
  else
    { Statu = 0; }
  return Statu;
}





