#include "spi.h"
#include "kernal.h"
#include "ltc2402.h"
#include "test.h"


void TestLtc2402(void)
{
    u8 u8channel = 0;
    LTC2402Init();
    LTC2402_SWitchInit();
	DelayMs_Sft(150);
	printf("ce liang begin!!!\r\n");
    while(1)
    {
//		u8channel++;
//        if(u8channel==6)
//        {
//            u8channel = 1;
//        }
		
//		printf("Channel %d  ",u8channel);
//		LTC2402_SwitchChannel(u8channel);
//		DelayMs_Sft(200);
//		GetNTCTemperature(LTC2402_GetResistance()-0.6178483);
//		DelayMs_Sft(585);
		
		
		
			LTC2402_SwitchChannel(5);
			DelayMs_Sft(200);
			printf("%f\r\n",LTC2402_GetResistance());
		
		
//		if(u8channel<5)
//		{
//			printf("Channel %d  ",u8channel);
//			LTC2402_SwitchChannel(u8channel);
//			DelayMs_Sft(150);
//			GetNTCTemperature(LTC2402_GetResistance()-0.6178483);
//		}
//		if(u8channel == 5)
//		{
//			printf("Channel %d  ",u8channel);
//			LTC2402_SwitchChannel(u8channel);
//			DelayMs_Sft(150);
//			GetPTTemperature(LTC2402_GetResistance()-0.6178483);
////			LTC2402_SwitchChannel(u8channel);
////			DelayMs_Sft(150);
////			printf("Channel %f  \r\n",LTC2402_GetResistance());
//		}
		
//        DelayMs_Sft(585);
    }
    
}

