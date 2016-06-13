
#include "kernel.h"
#include "msp430f149_uart.h"
#include "msp430f149_gpio.h"
#include "msp430f149_timer.h"

extern unsigned char Trg;
extern unsigned char Cont;
unsigned int timecounts = 0;
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  RCC_HSECLKInit();
  
  
  UART_Init(UART_0,UART_SouceClk_SMCLK,UART_SMCLKBaud_9600);//ÉèÖÃ´®¿Ú
  printf("hello\r\n");
  
  
  P6DIR = 0xFF;                             // All P6.x outputs
  P6OUT = 0xFF;                                // All P6.x rese
  
  P1DIR = 0xFF;                             // All P6.x outputs
  P1OUT = 0xFF;                                // All P6.x rese
  
  P1DIR = 0x00;                             // All P1.x input
  
  KeyTimerSet();
__enable_interrupt();
  while(1)
  {
 // delay_ms(40);
    if(Trg == 0x01)
      {P6OUT = 0x00;printf("key pressed.\r\n");}
    if(Cont == 0x01)
      {
        printf("key  still pressed..........\r\n");
        timecounts++;
        if(timecounts == 100)
          {P6OUT = 0xff;printf("long key \r\n");timecounts = 0;}
      }
    if(Cont == 0x00)
      {P6OUT = 0xff;timecounts = 0;}

  }
} 


// Watchdog Timer interrupt service routine
//#pragma vector=WDT_VECTOR
//__interrupt void watchdog_timer(void)
//{
// LPM3_EXIT;
//}

