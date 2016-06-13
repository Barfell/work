#include "kernel.h"
#include "Power.h"
#include "msp430.h"




void PowerInit(void)
{
  P1REN &= ~BIT0;
  P1DIR |=  BIT0;                             
  P1OUT &= ~BIT0;     //PWR_CN    
  
  P9REN &= ~BIT5;
  P9DIR |=  BIT5;                             
  P9OUT &= ~BIT5;     //COLL_PWR_CN    
  
  P4REN &= ~BIT4;
  P4DIR |=  BIT4;                             
  P4OUT &= ~BIT4;     //TRAN_PWR_CN    
  
}

