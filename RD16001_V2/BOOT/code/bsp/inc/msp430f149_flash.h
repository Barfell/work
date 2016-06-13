#ifndef _MSP430F149_FLASH_
#define _MSP430F149_FLASH_

void FlashInit(void);

void FlashEreaseSector(int addr);

void FlashWriteAddr(int addr, char *dat, int length);

#endif