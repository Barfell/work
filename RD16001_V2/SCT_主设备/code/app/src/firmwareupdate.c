
#include "includes.h"

//将BOOT中断向量表拷贝至物理中断向量表中
void Vector_BOOT2HRAD(void)
{
  unsigned int i;
  FlashEreaseSector(HARDWARE_VECTOR_BUTTOM);
  delay_ms(20);
  FCTL1 = FWKEY + WRT;
  for(i=0;i<32;i++)
  {
    *(char *)(HARDWARE_VECTOR_BUTTOM + i) = *(char*)(BOOT_VECTOR_BUTTOM + i);
  }
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK; 
}

//跳转到升级程序（boot）
void FirmwareUpdate(void)
{
  //跳转到BOOT区域执行,跳转之前需要将BOOT固件的中断项链表放置到物理的VECTOR中
  Vector_BOOT2HRAD();           //准备好BOOT的VECTOR
  WDTCTL = 0x0000;              //复位跳转到BOOT  
}
