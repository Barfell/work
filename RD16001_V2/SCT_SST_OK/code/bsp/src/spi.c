#include "msp430.h"
#include "spi.h"



#define SPI_MISO        P2IN & BIT1

#define SPI_MOSI_H      P2OUT |=  BIT2
#define SPI_MOSI_L      P2OUT &= ~BIT2

#define SPI_SCK_H       P2OUT |=  BIT3
#define SPI_SCK_L       P2OUT &= ~BIT3





void SpiInit(void)
{
  P2DIR |= BIT2 + BIT3;
  P2DIR &= ~BIT1;
}


unsigned char SpiReadByte(void)
{
  unsigned char dat;
  dat = SpiWriteReadByte(0xff);
  return dat;
}


unsigned char SpiWriteReadByte(unsigned char dat)
{
  unsigned char u8Ret = 0;
  unsigned char i=0;
  SPI_SCK_L;
  _NOP();
  
  for(i=0;i<8;i++)
  {
    SPI_SCK_L;
    if((dat<<i)&0x80)
    {
      SPI_MOSI_H;
    }
    else
    {
      SPI_MOSI_L;
    }
    SPI_SCK_H;
    _NOP();
    SPI_SCK_L;
  }
  
  i=0;
  for(i=0;i<8;i++)
  {
   SPI_SCK_L;
   if(SPI_MISO)
   {
      u8Ret |= 0x01;//1
   }
   else
   {
      u8Ret &= 0xfe;//0
   }
   u8Ret = u8Ret << 1;
   
   if(i==7)
   {
   _NOP();
   _NOP();
   _NOP();
    goto spi_exit;
   }
   _NOP();
   _NOP();
   _NOP();
   SPI_SCK_H;
   _NOP();
   _NOP();
   _NOP();
   
  }
  
spi_exit:  
  return u8Ret;
}



