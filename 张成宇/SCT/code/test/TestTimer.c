#include "Led.h" 
#include "Timer.h" 
VOID TestTimer(VOID)
{
	LedInit();
	
	TIM_Create();
	
	while(1)
	{
		LedOn();
		SetTimer(1000);
		TIM_Open();
		while(GetTimer() > 0);
		LedOff();
		SetTimer(1000);
		TIM_Open();
		while(GetTimer() > 0);
	}
}
