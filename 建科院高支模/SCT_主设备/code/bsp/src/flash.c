#include "msp430.h"
#include "flash.h"

/*--------FLASH memory organization-------------------------
*MAIN FLASH  INTERRUPT VECTOR   :  0XFFFF       -       0XFFC0  
*MAIN FLASH  CODE MEMORT        :  0X01FFFF     -       0X3100  
*RAM                            :  0X30FF       -       0X1100
*/
//һ��Segment��256B
void FlashInit(void)
{
  FCTL2 = FWKEY + FSSEL0 + FN0;             // MCLK/2 for Flash Timing Generator
}

//void FlashLock(void)
//{
//  FCTL3 = FWKEY;                            // Clear Lock bit
//}
//
//void FlashUnLock(void)
//{
//  FCTL1 = FWKEY;                            // Clear WRT bit
//  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
//}
/*������ַ���ڵ�Segment*/
void FlashEreaseSector(unsigned long addr)
{
  /*������ַ���ڶ�*/
  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
  FCTL3 = FWKEY;                            // Clear Lock bit
  *(char *)addr = 0;                           // Dummy write to erase Flash segment
  
}


void FlashWriteAddr(unsigned long addr, char *dat, int length)
{
  int i;
  /*ĳ��ַд��һ�����ȵ����� byteΪ��λ*/
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation
  for (i=0; i<length; i++)
  {
    *(char *)addr++ = *dat++;                   // Write value to flash
  }
  
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

void FlashWriteByte(unsigned long addr, char dat)
{
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation
  *(char *)addr = dat;                   // Write value to flash
}