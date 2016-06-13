#include "kernel.h"
#include "Power.h"


/*初始化电源控制引脚的模式为输出模式*/
void PowerIoInit(void)
{
  P2DIR |= BIT0;
  P2DIR |= BIT1;
  P2DIR |= BIT2;
  P2DIR |= BIT3;
  P6DIR |= BIT3;
}

