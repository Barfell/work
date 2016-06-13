#include "msp430f149_spi.h"
#include "i430type.h"
#include "kernel.h"

void SpiInit(void)
{
  P3SEL = 0x0E;                             // Setup P3 for SPI mode p31 p32 p33
  
  P3DIR |= 0x01;                            // P3.0 for slave cs
  P3OUT &= ~0x01;
  
  ME1 |= USPIE0;                             // SPI Module enable
  U0CTL = CHAR + SYNC + MM + SWRST;         // 8-bit, SPI, Master
  
  /*Polarity
  CKPH   CKPL
                 ______
  0      0  ____||    |______
  
            ____       ______
  0      1     ||_____|
  
                 ______ 
  1      0  ____|     ||_____
  
            _____      ______
  1      1      |_____||
  */
  U0TCTL = CKPL +  SSEL1 + STC;              // Polarity, SMCLK, 3-wire

  U0BR0 = 0x002;                            // SPICLK = SMCLK/2
  U0BR1 = 0x000;                            
  U0MCTL = 0x000;                           // 使用spi模式的时候必须要置为0x00
  
  
  U0CTL &= ~SWRST;                          // SPI enable 软件复位被禁用。 USART复位释放操作。
  //IE1 |= URXIE0;                            // Recieve interrupt enable
  //__enable_interrupt();                     // Enable interrupts

} 

//关闭spi
void SpiToUart(void)
{
  ME1 &= ~USPIE0;  
  U0CTL &= ~(CHAR + SYNC + MM + SWRST);  
  
  U0TCTL &= ~(CKPL  + SSEL1 + STC);              
  U0BR0 &= ~0x002;                           
  U0BR1 &= ~0x000;                            
  U0MCTL &= ~0x000;
  U0CTL |= SWRST;  
} 



unsigned char SpiReadByte(void)
{
  unsigned char dat;
  dat = SpiWriteReadByte(0xff);
  return dat;
}


unsigned char SpiWriteReadByte(unsigned char dat)
{
	u8 u8retry=0;	
	u8	u8Ret;
  while ((IFG1 & UTXIFG0) == 0)
  {
	  u8retry++;
		if(u8retry>200)
		{
			u8Ret = 0;
			goto SPI_ReadWriteByte_exit;
		}
  }
  TXBUF0 = dat;
  u8retry=0;
  while ((IFG1 & URXIFG0) == 0)
  {
	  u8retry++;
		if(u8retry>200)
		{
			u8Ret = 0;
			goto SPI_ReadWriteByte_exit;
		}
  }
  u8Ret = RXBUF0;
SPI_ReadWriteByte_exit:	

  return u8Ret;
}






//
//
//
///*******************************SPI SOFT**************************************/
//#define SPI_CS_High 	P3OUT |= BIT0
//#define SPI_CS_Low 		P3OUT &= ~BIT0
//
//#define SPI_SCLK_High	P3OUT |= BIT3
//#define SPI_SCLK_Low	P3OUT &= ~BIT3
//
//#define SPI_DATA_High	P3OUT |= BIT2
//#define SPI_DATA_low	P3OUT &= ~BIT2
//
//#define SPI_DATA_OUTMODE P3DIR |= BIT2
//#define SPI_DATA_INMODE	P3DIR &= ~BIT2
//#define SPI_DATA_IN 	P3IN & 0x04
//
//double g_dResSoft = 3.2;
//void SPISoft_Init(void)
//{
//	P3DIR |= BIT0 + BIT3;
//
//	SPI_CS_Low;
//	SPI_SCLK_Low;
//	delay_us_soft(10);
//}
//
//void SPISoft_WriteByte(unsigned char data)
//{
//	unsigned char i;
//	SPI_DATA_OUTMODE;
//	SPI_SCLK_Low;
//	delay_us_soft(1);
//	for(i=0; i<8; i++)
//	{
//		SPI_SCLK_Low;
//		if(0x80&data)
//		{
//			SPI_DATA_High;
//		}
//		else
//		{
//			SPI_DATA_low;
//		}
//		delay_us_soft(2);
//		SPI_SCLK_High;
//		delay_us_soft(2);
//		data <<= 1;
//	}
//	SPI_SCLK_Low;
//}
//
//unsigned char SPISoft_ReadByte(void)
//{
//	unsigned char i,temp = 0;
//	SPI_DATA_INMODE;
//	SPI_SCLK_Low;
//	delay_us_soft(1);
//	for(i=0; i<8; i++)
//	{
//		temp <<= 1;
//		SPI_SCLK_High;
//		delay_us_soft(2);
//		if(SPI_DATA_IN)
//		{
//			temp |= 0x01;
//		}
//		SPI_SCLK_Low;
//		delay_us_soft(1);
//	}
//	SPI_SCLK_Low;
//	delay_us_soft(1);
//	return temp;
//}
//
//unsigned char SPISoft_WriteReadByte(unsigned char data)
//{
//	return SPISoft_ReadByte();
//	//delay_us_soft(3);
//}
//
//
//
//unsigned char SPISoft_TEST_EOC(void)
//{
//	delay_ms(300);
//	return SPISoft_WriteReadByte(0xff);
//}
//
//double SPISoft_GetRES(void)
//{
//	unsigned char u8charresbuf[4] = {0};
//	unsigned char EOC = 0;
//	unsigned long u32resbuf = 0;
//	double convertionresult = 0;
//	double current = 0;
//	double RES = 0;
//	double ch1 = 0;
//	double ch0 = 0;
//	unsigned char i = 0;
//	
//	for(i = 0;i < 2;i++)
//	{
//		EOC = SPILTC_TEST_EOC();
//		if(  (EOC & 0x80) == 0  )//转换完毕
//		{
//				u8charresbuf[0] = EOC;
//				u8charresbuf[1] = SPISoft_ReadByte();
//				u8charresbuf[2] = SPISoft_ReadByte();
//				u8charresbuf[3] = SPISoft_ReadByte();
//				u32resbuf = (((unsigned long)u8charresbuf[0]<<24)+((unsigned long)u8charresbuf[1]<<16)+((unsigned long)u8charresbuf[2]<<8)+((unsigned long)u8charresbuf[3]<<0));
//				u32resbuf = u32resbuf&0x0FFFFFF0; 
//				u32resbuf = u32resbuf >>4;
//				printf("u8buf %d,%d,%d,%d\r\n",u8charresbuf[0],u8charresbuf[1],u8charresbuf[2],u8charresbuf[3]);
//				printf("LTC2402 zhi u32 is %ld\r\n",u32resbuf);
//				convertionresult = (double)(((u32resbuf)/16777216.0)*4.99);
//				if(  EOC & 0x40  )
//				{
//					ch1 = convertionresult;
//					ch1=0;
//				}
//				else
//				{
//					ch0 = convertionresult;
//					//ch0 = 0;
//					printf("0:eoc is ok and ch0 is %f\r\n\r\n", ch0 );
//				}
//				u8charresbuf[0] = 0;
//				u8charresbuf[1] = 0;
//				u8charresbuf[2] = 0;
//				u8charresbuf[3] = 0;
//		}
//	}
//    if(ch0 > ch1)
//	{
//		RES = ch0 - ch1;
//	}
//    else
//	{
//		RES = ch1 - ch0;
//	}
//    current = (4.99 - RES)/19600.0;
//    RES = RES/current;
//	g_dResSoft = RES;
//    return RES;    
//}
//
