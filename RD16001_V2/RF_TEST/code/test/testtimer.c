#include <msp430.h>
#include "gpio.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
void testtimer(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  ClkInit();
  
  P3DIR  |= BIT5;                     
  P3SEL  |= BIT5; 
  
  TBCCTL0 = OUTMOD_4;                       // toggle
  TBCCR0  = 8000-1;
  TBCTL   = TBSSEL_2 + MC_1;                // SMCLK, Up to CCR0 mode
}