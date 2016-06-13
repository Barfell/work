#include "Test.h"
#include "AppStorage.h" 
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
	TestDtu();
//	TestUartFlash();
//	TestAm2305();
//	TestAds1248();
//	TestSST25VF0();
//	TestRtc();
//	TestAdc();
//	TestLed();
//	TestCrc();	
//	TestLTC2402();
//	TestDs18b20();
//	TestAds1248andDs18b20();
}

STATIC VOID AppProc(VOID)
{
//	DataStorage();
}

int main(void)
{	

	OsInit();
	BoardInit();
	TestProc();
	AppProc();
	return 0;
}

