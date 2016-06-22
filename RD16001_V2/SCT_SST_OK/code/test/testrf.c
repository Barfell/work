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

#define RF_EN_1         P4OUT |= BIT3//�͹���ģʽ
#define RF_EN_0         P4OUT &= ~BIT3//��������

extern LoopRAMType Uart0loop;//����0���λ���(���ڴ˴�Ϊʲô����ָ���˼����ָ�벻�����ڴ棬����һ���ṹ�����ʹ���ڴ�)
extern long Uart0time;



//����
unsigned char cmd1[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X01,0X0E,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd2[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X02,0X0E,0X00,0X00,0X00,0X0D,0X0A};
//����ģʽ
unsigned char cmd3[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X03,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd4[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X04,0X02,0X01,0X00,0X00,0X0D,0X0A};
unsigned char cmd5[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X05,0X02,0X00,0X00,0X00,0X0D,0X0A};
//��ȡ��һ�����ݳ�ǿ
unsigned char cmd6[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X06,0X02,0X00,0X00,0X00,0X0D,0X0A};
//��������
unsigned char cmd9[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X09,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmdA[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X0A,0X02,0X00,0X00,0X00,0X0D,0X0A};
//�ز�Ƶ��
unsigned char cmdB[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X0B,0X03,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmdC[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X0C,0X03,0X00,0X00,0X00,0X0D,0X0A};
//��Ƶ����
unsigned char cmdD[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X0D,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmdE[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X0E,0X02,0X00,0X00,0X00,0X0D,0X0A};
//��Ƶ����
unsigned char cmdF[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X0F,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd10[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X10,0X02,0X00,0X00,0X00,0X0D,0X0A};
//����ģʽ
unsigned char cmd11[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X11,0X02,0X01,0X00,0X00,0X0D,0X0A};
unsigned char cmd12[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X12,0X02,0X00,0X00,0X00,0X0D,0X0A};
//�ͻ�ID
unsigned char cmd13[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X13,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd14[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X14,0X02,0X00,0X00,0X00,0X0D,0X0A};
//����ID
unsigned char cmd15[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X15,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd16[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X16,0X02,0X00,0X00,0X00,0X0D,0X0A};
//���书��
unsigned char cmd17[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X17,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd18[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X18,0X02,0X00,0X00,0X00,0X0D,0X0A};
//��������
unsigned char cmd19[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X19,0X02,0X00,0X00,0X00,0X0D,0X0A};
unsigned char cmd1A[13]={0XAF,0XAF,0X00,0X00,0XAF,0X80,0X1A,0X02,0X00,0X00,0X00,0X0D,0X0A};
//����ʱ��
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



/*���ģ������˽ڵ�ģʽ����������֮ǰ��Ҫ��EN�����ͣ�Ȼ���ٷ������ݡ�*/
/*������ģʽ�£�����ͽڵ�ģʽ��ģ�����ͨ�ţ��������ĺ�����ͨ��*/
/*����ģ��Ҫͨ�ŵ�ǰ���������ز�Ƶ�ʡ���Ƶ���ӡ���Ƶ�������� ID  ��Ҫ��ͬ�� */
/*ģ��ID ֻ���ڽڵ�ģʽ�²�������*/
/*���ʹ���ַ������ʱ��ÿ�����ݵ���󳤶Ȳ����Գ��� 200  ���ֽڡ� */
/*�����ͽڵ�  ����ʱ��ͺ��������Ҫ���ó�һ������ͨ��*/
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
      P4REN &= ~BIT3;//rf�͹���
      P4DIR |= BIT3;
      RF_EN_1;
      RainInit();//�����ж�
      PowerInit();
      PWR_OFF;
      COLL_PWR_OFF;
      TRAN_PWR_ON;
      ClkOff();   //����͹���֮ǰҪ��ʱ�����ú�
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