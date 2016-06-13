#include "Led.h"

VOID TestLedProc(VOID)
{
    LedInit();

    while(1)
    {
		SysLedOn();
		DatLedOn();
		PwrLedOn();
		
		DelayMs(1000);
		
		SysLedOff();
		DatLedOff();
		PwrLedOff();
		
		DelayMs(1000);
        
    }
       
}


