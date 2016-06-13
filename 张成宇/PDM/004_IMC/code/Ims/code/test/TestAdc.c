#include "Adc.h" 
VOID TestAdc(VOID)
{
	U16 u16Value;
	double dValue;
	AdcInit();
	
	
	while(1)
	{
		u16Value = GetAdc(ADC_CHANNEL);
		dValue = (u16Value/4096.0)*3.298;
		printf("Current voltage = %fv", dValue);
		DelayMs(1000);
	}
	
}
