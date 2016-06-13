#include "msp430.h"
#include "clk.h"

void ClkInit(void)
{
  volatile unsigned int i;
  FLL_CTL0 |= XCAP11PF;                       //LXT CAP 
  FLL_CTL1 &= ~XT2OFF;                        // Activate XT2 high freq xtal
  /* Wait for xtal to stabilize*/
  do
  {
    IFG1 &= ~OFIFG;                           
    for (i = 550; i > 0; i--);
  }
  while (IFG1 & OFIFG);                       // OSCFault flag still set
  
  FLL_CTL1 |= SELS;                           // SMCLK = XT2CLK
  FLL_CTL2 |= XT2S_2;                         // 2-16mhz
  FLL_CTL1 |= SELM1;                          // MCLK = XT2
  FLL_CTL1 &= ~SMCLKOFF;                      // SMCLK ON
  
}

void ClkOff(void)
{
  FLL_CTL1 &= ~SELS;                            // SMCLK = DCOCLK
  FLL_CTL1 |= SMCLKOFF;                         // SMCLK OFF
  FLL_CTL2 &= ~XT2S_2;                          // 2-16mhz
  FLL_CTL1 &= ~SELM1;                           // MCLK = DCOCLK
  FLL_CTL1 |= XT2OFF;                           // XT2 OFF
  FLL_CTL1 |= XT2OFF;
}