/*****************************************************************
*Modules: gpio.c
*Dedcription: ��gpio�Ĳ���
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-2-22       ����ļ�
******************************************************************/
/*****************************includes****************************/
#include "msp430.h"
#include "gpio.h"
/******************************veraible**************************/




/*****************************************************************
*Function: GPIOInit
*Para:  port���˿ں�,  pin�����ź� , mode�����롢���������
*Return:��
*Dedcription: ��ʼ��GPIO�ڵ�״̬���������ģʽ
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-3-14      ��Ӻ���
******************************************************************/
void GPIOInit(PortType port, PinType pin ,PinModeType mode)
{
  switch(port)
  {
    case P1:
      if(mode == In ){  P1DIR &= ~pin;}
      if(mode == Out){  P1DIR |=  pin;}
      if(mode == Af ){  P1SEL |=  pin;}
      break;
    case P2:
      if(mode == In ){  P2DIR &= ~pin;}
      if(mode == Out){  P2DIR |=  pin;}
      if(mode == Af ){  P2SEL |=  pin;}
      break;
    case P3:
      if(mode == In ){  P3DIR &= ~pin;}
      if(mode == Out){  P3DIR |=  pin;}
      if(mode == Af ){  P3SEL |=  pin;}
      break;
    case P4:
      if(mode == In ){  P4DIR &= ~pin;}
      if(mode == Out){  P4DIR |=  pin;}
      if(mode == Af ){  P4SEL |=  pin;}
      break;
    case P5:
      if(mode == In ){  P5DIR &= ~pin;}
      if(mode == Out){  P5DIR |=  pin;}
      if(mode == Af ){  P5SEL |=  pin;}
      break;
    case P7:
      if(mode == In ){  P7DIR &= ~pin;}
      if(mode == Out){  P7DIR |=  pin;}
      if(mode == Af ){  P7SEL |=  pin;}
      break;
    case P8:
      if(mode == In ){  P8DIR &= ~pin;}
      if(mode == Out){  P8DIR |=  pin;}
      if(mode == Af ){  P8SEL |=  pin;}
      break;
    case P9:
      if(mode == In ){  P9DIR &= ~pin;}
      if(mode == Out){  P9DIR |=  pin;}
      if(mode == Af ){  P9SEL |=  pin;}
      break;
    case P10:
      if(mode == In ){  P10DIR &= ~pin;}
      if(mode == Out){  P10DIR |=  pin;}
      if(mode == Af ){  P10SEL |=  pin;}
      break;
    default:break;
  }
}
/*****************************************************************
*Function: GPIOOutPut
*Para:  port���˿ں�,  pin�����ź� , value�������ƽ��1-�ߵ�ƽ��0-�͵�ƽ��
*Return:��
*Dedcription: ����GPIO�������ƽ
*
*Log: <editor>          <date>          <log>
*       zhangq          2016-3-14      ��Ӻ���
******************************************************************/
void GPIOOutPut(PortType port, PinType pin ,unsigned char value)
{
  switch(port)
  {
    case P1:
      if(value == 1){P1OUT |=   pin;}
      if(value == 0){P1OUT &=  ~pin;}
      
    case P2:
      if(value == 1){P2OUT |=   pin;}
      if(value == 0){P2OUT &=  ~pin;}
    
    case P3:
      if(value == 1){P3OUT |=   pin;}
      if(value == 0){P3OUT &=  ~pin;}
      
    case P4:
      if(value == 1){P4OUT |=   pin;}
      if(value == 0){P4OUT &=  ~pin;}
      
    case P5:
      if(value == 1){P5OUT |=   pin;}
      if(value == 0){P5OUT &=  ~pin;}
      
      
    case P7:
      if(value == 1){P7OUT |=   pin;}
      if(value == 0){P7OUT &=  ~pin;}
      
    case P8:
      if(value == 1){P8OUT |=   pin;}
      if(value == 0){P8OUT &=  ~pin;}
    
    case P9:
      if(value == 1){P9OUT |=   pin;}
      if(value == 0){P9OUT &=  ~pin;}
      
    case P10:
      if(value == 1){P10OUT |=   pin;}
      if(value == 0){P10OUT &=  ~pin;}
    default:break;
  }
}


void LowPowerGPIO(void)
{

  P1DIR = 0xFF;                             // All P1.x outputs
    P1OUT = 0;                                // All P1.x reset
    P1REN = 0XFF;
    P2DIR = 0xFF;                             // All P2.x outputs
    P2OUT = 0;                                // All P2.x reset
    P2REN = 0XFF;
    P3DIR = 0xFF;                             // All P3.x outputs
    P3OUT = 0;                                // All P3.x reset
    P3REN = 0XFF;
    P4DIR = 0xFF;                             // All P4.x outputs
    P4OUT = 0;                                // All P4.x reset
    P4REN = 0XFF;
    P5DIR = 0xFF;                             // All P5.x outputs
    P5OUT = 0;                                // All P5.x reset
    P5REN = 0XFF;
    
    P7DIR = 0xFF;                             // All P5.x outputs
    P7OUT = 0;                                // All P5.x reset
    P7REN = 0XFF;
    
    P8DIR = 0xFF;                             // All P5.x outputs
    P8OUT = 0;                                // All P5.x reset
    P8REN = 0XFF;
    
    P9DIR = 0xFF;                             // All P5.x outputs
    P9OUT = 0;                                // All P5.x reset
    P9REN = 0XFF;
    
    P10DIR = 0xFF;                             // All P5.x outputs
    P10OUT = 0;                                // All P5.x reset
    P10REN = 0XFF;
    
    PADIR = 0xFFFF;                           // All PA.x outputs
    PAOUT = 0; 
    PAREN = 0xFFFF; 
    PBDIR = 0xFFFF;                           // All PB.x outputs
    PBOUT = 0; 
    PBREN = 0xFFFF; 
}