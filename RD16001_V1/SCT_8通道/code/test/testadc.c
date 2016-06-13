#include <msp430.h>
#include "gpio.h"
#include "uart.h"
#include "kernel.h"
#include "clk.h"
#include "timer.h"
#include "power.h"
#include "sd.h"
#include <stdio.h>
unsigned int results;
void testsd(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  ClkInit();
  PowerInit();
  PWR_ON;
  CORE_PWR_ON;
  COLL_PWR_ON;
  
  UARTInit(UART_0, UART_Clk_SMCLK, Baud_115200);
 
  SDInit();
  while(1)
  {
    SD16CCTL2 |= SD16SC;                    // Set bit to start conversion
    while ((SD16CCTL2 & SD16IFG)==0);       // Poll interrupt flag for CH2
    results = SD16MEM2;                     // Save CH2 results (clears IFG)
    SD16CCTL2 &= ~SD16SC;
    printf("results:%d\r\n",results);
    delay_ms(500);
  }
  
} 