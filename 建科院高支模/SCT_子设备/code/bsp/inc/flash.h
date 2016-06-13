#ifndef _MSP430F149_FLASH_
#define _MSP430F149_FLASH_

void FlashInit(void);

void FlashEreaseSector(unsigned long addr);

void FlashWriteAddr(unsigned long addr, char *dat, int length);

void FlashWriteByte(unsigned long addr, char dat);
#endif