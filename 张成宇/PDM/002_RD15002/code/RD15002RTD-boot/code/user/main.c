#include "Test.h"
#include "Serial.h" 
#include "Led.h" 
#include "flash.h"
VOID BoardInit(VOID)
{
	USART_InitTypeDef Usart_InitStruct;
	
	UartInit(&Usart_InitStruct, 115200);
	
	UartCreate(USART1, &Usart_InitStruct, FALSE, TRUE);
	
	UartOpen(USART1);

	LedInit();
	
	LedOn();
	DelayMs(200);
	LedOff();
	DelayMs(200);
	LedOn();
	DelayMs(200);
	LedOff();
	DelayMs(200);
	LedOn();
}

STATIC VOID TestProc(VOID)
{
	
//	TestSST25VF0();
//	TestSST25VF0_Storage();
//	TestUart1();

}

STATIC VOID AppProc(VOID)
{
	U8 szData[4] = {0}; 
		
	FlashReadSTM32(UPDATE_FLAG_ADDRESS, 4, szData);
	
	if((szData[0] == 0xAA) && (szData[1] == 0x55) && (szData[2] == 0xAA) && (szData[3] == 0x55))//ÍøÂçÉý¼¶ 
	{
		DtuBoot();
	}
	UartBoot();
}

int main(void)
{	

	OsInit();
	BoardInit();
	TestProc();
	AppProc();
	return 0;
}

