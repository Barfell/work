#include <msp430.h>
#include "test.h"
#include "includes.h"
#include "power.h"


int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  while(1)
  {
    ch8_center_Task();
    
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
   // test485();
    //testrf();
    //testdtu();
    
//ClkInit();
//PowerInit();
//PWR_ON;
//COLL_PWR_ON;
//TRAN_PWR_ON;
//LED(1);
//LED(1);
//delay_ms(2000);
//LED(0);
//delay_ms(2000);
  }
}

