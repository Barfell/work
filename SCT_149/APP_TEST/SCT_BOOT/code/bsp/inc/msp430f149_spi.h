#ifndef __MSP430F149_SPI_H_
#define __MSP430F149_SPI_H_


void SpiInit(void);
void SpiToUart(void);
unsigned char SpiReadByte(void);
unsigned char SpiWriteReadByte(unsigned char dat);



#endif

