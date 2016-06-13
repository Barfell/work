#include "Test.h"
#include "AppMain.h" 
#include "Serial.h" 
#include "Led.h" 
#include "Adc.h"
#include "Rtc.h" 
#include "flash.h"
VOID BoardInit(VOID)
{
	USART_InitTypeDef Usart_InitStruct;
	
	UartInit(&Usart_InitStruct, 115200);

	UartCreate(USART1, &Usart_InitStruct, FALSE, TRUE);
	
	UartOpen(USART1);
		
	LedInit();
	DelayMs_Sft(1000);
	LedOn();
	RTC_Init(); 
    AdcInit();
	
	
}
STATIC VOID TestProc(VOID)
{
//	TestUart1Ex(); 
//	TestUart1Timer();
//	TestUartFlash();
//	TestAm2305();
//	TestAds1248();
//	TestSST25VF0();
//	TestRtc();
//	TestAdc();
//	TestLed();
//	TestCrc();	
//	TestLTC2402();
}

STATIC VOID AppProc(VOID)
{
	AppMain();
}

int main(void)
{	

	OsInit();
	BoardInit();
	TestProc();
	AppProc();
	return 0;
}

