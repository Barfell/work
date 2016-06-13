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


extern LoopRAMType Uart0loop;//����0���λ���(���ڴ˴�Ϊʲô����ָ���˼����ָ�벻�����ڴ棬����һ���ṹ�����ʹ���ڴ�)
extern long Uart0time;
unsigned char Dturetry = 0;

unsigned char DtuCMD(char *s)
{
  unsigned char cmd_flag   = 0;//�����Ƿ�ɹ�
  char recivedstr[180];//����ص�����
  
  long u32Count = 0;
  long s32Count = 0;
  long u32Tick  = 0;
  

  UartString(UART_0,s);//��������   
    
  u32Tick = GetTick();
  
  if(memcmp(s, "AT+SAVEPARAM", 12) == 0)
    { u32Count = 500;}
  else
    { u32Count = 100;}
    
  do
  {
    if(Uart0loop.LoopDatLength != 0)
    {
      s32Count = GetTick() - Uart0time;
      if(s32Count > 4)
      {
        LoopRAMReadLength(&Uart0loop, recivedstr, Uart0loop.LoopDatLength);//��ȡ�ظ�������
            
        if(strstr((char *)recivedstr, "OK") != 0)
          { cmd_flag =1; Dturetry = 0;break; }
        memset(recivedstr,'\0',180);
      }
    }
  }
  while( (GetTick() - u32Tick) < u32Count);
  delay_ms(500);
  
  if(cmd_flag == 0)
  {
    Dturetry++;
    if(Dturetry > 85)
    {
      //reset
    }
  }
    
    
  return cmd_flag;
  
}


void DtuInit(void)
{
  /*��ʼ��dtu��gpio*/
  P4REN  &= ~BIT6;//DCD P46
  P4DIR  &= ~BIT6;
  P4REN  &= ~BIT5;//ONOFF P45
  P4DIR  |=  BIT5;  
  P4OUT  &= ~BIT5;
  
  delay_ms(1000);
  LoopRAMInit(&Uart0loop);//�������λ���
  UARTInit(UART_0, UART_Clk_SMCLK, Baud_57600);//����dtu����
  _EINT();
  
  UART0_CH_DTU;//ѡ��DTU
  
  delay_ms(1000);
  DTU_ON;//����dtu
//  delay_ms(5000);
//  delay_ms(8000);
//  delay_ms(8000);
//  delay_ms(8000);
//  delay_ms(8000);
//  delay_ms(8000);
//  delay_ms(8000);
//  delay_ms(8000);
//  delay_ms(8000);
//  delay_ms(8000);

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


void Dtu(void)
{
  /*��ʼ��dtu��gpio*/

  LoopRAMInit(&Uart0loop);//�������λ���
  UARTInit(UART_0, UART_Clk_SMCLK, Baud_57600);//����dtu����
  
  UART0_CH_DTU;//ѡ��DTU
  delay_ms(1000);
  
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





