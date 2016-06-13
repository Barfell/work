
#include "includes.h"             //��������˰��ӵĸ�������,�Լ�һЩϵͳ��С������������ʱCRCУ���....

//��BOOT�ж����������������ж���������
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

//��ת����������boot��
void FirmwareUpdate(void)
{
  //��ת��BOOT����ִ��,��ת֮ǰ��Ҫ��BOOT�̼����ж���������õ������VECTOR��
  Vector_BOOT2HRAD();           //׼����BOOT��VECTOR
  WDTCTL = 0x0000;              //��λ��ת��BOOT  
}
