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


unsigned char DtuCMD(char *s)
{
  unsigned char cmd_flag   = 0;//�����Ƿ�ɹ�
  unsigned char retrytimes = 80;//��������Ĵ���
  char recivedstr[80];//����ص�����
  while(retrytimes--)
  {
    UartString(UART_0,s);//��������    
    if(memcmp(s, "AT+SAVEPARAM\r\n", 14) == 0)
      { delay_ms(5000);}
    delay_ms(300);
    
    if( (Uart0loop.LoopDatLength != 0) && ( (GetTick()-Uart0time) > 2))//������յ�DTU�ظ�������
    {
      LoopRAMReadLength(&Uart0loop, recivedstr, Uart0loop.LoopDatLength);//��ȡ�ظ�������
      if(strstr(recivedstr, "OK") != 0)
        { cmd_flag =1; retrytimes=0; delay_ms(500);break; }
      memset(recivedstr,'\0',80);
    }
    //û�н��յ���ȴ�500ms���ٷ���
    delay_ms(500);
  }
  if(retrytimes == 0)//����һֱû�гɹ�������
    {/*����*/}
  return cmd_flag;
}



void DtuInit(void)
{
  /*��ʼ��dtu��gpio*/
  /*��������*/
  P4REN  &= ~BIT6;//DCD P46
  P4DIR  &= ~BIT6;
  P4REN  &= ~BIT5;//ONOFF P45
  P4DIR  |=  BIT5;  
  P4OUT  &= ~BIT5;
  DTU_OFF;
  delay_ms(1000);
  LoopRAMInit(&Uart0loop);//�������λ���
  UARTInit(UART_0, UART_Clk_SMCLK, Baud_57600);//����dtu����
  _EINT();
  delay_ms(1000);
  DTU_ON;//����dtu
  while(DtuCMD("+++") == 0);
  delay_ms(500);
  while(DtuCMD("AT+LOGIN=admin\r\n") == 0);
  delay_ms(500);
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


unsigned char DtuStatu(void)
{
  unsigned char Statu = 0;
  if(P4IN & BIT6)
    {Statu = 1;}
  else
    {Statu = 0;}
  return Statu;
}




