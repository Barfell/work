#include "Led.h" 
#include "Timer.h" 
VOID TestLed(VOID)
{
	U32 u32Tick;
	
	LedInit();
		
	u32Tick = GetTickCount();
	while(1)
	{
		if((GetTickCount() - u32Tick) < 1000)
		{
			LedOn();
		}
		else if((GetTickCount() - u32Tick) < 2000)
		{
			LedOff();	
		}
		else
		{
			u32Tick = GetTickCount();
		}
        
	}
}
