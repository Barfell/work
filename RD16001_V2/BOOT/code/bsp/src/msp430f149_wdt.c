#include "msp430.h"

void WatchDogOn(void)
{
  WDTCTL = WDT_ARST_250;
}

void WatchDogOff(void)
{
  WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
}
void FeedWatchDog(void)
{
  WDTCTL = WDT_ARST_250;
}