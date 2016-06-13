#include "msp430.h"
#include <stdio.h>
#include <string.h>
#include "clk.h"
#include "rain.h"
#include "rtc.h"
#include "cfg.h"
#include "flash.h"
#include "kernel.h"
void RainInit(void)
{
  P2IFG  = 0;//CLEAR FLAGS
  P2REN  &= ~BIT7;
  P2DIR  &= ~BIT7;
  P2SEL  &= ~BIT7;
  P2IES  &= ~BIT7;//L---H
  P2IFG  = 0;//CLEAR FLAGS
  P2IE  |=  BIT7;//ENABLE
  P2IFG  = 0;//CLEAR FLAGS
  _EINT();//GLOABLE INTERRUPT
}

//2016-04-26-19:24:55|(20byte)
void StoreRain(void)
{
  char rainTime[25];
  unsigned int addr = 0;
  addr = GetRainNum();
  GetRtc(rainTime);
  WriteRainToFlash(addr,rainTime);
}



void WriteRainToFlash(unsigned long addr, char* rain)
{
  unsigned int i;
  unsigned int Addr_extra = 0;//д��㵽����SEG��ʼλ�õĴ�С
  Addr_extra = addr%256;//д��㵽����SEG��ʼλ�õĴ�С
  
  /*���ݱ���SEG*/
  FlashInit();
  FlashEreaseSector(RAIN_TEMP_ADDR);
  for(i=0;i<256;i++)
  {
    FlashWriteByte(RAIN_TEMP_ADDR + i, (*(unsigned char *)(addr - Addr_extra + i)) );
  }  
  /*д�뱸�ݵ�SEG������������RAIN���ݣ����RAIN���ݳ����˱�SEG���������һ��SEG����������*/
  FlashEreaseSector(addr);
  for(i=0;i<Addr_extra;i++)
  {
    FlashWriteByte(addr - Addr_extra + i, (*(unsigned char *)(RAIN_TEMP_ADDR + i)) );
  }

  if( (256 - Addr_extra) < 20 )//�����˱���SEG
    {
      FlashEreaseSector(addr + 256);
      FlashWriteAddr(addr, rain, strlen(rain));
    }
  else if( (256 - Addr_extra) > 20 )//û�г����˱���SEG
    {
      FlashWriteAddr(addr, rain, strlen(rain));
    }
  
  
  
  /*����������¼���ַ �� RAIN_NUM_ADDR */
  FlashInit();
  FlashEreaseSector(RAIN_NUM_ADDR);
  FlashWriteByte(RAIN_NUM_ADDR, (unsigned char)( (addr+20)>>8 ) );
  FlashWriteByte(RAIN_NUM_ADDR+1, (unsigned char)( (addr+20)  ) );
}


unsigned int GetRainNum(void)
{
  unsigned int  rainNum    = 0;//��������
  unsigned char rainNum_H  = 0;
  unsigned char rainNum_L  = 0;

  rainNum_H = *(unsigned char *)(RAIN_NUM_ADDR);
  rainNum_L = *(unsigned char *)(RAIN_NUM_ADDR+1);
  rainNum = ((unsigned int)rainNum_H<<8 & 0xff00)|((unsigned int)rainNum_L & 0x00ff);
  
  return rainNum;
}

#pragma vector=PORT2_VECTOR
__interrupt void gpio1_int(void)
{
//  char time[25];
//  
//  LPM3_EXIT;//�˳�����
//  WDTCTL = WDTPW + WDTHOLD;
//  ClkInit();  //�Ƴ��͹��ĺ�����ʱ����������һ��
//  
//  
//  _DINT();
//  if( P2IFG  != 0)
//  {
//    P2IFG = 0;
//    GetRtc(time);
//    WriteRainToFlash(GetRainNum(), time);
//    
//    //printf("1234567890\r\n");
//    //delay_ms(1000);
//    //��¼һ������
//  }
//  delay_ms(300);
//  _EINT();
//  
//  
//  ClkOff();   //����͹���
//  __bis_SR_register(LPM3_bits + GIE);
  
  P2IFG = 0;
  LPM3_EXIT;//�˳�����
  
}
