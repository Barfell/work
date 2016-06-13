#include "FreqMeasurement.h"
#include  "bsp_init.h"
#include "bsp_io_control.h"
VOID TestFreqMeasure(VOID)
{
	double dValue;
	U32 u32Tick;
	U8 u8Cnt;
	BoardGPIOConfig();
	SW_12V(1);
	SW_5V(1);
	Time3_Config();
	Time2_Config();
	Time4_Config();
	Nvic_Config();
	FreqModuleInit();
	
	while(1)
	{
		for(u8Cnt = 0; u8Cnt < 8; u8Cnt++)
		{
			if(u8Cnt == 0)
			{
				u32Tick = GetTickCount();
				printf("Start Tick = %d\r\n", u32Tick);
			}
			dValue = GetFreq(u8Cnt);
			printf("Frequency channel %d = %.6f\r\n", u8Cnt, dValue);
			
			if(u8Cnt == 7)
			{
				u32Tick = GetTickCount();
				printf("End Tick = %d\r\n", u32Tick);
			}
		}
	}
	
	
}


