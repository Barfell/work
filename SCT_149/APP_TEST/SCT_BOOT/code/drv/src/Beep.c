#include "msp430f149_gpio.h"
#include "Beep.h"
#include "kernel.h"

void BeepInit(void)
{
  P4DIR |= BIT0;
  P4OUT &= ~BIT0;
}

void Beep(unsigned char i)
{
  BEEP_ON;
  delay_ms(50);
  BEEP_OFF;
}



