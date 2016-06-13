#include "power.h"
#include "gpio.h"
#include "msp430.h"

void PowerInit(void)
{
  P9REN &= ~BIT5;
  P9DIR |=  BIT5;                             
  P9OUT &= ~BIT5;                            
  
  P4REN &= ~BIT2;
  P4REN &= ~BIT3;
  P4DIR |= BIT3+BIT2;                             
  P4OUT &= ~BIT2;                                
  P4OUT &= ~BIT3;
}


