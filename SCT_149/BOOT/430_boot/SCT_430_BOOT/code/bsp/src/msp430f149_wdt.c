#include "msp430f149_flash.h"
#include "i430type.h"
#include "msp430f149_wdt.h"

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