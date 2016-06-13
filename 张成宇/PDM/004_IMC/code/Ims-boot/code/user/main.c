#include "Test.h"
#include "Serial.h" 
#include "flash.h"
#include "pwc.h"
VOID BoardInit(VOID)
{
	USART_InitTypeDef Usart_InitStruct;
	
	UartInit(&Usart_InitStruct, 115200);
	
	UartCreate(USART2, &Usart_InitStruct, FALSE, TRUE);
	
	UartOpen(USART2);
	
	PWCInit();
}

STATIC VOID TestProc(VOID)
{
	
//	TestUart1();

}
EXTERN VOID EnterAppProc(VOID);

STATIC VOID AppProc(VOID)
{
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

