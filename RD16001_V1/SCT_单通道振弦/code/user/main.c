#include <msp430.h>
#include "test.h"
#include "includes.h"


int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  while(1)
  {
    signel_Task();
    //testecc();
    //signel_vw();
    //signel_level();
    //ch8_dtu_rf();
  }
}

