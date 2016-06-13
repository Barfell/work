#ifndef _SPI_H_
#define _SPI_H_


void SpiInit(void);
void SpiToUart(void);
unsigned char SpiReadByte(void);
unsigned char SpiWriteReadByte(unsigned char dat);



#endif

