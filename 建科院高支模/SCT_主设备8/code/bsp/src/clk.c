#include "msp430.h"
#include "clk.h"
#include "kernel.h"

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
  
  
  SysTickInit();
  
    /*用于控制串口0选择哪个通道   DTU  或者 RF */
  P1REN &= ~BIT1;
  P1REN &= ~BIT2;
  P1DIR |=  BIT1;
  P1DIR |=  BIT2;
  P1OUT &=  ~BIT1;
  P1OUT &=  ~BIT2;//默认初始化是N2
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