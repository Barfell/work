#include <msp430.h>
#include "test.h"
#include "includes.h"
#include "power.h"


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
    //testusart();
    //testcmd();
    //testfreq();
    //testrtc();
    //testsd();
    //testsst25();
    
    //testrain();
    //test485();
    //testrf();
    //testdtu();
//    LED(1);
//    delay_ms(2000);
//    LED(0);
//    delay_ms(2000);
  }
}

