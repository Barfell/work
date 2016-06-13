#include "msp430.h"
#include "spi.h"


void SpiInit(void)
{
  P3SEL    |= BIT3+BIT2+BIT1;                  // P1.3,2,1 option select
  P2DIR    |= BIT0;                            // P2.0 output direction (cs)
  UCB1CTL0 |= UCMST+UCSYNC+UCMSB;      // 3-pin, 8-bit SPI mstr, MSb 1st
  UCB1CTL1 |= UCSSEL_2;                     // SMCLK
  UCB1BR0   = 0x02;
  UCB1BR1   = 0;
  UCB1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  /*Polarity
  UCCKPH   UCCKPL
                 ______
  0      0  ____||    |______
  
            ____       ______
  0      1     ||_____|
  
                 ______ 
  1      0  ____|     ||_____
  
            _____      ______
  1      1      |_____||
  */
}

//关闭spi
void SpiToUart(void)
{

} 



unsigned char SpiReadByte(void)
{
  unsigned char dat;
  dat = SpiWriteReadByte(0xff);
  return dat;
}


unsigned char SpiWriteReadByte(unsigned char dat)
{
  unsigned int u8retry=0;	
  unsigned char	u8Ret;
  while ((UC1IFG & UCB1TXIFG) == 0)//等待到TXbuff没有数据的时候
  {
    u8retry++;
    if(u8retry>200)
      {
              u8Ret = 0;
              goto SPI_ReadWriteByte_exit;
      }
  }
  UCB1TXBUF = dat;
  u8retry=0;
  while((UC1IFG & UCB1RXIFG) == 0)//等待收到数据
  {
    u8retry++;
    if(u8retry>200)
      {
        u8Ret = 0;
        goto SPI_ReadWriteByte_exit;
      }
  }
  u8Ret = UCB1RXBUF;
SPI_ReadWriteByte_exit:	

  return u8Ret;
}



