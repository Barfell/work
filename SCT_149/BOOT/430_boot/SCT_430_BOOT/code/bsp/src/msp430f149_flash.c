#include "msp430f149_flash.h"
#include "i430type.h"
#include "msp430f149_wdt.h"

void FlashInit(void)
{
  FCTL2 = FWKEY + FSSEL0 + FN0;             // MCLK/2 for Flash Timing Generator
}

void FlashEreaseSector(int addr)
{
  /*擦除地址所在段*/
  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
  FCTL3 = FWKEY;                            // Clear Lock bit
  *(char *)addr = 0;                           // Dummy write to erase Flash segment
  
}


void FlashWriteAddr(int addr, char *dat, int length)
{
  int i;
  /*某地址写入一定长度的数据 byte为单位*/
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation
  for (i=0; i<length; i++)
  {
    *(char *)addr++ = *dat++;                   // Write value to flash
  }
  
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

