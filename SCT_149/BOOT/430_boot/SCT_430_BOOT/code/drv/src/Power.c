#include "kernel.h"
#include "Power.h"


/*��ʼ����Դ�������ŵ�ģʽΪ���ģʽ*/
void PowerIoInit(void)
{
  P2DIR |= BIT0;
  P2DIR |= BIT1;
  P2DIR |= BIT2;
  P2DIR |= BIT3;
  P6DIR |= BIT3;
}

